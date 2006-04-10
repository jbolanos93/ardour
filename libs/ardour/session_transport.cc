/*
    Copyright (C) 1999-2003 Paul Davis 

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

    $Id$
*/

#include <cmath>
#include <cerrno>
#include <unistd.h>

#include <sigc++/bind.h>
#include <sigc++/retype.h>

#include <pbd/undo.h>
#include <pbd/error.h>
#include <pbd/lockmonitor.h>
#include <pbd/pthread_utils.h>

#include <midi++/mmc.h>
#include <midi++/port.h>

#include <ardour/ardour.h>
#include <ardour/audioengine.h>
#include <ardour/session.h>
#include <ardour/diskstream.h>
#include <ardour/auditioner.h>
#include <ardour/slave.h>
#include <ardour/location.h>

#include "i18n.h"

using namespace std;
using namespace ARDOUR;
using namespace sigc;

void
Session::request_input_change_handling ()
{
	Event* ev = new Event (Event::InputConfigurationChange, Event::Add, Event::Immediate, 0, 0.0);
	queue_event (ev);
}

void
Session::request_slave_source (SlaveSource src, jack_nframes_t pos)
{
	Event* ev = new Event (Event::SetSlaveSource, Event::Add, Event::Immediate, pos, 0.0);

	if (src == Session::JACK) {
	  /* could set_seamless_loop() be disposed of entirely?*/
	  set_seamless_loop (false);
	} else {

	  set_seamless_loop (true);
	}
	ev->slave = src;
	queue_event (ev);
}

void
Session::request_transport_speed (float speed)
{
	Event* ev = new Event (Event::SetTransportSpeed, Event::Add, Event::Immediate, 0, speed);
	queue_event (ev);
}

void
Session::request_diskstream_speed (DiskStream& ds, float speed)
{
	Event* ev = new Event (Event::SetDiskstreamSpeed, Event::Add, Event::Immediate, 0, speed);
	ev->set_ptr (&ds);
	queue_event (ev);
}

void
Session::request_stop (bool abort)
{
	Event* ev = new Event (Event::SetTransportSpeed, Event::Add, Event::Immediate, 0, 0.0, abort);
	queue_event (ev);
}

void
Session::request_locate (jack_nframes_t target_frame, bool with_roll)
{
	Event *ev = new Event (with_roll ? Event::LocateRoll : Event::Locate, Event::Add, Event::Immediate, target_frame, 0, false);
	queue_event (ev);
}

void
Session::force_locate (jack_nframes_t target_frame, bool with_roll)
{
	Event *ev = new Event (with_roll ? Event::LocateRoll : Event::Locate, Event::Add, Event::Immediate, target_frame, 0, true);
	queue_event (ev);
}

void
Session::request_auto_loop (bool yn)
{
	Event* ev;	
	Location *location = _locations.auto_loop_location();

	if (location == 0 && yn) {
		error << _("Cannot loop - no loop range defined")
		      << endmsg;
		return;
	}

	ev = new Event (Event::SetLoop, Event::Add, Event::Immediate, 0, 0.0, yn);
	queue_event (ev);

	if (!yn && seamless_loop && transport_rolling()) {
		// request an immediate locate to refresh the diskstreams
		// after disabling looping
		request_locate (_transport_frame-1, true);
	}
}

void
Session::set_seamless_loop (bool yn)
{
	if (seamless_loop != yn) {
		seamless_loop = yn;

		if (auto_loop && transport_rolling()) {
			// to reset diskstreams etc
			request_auto_loop (true);
		}
		
		ControlChanged (SeamlessLoop); /* EMIT */
	}
}

void
Session::realtime_stop (bool abort)
{
	/* assume that when we start, we'll be moving forwards */

	if (_transport_speed < 0.0f) {
		post_transport_work = PostTransportWork (post_transport_work | PostTransportStop | PostTransportReverse);
	} else {
		post_transport_work = PostTransportWork (post_transport_work | PostTransportStop);
	}

	if (actively_recording()) {

		/* move the transport position back to where the
		   request for a stop was noticed. we rolled
		   past that point to pick up delayed input.
		*/

#ifndef LEAVE_TRANSPORT_UNADJUSTED
		decrement_transport_position (_worst_output_latency);
#endif

		/* the duration change is not guaranteed to have happened, but is likely */

		post_transport_work = PostTransportWork (post_transport_work | PostTransportDuration);
	}

	if (abort) {
		post_transport_work = PostTransportWork (post_transport_work | PostTransportAbort);
	}

	_clear_event_type (Event::StopOnce);
	_clear_event_type (Event::RangeStop);
	_clear_event_type (Event::RangeLocate);

	disable_record (true);

	reset_slave_state ();
		
	_transport_speed = 0;

	transport_sub_state = (auto_return ? AutoReturning : 0);
}

void
Session::butler_transport_work ()
{
	RWLockMonitor rm (route_lock, false, __LINE__, __FILE__);
	RWLockMonitor dsm (diskstream_lock, false, __LINE__, __FILE__);
		
	if (post_transport_work & PostTransportCurveRealloc) {
		for (RouteList::iterator i = routes.begin(); i != routes.end(); ++i) {
			(*i)->curve_reallocate();
		}
	}

	if (post_transport_work & PostTransportInputChange) {
		for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
			(*i)->non_realtime_input_change ();
		}
	}

	if (post_transport_work & PostTransportSpeed) {
		non_realtime_set_speed ();
	}

	if (post_transport_work & PostTransportReverse) {


		clear_clicks();
		cumulative_rf_motion = 0;
		reset_rf_scale (0);

		for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
			if (!(*i)->hidden()) {
				if ((*i)->speed() != 1.0f || (*i)->speed() != -1.0f) {
					(*i)->seek ((jack_nframes_t) (_transport_frame * (double) (*i)->speed()));
				}
				else {
					(*i)->seek (_transport_frame);
				}
			}
		}
	}

	if (post_transport_work & (PostTransportStop|PostTransportLocate)) {
		non_realtime_stop (post_transport_work & PostTransportAbort);
	}

	if (post_transport_work & PostTransportOverWrite) {
		non_realtime_overwrite ();
	}

	if (post_transport_work & PostTransportAudition) {
		non_realtime_set_audition ();
	}

	atomic_dec (&butler_should_do_transport_work);
}

void
Session::non_realtime_set_speed ()
{
	RWLockMonitor lm (diskstream_lock, false, __LINE__, __FILE__);

	for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
		(*i)->non_realtime_set_speed ();
	}
}

void
Session::non_realtime_overwrite ()
{
	RWLockMonitor lm (diskstream_lock, false, __LINE__, __FILE__);

	for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
		if ((*i)->pending_overwrite) {
			(*i)->overwrite_existing_buffers ();
		}
	}
}

void
Session::non_realtime_stop (bool abort)
{
	struct tm* now;
	time_t     xnow;
	bool       did_record;
	
	did_record = false;
	
	for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
		if ((*i)->get_captured_frames () != 0) {
			did_record = true;
			break;
		}
	}

	/* stop and locate are merged here because they share a lot of common stuff */
	
	time (&xnow);
	now = localtime (&xnow);

	if (auditioner) {
		auditioner->cancel_audition ();
	}

	clear_clicks();
	cumulative_rf_motion = 0;
	reset_rf_scale (0);

	if (did_record) {
		begin_reversible_command ("capture");
		
		Location* loc = _locations.end_location();
		bool change_end = false;

		if (_transport_frame < loc->end()) {

			/* stopped recording before current end */

			if (_end_location_is_free) {

				/* first capture for this session, move end back to where we are */

				change_end = true;
			} 

		} else if (_transport_frame > loc->end()) {
			
			/* stopped recording after the current end, extend it */

			change_end = true;
		}
		
		if (change_end) {
			add_undo (sigc::retype_return<void>(sigc::bind (mem_fun (*loc, &Location::set_end), loc->end())));
			add_redo (sigc::retype_return<void>(sigc::bind (mem_fun (*loc, &Location::set_end), _transport_frame)));
		}

		_end_location_is_free = false;
		_have_captured = true;
	}

	for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
		(*i)->transport_stopped (*now, xnow, abort);
	}
	
	for (RouteList::iterator i = routes.begin(); i != routes.end(); ++i) {
		if (!(*i)->hidden()) {
			(*i)->set_pending_declick (0);
		}
	}

	if (did_record) {
		commit_reversible_command ();
	}	

	if (_engine.running()) {
		update_latency_compensation (true, abort);
	}

	if (auto_return || (post_transport_work & PostTransportLocate) || synced_to_jack()) {

		if (pending_locate_flush) {
			flush_all_redirects ();
		}

		if ((auto_return || synced_to_jack()) && !(post_transport_work & PostTransportLocate)) {

			_transport_frame = last_stop_frame;

			if (synced_to_jack()) {
				_engine.transport_locate (_transport_frame);
			}
		} 

#ifndef LEAVE_TRANSPORT_UNADJUSTED
	}
#endif

		for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
			if (!(*i)->hidden()) {
				if ((*i)->speed() != 1.0f || (*i)->speed() != -1.0f) {
					(*i)->seek ((jack_nframes_t) (_transport_frame * (double) (*i)->speed()));
				}
				else {
					(*i)->seek (_transport_frame);
				}
			}
		}

		deliver_mmc (MIDI::MachineControl::cmdLocate, _transport_frame);

#ifdef LEAVE_TRANSPORT_UNADJUSTED
	}
#endif

	last_stop_frame = _transport_frame;

	send_full_time_code ();
	deliver_mmc (MIDI::MachineControl::cmdStop, 0);
	deliver_mmc (MIDI::MachineControl::cmdLocate, _transport_frame);

	if (did_record) {

		/* XXX its a little odd that we're doing this here
		   when realtime_stop(), which has already executed,
		   will have done this.
		*/

		if (!Config->get_latched_record_enable()) {
			atomic_set (&_record_status, Disabled);
		} else {
			atomic_set (&_record_status, Enabled);
		}
		RecordStateChanged (); /* emit signal */
	}
	
	if ((post_transport_work & PostTransportLocate) && get_record_enabled()) {
		/* capture start has been changed, so save pending state */
		save_state ("", true);
	}

        /* always try to get rid of this */

        remove_pending_capture_state ();
	
	/* save the current state of things if appropriate */

	if (did_record) {
		save_state (_current_snapshot_name);
	}

	if (post_transport_work & PostTransportDuration) {
		DurationChanged (); /* EMIT SIGNAL */
	}

	if (post_transport_work & PostTransportStop) { 
		_play_range = false;

		/* do not turn off autoloop on stop */

	}

	PositionChanged (_transport_frame); /* EMIT SIGNAL */
	TransportStateChange (); /* EMIT SIGNAL */

	/* and start it up again if relevant */

	if ((post_transport_work & PostTransportLocate) && _slave_type == None && pending_locate_roll) {
		request_transport_speed (1.0);
		pending_locate_roll = false;
	}
}

void
Session::check_declick_out ()
{
	bool locate_required = transport_sub_state & PendingLocate;

	/* this is called after a process() iteration. if PendingDeclickOut was set,
	   it means that we were waiting to declick the output (which has just been
	   done) before doing something else. this is where we do that "something else".
	   
	   note: called from the audio thread.
	*/

	if (transport_sub_state & PendingDeclickOut) {

		if (locate_required) {
			start_locate (pending_locate_frame, pending_locate_roll, pending_locate_flush);
			transport_sub_state &= ~(PendingDeclickOut|PendingLocate);
		} else {
			stop_transport (pending_abort);
			transport_sub_state &= ~(PendingDeclickOut|PendingLocate);
		}
	}
}

void
Session::set_auto_loop (bool yn)
{
	/* Called from event-handling context */
	
	if ((actively_recording() && yn) || _locations.auto_loop_location() == 0) {
		return;
	}
	
	set_dirty();

	if (yn && seamless_loop && synced_to_jack()) {
		warning << _("Seamless looping cannot be supported while Ardour is using JACK transport.\n"
			     "Recommend changing the configured options")
			<< endmsg;
		return;
	}

	
	if ((auto_loop = yn)) {

		Location *loc;

		
		if ((loc = _locations.auto_loop_location()) != 0) {

			if (seamless_loop) {
				// set all diskstreams to use internal looping
				for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
					if (!(*i)->hidden()) {
						(*i)->set_loop (loc);
					}
				}
			}
			else {
				// set all diskstreams to NOT use internal looping
				for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
					if (!(*i)->hidden()) {
						(*i)->set_loop (0);
					}
				}
			}
			
			/* stick in the loop event */
			
			Event* event = new Event (Event::AutoLoop, Event::Replace, loc->end(), loc->start(), 0.0f);
			merge_event (event);

			/* locate to start of loop and roll if current pos is outside of the loop range */
			if (_transport_frame < loc->start() || _transport_frame > loc->end()) {
				event = new Event (Event::LocateRoll, Event::Add, Event::Immediate, loc->start(), 0, !synced_to_jack());
				merge_event (event);
			}
			else {
				// locate to current position (+ 1 to force reload)
				event = new Event (Event::LocateRoll, Event::Add, Event::Immediate, _transport_frame + 1, 0, !synced_to_jack());
				merge_event (event);
			}
		}



	} else {
		clear_events (Event::AutoLoop);

		// set all diskstreams to NOT use internal looping
		for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
			if (!(*i)->hidden()) {
				(*i)->set_loop (0);
			}
		}
		
	}
	
	ControlChanged (AutoLoop); /* EMIT SIGNAL */
}

void
Session::flush_all_redirects ()
{
	for (RouteList::iterator i = routes.begin(); i != routes.end(); ++i) {
		(*i)->flush_redirects ();
	}
}

void
Session::start_locate (jack_nframes_t target_frame, bool with_roll, bool with_flush, bool with_loop)
{
	if (synced_to_jack()) {

		float sp;
		jack_nframes_t pos;

		_slave->speed_and_position (sp, pos);

		if (target_frame != pos) {

			/* tell JACK to change transport position, and we will
			   follow along later in ::follow_slave()
			*/

			_engine.transport_locate (target_frame);

			if (sp != 1.0f && with_roll) {
				_engine.transport_start ();
			}

		}

	} else {

		locate (target_frame, with_roll, with_flush, with_loop);
	}
}

void
Session::locate (jack_nframes_t target_frame, bool with_roll, bool with_flush, bool with_loop)
{
	if (actively_recording()) {
		return;
	}

	if (_transport_frame == target_frame && !loop_changing && !with_loop) {
		if (with_roll) {
			set_transport_speed (1.0, false);
		}
		loop_changing = false;
		return;
	}

	_transport_frame = target_frame;

	if (_transport_speed && (!with_loop || loop_changing)) {
		/* schedule a declick. we'll be called again when its done */

		if (!(transport_sub_state & PendingDeclickOut)) {
			transport_sub_state |= (PendingDeclickOut|PendingLocate);
			pending_locate_frame = target_frame;
			pending_locate_roll = with_roll;
			pending_locate_flush = with_flush;
			return;
		} 
	}

	if (transport_rolling() && !auto_play && !with_roll && !(synced_to_jack() && auto_loop)) {
		realtime_stop (false);
	} 

	if ( !with_loop || loop_changing) {

		post_transport_work = PostTransportWork (post_transport_work | PostTransportLocate);
		
		if (with_roll) {
			post_transport_work = PostTransportWork (post_transport_work | PostTransportRoll);
		}

		schedule_butler_transport_work ();

	} else {

		/* this is functionally what clear_clicks() does but with a tentative lock */

		TentativeRWLockMonitor clickm (click_lock, true, __LINE__, __FILE__);
	
		if (clickm.locked()) {
			
			for (Clicks::iterator i = clicks.begin(); i != clicks.end(); ++i) {
				delete *i;
			}
		
			clicks.clear ();
		}
	}

	if (with_roll) {
		/* switch from input if we're going to roll */
		if (Config->get_use_hardware_monitoring()) {
			/* Even though this is called from RT context we are using
			   a non-tentative rwlock here,  because the action must occur.
			   The rarity and short potential lock duration makes this "OK"
			*/
			RWLockMonitor dsm (diskstream_lock, false, __LINE__, __FILE__);
			for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
				if ((*i)->record_enabled ()) {
					//cerr << "switching from input" << __FILE__ << __LINE__ << endl << endl;
					(*i)->monitor_input (!auto_input);
				}
			}
		}
	} else {
		/* otherwise we're going to stop, so do the opposite */
		if (Config->get_use_hardware_monitoring()) {
			/* Even though this is called from RT context we are using
			   a non-tentative rwlock here,  because the action must occur.
			   The rarity and short potential lock duration makes this "OK"
			*/
			RWLockMonitor dsm (diskstream_lock, false, __LINE__, __FILE__);
			for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
				if ((*i)->record_enabled ()) {
					//cerr << "switching to input" << __FILE__ << __LINE__ << endl << endl;
					(*i)->monitor_input (true);
				}
			}
		}
	}

	/* cancel autoloop if transport pos outside of loop range */
	if (auto_loop) {
		Location* al = _locations.auto_loop_location();
		
		if (al && (_transport_frame < al->start() || _transport_frame > al->end())) {
			// cancel looping directly, this is called from event handling context
			set_auto_loop(false);
		}
	}
	
	loop_changing = false;
}

void
Session::set_transport_speed (float speed, bool abort)
{
	if (_transport_speed == speed) {
		return;
	}

	if (speed > 0) {
		speed = min (8.0f, speed);
	} else if (speed < 0) {
		speed = max (-8.0f, speed);
	}

	if (transport_rolling() && speed == 0.0) {

		if (Config->get_use_hardware_monitoring())
		{
			/* Even though this is called from RT context we are using
			   a non-tentative rwlock here,  because the action must occur.
			   The rarity and short potential lock duration makes this "OK"
			*/
			RWLockMonitor dsm (diskstream_lock, false, __LINE__, __FILE__);
			for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
				if ((*i)->record_enabled ()) {
					//cerr << "switching to input" << __FILE__ << __LINE__ << endl << endl;
					(*i)->monitor_input (true);	
				}
			}
		}

		if (synced_to_jack ()) {
			_engine.transport_stop ();
		} else {
			stop_transport (abort);
		}

	} else if (transport_stopped() && speed == 1.0) {

		if (!get_record_enabled() && Config->get_stop_at_session_end() && _transport_frame >= current_end_frame()) {
			return;
		}

		if (Config->get_use_hardware_monitoring()) {
			/* Even though this is called from RT context we are using
			   a non-tentative rwlock here,  because the action must occur.
			   The rarity and short potential lock duration makes this "OK"
			*/
			RWLockMonitor dsm (diskstream_lock, false, __LINE__, __FILE__);
			for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
				if (auto_input && (*i)->record_enabled ()) {
					//cerr << "switching from input" << __FILE__ << __LINE__ << endl << endl;
					(*i)->monitor_input (false);	
				}
			}
		}

		if (synced_to_jack()) {
			_engine.transport_start ();
		} else {
			start_transport ();
		}

	} else {

		if (!get_record_enabled() && Config->get_stop_at_session_end() && _transport_frame >= current_end_frame()) {
			return;
		}

		if ((synced_to_jack()) && speed != 0.0 && speed != 1.0) {
			warning << _("Global varispeed cannot be supported while Ardour is connected to JACK transport control")
				<< endmsg;
			return;
		}

		if (actively_recording()) {
			return;
		}

		if (speed > 0.0f && _transport_frame == current_end_frame()) {
			return;
		}

		if (speed < 0.0f && _transport_frame == 0) {
			return;
		}
		
		clear_clicks ();

		/* if we are reversing relative to the current speed, or relative to the speed
		   before the last stop, then we have to do extra work.
		*/

		if ((_transport_speed && speed * _transport_speed < 0.0f) || (_last_transport_speed * speed < 0.0f)) {
			post_transport_work = PostTransportWork (post_transport_work | PostTransportReverse);
		}
		
		_last_transport_speed = _transport_speed;
		_transport_speed = speed;
		
		for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
			if ((*i)->realtime_set_speed ((*i)->speed(), true)) {
				post_transport_work = PostTransportWork (post_transport_work | PostTransportSpeed);
			}
		}
		
		if (post_transport_work & (PostTransportSpeed|PostTransportReverse)) {
			schedule_butler_transport_work ();
		}
	}
}

void
Session::stop_transport (bool abort)
{
	if (_transport_speed == 0.0f) {
		return;
	}

	if (actively_recording() && !(transport_sub_state & StopPendingCapture) && 
	    _worst_output_latency > current_block_size) 
	{
		
		/* we need to capture the audio that has still not yet been received by the system
		   at the time the stop is requested, so we have to roll past that time.

		   we want to declick before stopping, so schedule the autostop for one
		   block before the actual end. we'll declick in the subsequent block,
		   and then we'll really be stopped.
		*/
		
		Event *ev = new Event (Event::StopOnce, Event::Replace, 
				       _transport_frame + _worst_output_latency - current_block_size,
				       0, 0, abort);
		
		merge_event (ev);
		transport_sub_state |= StopPendingCapture;
		pending_abort = abort;
		return;
	} 

	if ((transport_sub_state & PendingDeclickOut) == 0) {
		transport_sub_state |= PendingDeclickOut;
		/* we'll be called again after the declick */
		return;
	}

	realtime_stop (abort);
	schedule_butler_transport_work ();
}

void
Session::start_transport ()
{
	_last_roll_location = _transport_frame;

	/* if record status is Enabled, move it to Recording. if its
	   already Recording, move it to Disabled. 
	*/

	switch (record_status()) {
	case Enabled:
		if (!punch_in) {
			enable_record ();
		}
		break;

	case Recording:
		disable_record (false);
		break;

	default:
		break;
	}

	if (!synced_to_jack() || _exporting) {
		actually_start_transport ();
	} else {
		waiting_to_start = true;
	}
}

void
Session::actually_start_transport ()
{
	waiting_to_start = false;

	transport_sub_state |= PendingDeclickIn;
	_transport_speed = 1.0;
	
	for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
		(*i)->realtime_set_speed ((*i)->speed(), true);
	}

	send_mmc_in_another_thread (MIDI::MachineControl::cmdDeferredPlay, 0);
	
	TransportStateChange (); /* EMIT SIGNAL */
}

void
Session::post_transport ()
{
	if (post_transport_work & PostTransportAudition) {
		if (auditioner && auditioner->active()) {
			process_function = &Session::process_audition;
		} else {
			process_function = &Session::process_with_events;
		}
	}

	if (post_transport_work & PostTransportStop) {

		transport_sub_state = 0;
	}

	if (post_transport_work & PostTransportLocate) {

		if ((auto_play && !_exporting) || (post_transport_work & PostTransportRoll)) {
			
			start_transport ();
			
		} else {
			transport_sub_state = 0;
		}
	}

	set_next_event ();

	post_transport_work = PostTransportWork (0);
}

void
Session::set_rf_speed (float speed)
{
	rf_speed = speed;
	cumulative_rf_motion = 0;
	reset_rf_scale (0);
}

void
Session::reset_rf_scale (jack_nframes_t motion)
{
	cumulative_rf_motion += motion;

	if (cumulative_rf_motion < 4 * _current_frame_rate) {
		rf_scale = 1;
	} else if (cumulative_rf_motion < 8 * _current_frame_rate) {
		rf_scale = 4;
	} else if (cumulative_rf_motion < 16 * _current_frame_rate) {
		rf_scale = 10;
	} else {
		rf_scale = 100;
	}

	if (motion != 0) {
		set_dirty();
	}
}

int
Session::set_slave_source (SlaveSource src, jack_nframes_t frame)
{
	bool reverse = false;
	bool non_rt_required = false;

	if (_transport_speed) {
		error << _("please stop the transport before adjusting slave settings") << endmsg;
		/* help out non-MVC friendly UI's by telling them the slave type changed */
		 ControlChanged (SlaveType); /* EMIT SIGNAL */
		return 0;
	}

	if (src == _slave_type) {
		return 0;
	} 

// 	if (src == JACK && Config->get_jack_time_master()) {
// 		return -1;
// 	}
	
	if (_slave) {
		delete _slave;
		_slave = 0;
		_slave_type = None;
	}

	if (_transport_speed < 0.0) {
		reverse = true;
	}

	switch (src) {
	case None:
		stop_transport ();
		break;

	case MTC:
		if (_mtc_port) {
			try {
				_slave = new MTC_Slave (*this, *_mtc_port);
			}

			catch (failed_constructor& err) {
				return -1;
			}

		} else {
			error << _("No MTC port defined: MTC slaving is impossible.") << endmsg;
			return -1;
		}
		_desired_transport_speed = _transport_speed;
		break;
		
	case JACK:
		_slave = new JACK_Slave (_engine.jack());
		_desired_transport_speed = _transport_speed;
		break;
	};
	
	_slave_type = src;

	for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
		if (!(*i)->hidden()) {
			if ((*i)->realtime_set_speed ((*i)->speed(), true)) {
				non_rt_required = true;
			}
			(*i)->set_slaved (_slave);
		}
	}

	if (reverse) {
		reverse_diskstream_buffers ();
	}

	if (non_rt_required) {
		post_transport_work = PostTransportWork (post_transport_work | PostTransportSpeed);
		schedule_butler_transport_work ();
	}

	set_dirty();
	ControlChanged (SlaveType); /* EMIT SIGNAL */
	
	return 0;
}

void
Session::reverse_diskstream_buffers ()
{
	post_transport_work = PostTransportWork (post_transport_work | PostTransportReverse);
	schedule_butler_transport_work ();
}

void
Session::set_diskstream_speed (DiskStream* stream, float speed)
{
	if (stream->realtime_set_speed (speed, false)) {
		post_transport_work = PostTransportWork (post_transport_work | PostTransportSpeed);
		schedule_butler_transport_work ();
		set_dirty ();
	}
}

void
Session::set_audio_range (list<AudioRange>& range)
{
	Event *ev = new Event (Event::SetAudioRange, Event::Add, Event::Immediate, 0, 0.0f);
	ev->audio_range = range;
	queue_event (ev);
}

void
Session::request_play_range (bool yn)
{
	Event* ev = new Event (Event::SetPlayRange, Event::Add, Event::Immediate, 0, 0.0f, yn);
	queue_event (ev);
}

void
Session::set_play_range (bool yn)
{
	/* Called from event-processing context */

	if (_play_range != yn) {
		_play_range = yn;
		setup_auto_play ();

		if (!_play_range) {
			/* stop transport */
			Event* ev = new Event (Event::SetTransportSpeed, Event::Add, Event::Immediate, 0, 0.0f, false);
			merge_event (ev);
		}

 		 ControlChanged (PlayRange); /* EMIT SIGNAL */
	}
}

void
Session::setup_auto_play ()
{
	/* Called from event-processing context */

	Event* ev;
	
	_clear_event_type (Event::RangeStop);
	_clear_event_type (Event::RangeLocate);

	if (!_play_range) {
		return;
	}

	list<AudioRange>::size_type sz = current_audio_range.size();
	
	if (sz > 1) {
		
		list<AudioRange>::iterator i = current_audio_range.begin(); 
		list<AudioRange>::iterator next;
		
		while (i != current_audio_range.end()) {
			
			next = i;
			++next;
			
			/* locating/stopping is subject to delays for declicking.
			 */
			
			jack_nframes_t requested_frame = (*i).end;
			
			if (requested_frame > current_block_size) {
				requested_frame -= current_block_size;
			} else {
				requested_frame = 0;
			}
			
			if (next == current_audio_range.end()) {
				ev = new Event (Event::RangeStop, Event::Add, requested_frame, 0, 0.0f);
			} else {
				ev = new Event (Event::RangeLocate, Event::Add, requested_frame, (*next).start, 0.0f);
			}
			
			merge_event (ev);
			
			i = next;
		}
		
	} else if (sz == 1) {
		
		ev = new Event (Event::RangeStop, Event::Add, current_audio_range.front().end, 0, 0.0f);
		merge_event (ev);
		
	} 

	/* now start rolling at the right place */
	
	ev = new Event (Event::LocateRoll, Event::Add, Event::Immediate, current_audio_range.front().start, 0.0f, false);
	merge_event (ev);
}

void
Session::request_bounded_roll (jack_nframes_t start, jack_nframes_t end)
{
	request_stop ();
	Event *ev = new Event (Event::StopOnce, Event::Replace, Event::Immediate, end, 0.0);
	queue_event (ev);
	request_locate (start, true);
}

void
Session::engine_halted ()
{
	/* there will be no more calls to process(), so
	   we'd better clean up for ourselves, right now.

	   but first, make sure the butler is out of 
	   the picture.
	*/

	atomic_set (&butler_should_do_transport_work, 0);
	post_transport_work = PostTransportWork (0);
	stop_butler ();
	
	realtime_stop (false);
	non_realtime_stop (false);
	transport_sub_state = 0;

	TransportStateChange (); /* EMIT SIGNAL */
}


void
Session::xrun_recovery ()
{
	if (Config->get_stop_recording_on_xrun() && actively_recording()) {

		 HaltOnXrun (); /* EMIT SIGNAL */

		/* it didn't actually halt, but we need
		   to handle things in the same way.
		*/

		engine_halted();
	} 
}

void
Session::update_latency_compensation (bool with_stop, bool abort)
{
	bool update_jack = false;

	if (_state_of_the_state & Deletion) {
		return;
	}

	RWLockMonitor lm (route_lock, false, __LINE__, __FILE__);
	RWLockMonitor lm2 (diskstream_lock, false, __LINE__, __FILE__);
	_worst_track_latency = 0;

	for (RouteList::iterator i = routes.begin(); i != routes.end(); ++i) {
		if (with_stop) {
			(*i)->transport_stopped (abort, (post_transport_work & PostTransportLocate), 
						 (!(post_transport_work & PostTransportLocate) || pending_locate_flush));
		}

		jack_nframes_t old_latency = (*i)->signal_latency ();
		jack_nframes_t track_latency = (*i)->update_total_latency ();

		if (old_latency != track_latency) {
			update_jack = true;
		}
		
		if (!(*i)->hidden() && ((*i)->active())) {
			_worst_track_latency = max (_worst_track_latency, track_latency);
		}
	}

	for (RouteList::iterator i = routes.begin(); i != routes.end(); ++i) {
		(*i)->set_latency_delay (_worst_track_latency);
	}

	/* tell JACK to play catch up */

	if (update_jack) {
		_engine.update_total_latencies ();
	}

	set_worst_io_latencies (false);

	/* reflect any changes in latencies into capture offsets
	*/
	
	for (DiskStreamList::iterator i = diskstreams.begin(); i != diskstreams.end(); ++i) {
		(*i)->set_capture_offset ();
	}
}

void
Session::update_latency_compensation_proxy (void* ignored)
{
	update_latency_compensation (false, false);
}
