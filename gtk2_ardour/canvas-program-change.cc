#include "canvas-program-change.h"
#include <iostream>
#include "ardour_ui.h"

using namespace Gnome::Canvas;
using namespace std;

CanvasProgramChange::CanvasProgramChange(
		MidiRegionView&                       region,
		Group&                                parent,
		boost::shared_ptr<Evoral::Event>      event,
		double                                height,
		double                                x,
		double                                y)
	: Group(parent, x, y)
	, _region(region)
	, _event(event)
	, _text(0)
	, _line(0)
	, _rect(0)
{
	char pgm_str[4];
	snprintf(pgm_str, 4, "%d", (int)(((Evoral::MIDIEvent*)event.get())->pgm_number()));
	_text = new Text(*this, 0.0, 0.0, pgm_str);
	_text->property_justification() = Gtk::JUSTIFY_CENTER;
	_text->property_fill_color_rgba() = ARDOUR_UI::config()->canvasvar_MidiProgramChangeOutline.get();
	double flagwidth  = _text->property_text_width()  + 10.0;
	double flagheight = _text->property_text_height() + 3.0;
	_text->property_x() = flagwidth / 2.0;
	_text->property_y() = flagheight / 2.0;
	_text->show();
	_line = new SimpleLine(*this, 0.0, 0.0, 0.0, height);
	_line->property_color_rgba() = ARDOUR_UI::config()->canvasvar_MidiProgramChangeOutline.get();
	_rect = new SimpleRect(*this, 0.0, 0.0, flagwidth, flagheight);
	_rect->property_outline_color_rgba() = ARDOUR_UI::config()->canvasvar_MidiProgramChangeOutline.get();
	_rect->property_fill_color_rgba() = ARDOUR_UI::config()->canvasvar_MidiProgramChangeFill.get();
	_text->lower_to_bottom();
	_text->raise(2);
}

CanvasProgramChange::~CanvasProgramChange()
{
	delete _line;
	delete _rect;
	delete _text;
}

