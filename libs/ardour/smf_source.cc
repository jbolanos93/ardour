/*
    Copyright (C) 2006 Paul Davis 
	Written by Dave Robillard, 2006

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <vector>

#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include <pbd/mountpoint.h>
#include <pbd/pathscanner.h>
#include <pbd/stl_delete.h>
#include <pbd/strsplit.h>

#include <glibmm/miscutils.h>

#include <ardour/smf_source.h>
#include <ardour/session.h>
#include <ardour/midi_ring_buffer.h>
#include <ardour/midi_util.h>

#include "i18n.h"

using namespace ARDOUR;

string SMFSource::_search_path;

/*sigc::signal<void,struct tm*, time_t> SMFSource::HeaderPositionOffsetChanged;
bool                                  SMFSource::header_position_negative;
uint64_t                              SMFSource::header_position_offset;
*/

SMFSource::SMFSource (std::string path, Flag flags)
	: MidiSource (region_name_from_path(path))
	, _channel(0)
	, _flags (Flag(flags | Writable)) // FIXME: this needs to be writable for now
	, _allow_remove_if_empty(true)
	, _timeline_position (0)
	, _fd (0)
	, _last_ev_time(0)
	, _track_size(4) // compensate for the EOT event
{
	/* constructor used for new internal-to-session files. file cannot exist */

	if (init (path, false)) {
		throw failed_constructor ();
	}
	
	if (open()) {
		throw failed_constructor ();
	}
	
	assert(_name.find("/") == string::npos);

	SourceCreated (this); /* EMIT SIGNAL */
}

SMFSource::SMFSource (const XMLNode& node)
	: MidiSource (node)
	, _channel(0)
	, _flags (Flag (Writable|CanRename))
	, _allow_remove_if_empty(true)
	, _timeline_position (0)
	, _fd (0)
	, _last_ev_time(0)
	, _track_size(4) // compensate for the EOT event
{
	/* constructor used for existing internal-to-session files. file must exist */

	if (set_state (node)) {
		throw failed_constructor ();
	}
	
	if (init (_name, true)) {
		throw failed_constructor ();
	}
	
	if (open()) {
		throw failed_constructor ();
	}
	
	assert(_name.find("/") == string::npos);
	
	SourceCreated (this); /* EMIT SIGNAL */
}

SMFSource::~SMFSource ()
{
	if (removable()) {
		unlink (_path.c_str());
	}
}

bool
SMFSource::removable () const
{
	return (_flags & Removable) && ((_flags & RemoveAtDestroy) || 
				      ((_flags & RemovableIfEmpty) && is_empty (_path)));
}

int
SMFSource::init (string pathstr, bool must_exist)
{
	bool is_new = false;

	if (!find (pathstr, must_exist, is_new)) {
		cerr << "cannot find " << pathstr << " with me = " << must_exist << endl;
		return -1;
	}

	if (is_new && must_exist) {
		return -1;
	}

	assert(_name.find("/") == string::npos);
	return 0;
}

int
SMFSource::open()
{
	cerr << "Opening SMF file " << path() << " writeable: " << writable() << endl;

	// FIXME
	//_fd = fopen(path().c_str(), writable() ? "r+" : "r");
	_fd = fopen(path().c_str(), "w+");

	// FIXME: pad things out so writing the header later doesn't overwrite data
	flush_header();

	// FIXME
	//return (_fd == 0) ? -1 : 0;
	return 0;
}

int
SMFSource::update_header (jack_nframes_t when, struct tm&, time_t)
{
	_timeline_position = when;
	return flush_header();
}

int
SMFSource::flush_header ()
{
	// FIXME: write timeline position somehow?
	
	cerr << "SMF Flushing header\n";

	assert(_fd);

	const uint16_t type     = GUINT16_TO_BE(0);    // SMF Type 0 (single track)
	const uint16_t ntracks  = GUINT16_TO_BE(1);    // Number of tracks (always 1 for Type 0)
	const uint16_t division = GUINT16_TO_BE(1920); // FIXME FIXME FIXME PPQN

	char data[6];
	memcpy(data, &type, 2);
	memcpy(data+2, &ntracks, 2);
	memcpy(data+4, &division, 2);

	_fd = freopen(path().c_str(), "r+", _fd);
	assert(_fd);
	fseek(_fd, 0, 0);
	write_chunk("MThd", 6, data);
	//if (_track_size > 0) {
		write_chunk_header("MTrk", _track_size); 
	//}

	_header_size = 22;

	fflush(_fd);

	return 0;
}

/** Returns the offset of the first event in the file with a time past @a start,
 * relative to the start of the source.
 *
 * Returns -1 if not found.
 */
/*
long
SMFSource::find_first_event_after(jack_nframes_t start)
{
	// FIXME: obviously this is slooow
	
	fseek(_fd, _header_size, 0);

	while ( ! feof(_fd) ) {
		const uint32_t delta_time = read_var_len();

		if (delta_time > start)
			return delta_time;
	}

	return -1;
}
*/

/** Read an event from the current position in file.
 *
 * File position MUST be at the beginning of a delta time, or this will die very messily.
 * ev.buffer must be of size ev.size, and large enough for the event.
 *
 * Returns 0 on success, -1 if EOF.
 */
int
SMFSource::read_event(MidiEvent& ev) const
{
	if (feof(_fd)) {
		return -1;
	}

	uint32_t delta_time = read_var_len();
	int status = fgetc(_fd);
	assert(status != EOF); // FIXME die gracefully
	ev.buffer[0] = (unsigned char)status;
	ev.size = midi_event_size(ev.buffer[0]) + 1;
	fread(ev.buffer+1, 1, ev.size - 1, _fd);
	
	printf("SMF - read event, delta = %u, size = %zu, data = ",
		delta_time, ev.size);
	for (size_t i=0; i < ev.size; ++i) {
		printf("%X ", ev.buffer[i]);
	}
	printf("\n");
	
	return 0;
}

jack_nframes_t
SMFSource::read_unlocked (MidiRingBuffer& dst, jack_nframes_t start, jack_nframes_t cnt) const
{
	cerr << "SMF - read " << start << " -- " << cnt;

	// FIXME: ugh
	unsigned char ev_buf[MidiBuffer::max_event_size()];
	MidiEvent ev;
	ev.time = 0;
	ev.size = MidiBuffer::max_event_size();
	ev.buffer = ev_buf;

	while (true) {
		int ret = read_event(ev);
		if (ret == -1) {
			break;
		}

		if (ev.time >= start) {
			if (ev.time > start + cnt) {
				break;
			} else {
				dst.write(ev);
			}
		}
	}
#if 0
	cerr << "SMF pretending to read" << endl;

	MidiEvent ev;
	RawMidi data[4];

	const char note = rand()%30 + 30;
	
	ev.buffer = data;
	ev.time = start+1; // FIXME: bug at 0?
	ev.size = 3;

	data[0] = 0x90;
	data[1] = note;
	data[2] = 120;

	dst.write(ev);
	
	ev.buffer = data;
	ev.time = start + (jack_nframes_t)(cnt * 8.0/10.0);
	ev.size = 3;

	data[0] = 0x80;
	data[1] = note;
	data[2] = 64;
	
	dst.write(ev);

	//dst.clear();
#endif
	return cnt;
}

jack_nframes_t
SMFSource::write_unlocked (MidiRingBuffer& src, jack_nframes_t cnt)
{
	cerr << "SMF WRITE -- " << _length << "--" << cnt << endl;
	
	MidiBuffer buf(1024); // FIXME: allocation, size?
	src.read(buf, /*_length*/0, _length + cnt); // FIXME?

	fseek(_fd, 0, SEEK_END);

	// FIXME: start of source time?
	
	for (size_t i=0; i < buf.size(); ++i) {
		const MidiEvent& ev = buf[i];
		assert(ev.time >= _timeline_position);
		uint32_t delta_time = (ev.time - _timeline_position) - _last_ev_time;
		
		printf("SMF - writing event, delta = %u, size = %zu, data = ",
			delta_time, ev.size);
		for (size_t i=0; i < ev.size; ++i) {
			printf("%X ", ev.buffer[i]);
		}
		printf("\n");
		
		size_t stamp_size = write_var_len(delta_time);
		fwrite(ev.buffer, 1, ev.size, _fd);
		_last_ev_time += delta_time;
		_track_size += stamp_size + ev.size;
	}

	fflush(_fd);

	ViewDataRangeReady (_length, cnt); /* EMIT SIGNAL */
	update_length(_length, cnt);
	return cnt;
}

XMLNode&
SMFSource::get_state ()
{
	XMLNode& root (MidiSource::get_state());
	char buf[16];
	snprintf (buf, sizeof (buf), "0x%x", (int)_flags);
	root.add_property ("flags", buf);
	return root;
}

int
SMFSource::set_state (const XMLNode& node)
{
	const XMLProperty* prop;

	if (MidiSource::set_state (node)) {
		return -1;
	}

	if ((prop = node.property (X_("flags"))) != 0) {

		int ival;
		sscanf (prop->value().c_str(), "0x%x", &ival);
		_flags = Flag (ival);

	} else {

		_flags = Flag (0);

	}

	assert(_name.find("/") == string::npos);

	return 0;
}

void
SMFSource::mark_for_remove ()
{
	if (!writable()) {
		return;
	}
	_flags = Flag (_flags | RemoveAtDestroy);
}

void
SMFSource::mark_streaming_write_completed ()
{
	if (!writable()) {
		return;
	}
	
	cerr << "SMF - Writing EOT\n";

	fseek(_fd, 0, SEEK_END);
	write_var_len(1); // whatever...
	char eot[4] = { 0xFF, 0x2F, 0x00 }; // end-of-track meta-event
	fwrite(eot, 1, 4, _fd);
	fflush(_fd);

#if 0
	Glib::Mutex::Lock lm (_lock);


	next_peak_clear_should_notify = true;

	if (_peaks_built || pending_peak_builds.empty()) {
		_peaks_built = true;
		 PeaksReady (); /* EMIT SIGNAL */
	}
#endif
}

void
SMFSource::mark_take (string id)
{
	if (writable()) {
		_take_id = id;
	}
}

int
SMFSource::move_to_trash (const string trash_dir_name)
{
	string newpath;

	if (!writable()) {
		return -1;
	}

	/* don't move the file across filesystems, just
	   stick it in the `trash_dir_name' directory
	   on whichever filesystem it was already on.
	*/

	newpath = Glib::path_get_dirname (_path);
	newpath = Glib::path_get_dirname (newpath);

	newpath += '/';
	newpath += trash_dir_name;
	newpath += '/';
	newpath += Glib::path_get_basename (_path);

	if (access (newpath.c_str(), F_OK) == 0) {

		/* the new path already exists, try versioning */
		
		char buf[PATH_MAX+1];
		int version = 1;
		string newpath_v;

		snprintf (buf, sizeof (buf), "%s.%d", newpath.c_str(), version);
		newpath_v = buf;

		while (access (newpath_v.c_str(), F_OK) == 0 && version < 999) {
			snprintf (buf, sizeof (buf), "%s.%d", newpath.c_str(), ++version);
			newpath_v = buf;
		}
		
		if (version == 999) {
			PBD::error << string_compose (_("there are already 1000 files with names like %1; versioning discontinued"),
					  newpath)
			      << endmsg;
		} else {
			newpath = newpath_v;
		}

	} else {

		/* it doesn't exist, or we can't read it or something */

	}

	if (::rename (_path.c_str(), newpath.c_str()) != 0) {
		PBD::error << string_compose (_("cannot rename audio file source from %1 to %2 (%3)"),
				  _path, newpath, strerror (errno))
		      << endmsg;
		return -1;
	}
#if 0
	if (::unlink (peakpath.c_str()) != 0) {
		PBD::error << string_compose (_("cannot remove peakfile %1 for %2 (%3)"),
				  peakpath, _path, strerror (errno))
		      << endmsg;
		/* try to back out */
		rename (newpath.c_str(), _path.c_str());
		return -1;
	}
	    
	_path = newpath;
	peakpath = "";
#endif	
	/* file can not be removed twice, since the operation is not idempotent */

	_flags = Flag (_flags & ~(RemoveAtDestroy|Removable|RemovableIfEmpty));

	return 0;
}

// FIXME: Merge this with audiofilesource somehow (make a generic filesource?)
bool
SMFSource::find (string pathstr, bool must_exist, bool& isnew)
{
	string::size_type pos;
	bool ret = false;

	isnew = false;

	/* clean up PATH:CHANNEL notation so that we are looking for the correct path */

	if ((pos = pathstr.find_last_of (':')) == string::npos) {
		pathstr = pathstr;
	} else {
		pathstr = pathstr.substr (0, pos);
	}

	if (pathstr[0] != '/') {

		/* non-absolute pathname: find pathstr in search path */

		vector<string> dirs;
		int cnt;
		string fullpath;
		string keeppath;

		if (_search_path.length() == 0) {
			PBD::error << _("FileSource: search path not set") << endmsg;
			goto out;
		}

		split (_search_path, dirs, ':');

		cnt = 0;
		
		for (vector<string>::iterator i = dirs.begin(); i != dirs.end(); ++i) {

			fullpath = *i;
			if (fullpath[fullpath.length()-1] != '/') {
				fullpath += '/';
			}
			fullpath += pathstr;
			
			if (access (fullpath.c_str(), R_OK) == 0) {
				keeppath = fullpath;
				++cnt;
			} 
		}

		if (cnt > 1) {

			PBD::error << string_compose (_("FileSource: \"%1\" is ambigous when searching %2\n\t"), pathstr, _search_path) << endmsg;
			goto out;

		} else if (cnt == 0) {

			if (must_exist) {
				PBD::error << string_compose(_("Filesource: cannot find required file (%1): while searching %2"), pathstr, _search_path) << endmsg;
				goto out;
			} else {
				isnew = true;
			}
		}
		
		_name = pathstr;
		_path = keeppath;
		ret = true;

	} else {
		
		/* external files and/or very very old style sessions include full paths */
		
		_path = pathstr;
		_name = pathstr.substr (pathstr.find_last_of ('/') + 1);
		
		if (access (_path.c_str(), R_OK) != 0) {

			/* file does not exist or we cannot read it */

			if (must_exist) {
				PBD::error << string_compose(_("Filesource: cannot find required file (%1): %2"), _path, strerror (errno)) << endmsg;
				goto out;
			}
			
			if (errno != ENOENT) {
				PBD::error << string_compose(_("Filesource: cannot check for existing file (%1): %2"), _path, strerror (errno)) << endmsg;
				goto out;
			}
			
			/* a new file */

			isnew = true;
			ret = true;

		} else {
			
			/* already exists */

			ret = true;
		}
	}
	
  out:
	return ret;
}

void
SMFSource::set_search_path (string p)
{
	_search_path = p;
}


void
SMFSource::set_allow_remove_if_empty (bool yn)
{
	if (writable()) {
		_allow_remove_if_empty = yn;
	}
}

int
SMFSource::set_name (string newname, bool destructive)
{
	//Glib::Mutex::Lock lm (_lock); FIXME
	string oldpath = _path;
	string newpath = Session::change_audio_path_by_name (oldpath, _name, newname, destructive);

	if (newpath.empty()) {
		PBD::error << string_compose (_("programming error: %1"), "cannot generate a changed audio path") << endmsg;
		return -1;
	}

	if (rename (oldpath.c_str(), newpath.c_str()) != 0) {
		PBD::error << string_compose (_("cannot rename audio file for %1 to %2"), _name, newpath) << endmsg;
		return -1;
	}

	_name = Glib::path_get_basename (newpath);
	_path = newpath;

	return 0;//rename_peakfile (peak_path (_path));
}

bool
SMFSource::is_empty (string path)
{
	/* XXX fix me */

	return false;
}


void
SMFSource::write_chunk_header(char id[4], uint32_t length)
{
	const uint32_t length_be = GUINT32_TO_BE(length);

	fwrite(id, 1, 4, _fd);
	fwrite(&length_be, 4, 1, _fd);
}

void
SMFSource::write_chunk(char id[4], uint32_t length, void* data)
{
	write_chunk_header(id, length);
	
	fwrite(data, 1, length, _fd);
}

/** Returns the size (in bytes) of the value written. */
size_t
SMFSource::write_var_len(uint32_t value)
{
	size_t ret = 0;

	uint32_t buffer = value & 0x7F;

	while ( (value >>= 7) ) {
		buffer <<= 8;
		buffer |= ((value & 0x7F) | 0x80);
	}

	while (true) {
		printf("Writing var len byte %X\n", (unsigned char)buffer);
		++ret;
		fputc(buffer, _fd);
		if (buffer & 0x80)
			buffer >>= 8;
		else
			break;
	}

	return ret;
}

uint32_t
SMFSource::read_var_len() const
{
	assert(!feof(_fd));

	uint32_t value;
	unsigned char c;

	if ( (value = getc(_fd)) & 0x80 ) {
		value &= 0x7F;
		do {
			assert(!feof(_fd));
			value = (value << 7) + ((c = getc(_fd)) & 0x7F);
		} while (c & 0x80);
	}

	return value;
}
