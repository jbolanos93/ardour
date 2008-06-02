#ifndef mackie_surface_mackie_h
#define mackie_surface_mackie_h
/*
	Generated by scripts/generate-surface.rb
*/

#include "surface.h"

namespace Mackie
{

class MackieButtonHandler;

class MackieSurface : public Surface
{
public:
	MackieSurface( uint32_t max_strips ) : Surface( max_strips )
	{
	}
	
	virtual void handle_button( MackieButtonHandler & mbh, ButtonState bs, Button & button );
	virtual void init_controls();
};

}

#endif
