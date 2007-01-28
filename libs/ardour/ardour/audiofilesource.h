/*
    Copyright (C) 2006 Paul Davis 

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

#ifndef __ardour_audiofilesource_h__ 
#define __ardour_audiofilesource_h__

#include <time.h>

#include <ardour/audiosource.h>

namespace ARDOUR {

struct SoundFileInfo {
    float       samplerate;
    uint16_t    channels;
    int64_t     length;
    std::string format_name;
    int64_t     timecode;
};

class AudioFileSource : public AudioSource {
  public:
	enum Flag {
		Writable = 0x1,
		CanRename = 0x2,
		Broadcast = 0x4,
		Removable = 0x8,
		RemovableIfEmpty = 0x10,
		RemoveAtDestroy = 0x20,
		NoPeakFile = 0x40,
		Destructive = 0x80
	};

	virtual ~AudioFileSource ();

	int set_name (string newname, bool destructive);

	string path() const { return _path; }
	string peak_path (string audio_path);
	string old_peak_path (string audio_path);

	static void set_peak_dir (string dir) { peak_dir = dir; }

	static bool get_soundfile_info (string path, SoundFileInfo& _info, string& error);

	static bool safe_file_extension (string path);

	void set_allow_remove_if_empty (bool yn);
	void mark_for_remove();

	/* this block of methods do nothing for regular file sources, but are significant
	   for files used in destructive recording.
	*/

	virtual nframes_t last_capture_start_frame() const { return 0; }
	virtual void           mark_capture_start (nframes_t) {}
	virtual void           mark_capture_end () {}
	virtual void           clear_capture_marks() {}

	virtual int update_header (nframes_t when, struct tm&, time_t) = 0;
	virtual int flush_header () = 0;

	int move_to_trash (const string trash_dir_name);

	static bool is_empty (Session&, string path);
	void mark_streaming_write_completed ();

	void   mark_take (string);
	string take_id() const { return _take_id; }

	bool is_embedded() const { return _is_embedded; }

	static void set_bwf_serial_number (int);
	
	static void set_search_path (string);
	static void set_header_position_offset (nframes_t offset );

	int setup_peakfile ();

	static sigc::signal<void> HeaderPositionOffsetChanged;

	XMLNode& get_state ();
	int set_state (const XMLNode&);

	bool destructive() const { return (_flags & Destructive); }
	virtual bool set_destructive (bool yn) { return false; }

	Flag flags() const { return _flags; }

	void mark_immutable ();

	/* this should really be protected, but C++ is getting stricter
	   and creating slots from protected member functions is starting
	   to cause issues.
	*/

	virtual void handle_header_position_change ();

  protected:
	
	/* constructor to be called for existing external-to-session files */

	AudioFileSource (Session&, std::string path, Flag flags);

	/* constructor to be called for new in-session files */

	AudioFileSource (Session&, std::string path, Flag flags,
			 SampleFormat samp_format, HeaderFormat hdr_format);

	/* constructor to be called for existing in-session files */

	AudioFileSource (Session&, const XMLNode&);

	int init (string idstr, bool must_exist);

	string        _path;
	Flag          _flags;
	string        _take_id;
	int64_t       timeline_position;
	bool           file_is_new;
	uint16_t       channel;

	bool          _is_embedded;
	static bool determine_embeddedness(string path);

	static string peak_dir;
	static string search_path;

	static char bwf_country_code[3];
	static char bwf_organization_code[4];
	static char bwf_serial_number[13];

	static uint64_t header_position_offset;

	virtual void set_timeline_position (int64_t pos);
	virtual void set_header_timeline_position () = 0;

	bool find (std::string path, bool must_exist, bool& is_new);
	bool removable() const;
	bool writable() const { return _flags & Writable; }
};

} // namespace ARDOUR

#endif /* __ardour_audiofilesource_h__ */

