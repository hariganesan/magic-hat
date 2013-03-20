// Hari Ganesan 2/8/13
// Bridge elements library file

#include "SDL/SDL.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

const int BID_BUTTON_WIDTH = 50;
const int BID_BUTTON_HEIGHT = 25;

class Button {
	SDL_Rect box; // button attributes
	SDL_Rect *clip; // part of sprite sheet
public:
	Button(int x, int y, int w, int h);
	bool handleEvents(double x, double y);
	void show();
};