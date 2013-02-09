// Hari Ganesan 2/8/13
// element class for magic-hat

#include "Elements.hpp"

Button::Button(int x, int y, int w, int h) {
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	//TODO: find out how to incorporate sprite sheet
	clip = NULL;
}

bool Button::handleEvents(double x, double y) {
	if(( x > box.x ) && ( x < box.x + box.w ) &&
		 ( y > box.y ) && ( y < box.y + box.h )) {
		//Set the button sprite
		//clip = &clips[ CLIP_MOUSEUP ];
		return true;
	}

	return false;
}

void Button::show() {
	;
}