// Hari Ganesan 3/11/13
// Render library file

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_opengl.h"
#include "SDL_ttf/SDL_ttf.h"
#include <iostream>
#include <string>
#include "../CardGame.hpp"
#include "../Elements.hpp"
#include "json_spirit_reader_template.h"

// window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MARGIN = 10;

// text colors
const SDL_Color TEXT_WHITE = {220, 220, 220};
const SDL_Color TEXT_GRAY = {150, 150, 150};
const SDL_Color TEXT_BLACK = {20, 20, 20};
const SDL_Color TEXT_RED = {200, 0, 0};

// tutorial nav buttons
const int NAV_BOX_X = 100;
const int NAV_BOX_Y = 300;
const int NAV_BOX_W = WINDOW_WIDTH-200;
const int NAV_BOX_H = 150;
const int NAV_BUTTON_W = 80;
const int NAV_BUTTON_H = 20;
const int NAV_FOR_X = 550;
const int NAV_FOR_Y = 420;
const int NAV_BACK_X = 150;
const int NAV_BACK_Y = 420;
const int NAV_RUN_X = 350;
const int NAV_RUN_Y = 420;

// hands
const int HAND_USER_X = 80;
const int HAND_USER_Y = 560;

// render functions
void render(BridgeGame *g);
void SDL_GL_RenderText(TTF_Font *font, const char *text, SDL_Color color, SDL_Rect *location);
void SDL_GL_RenderPNG(const char *image, SDL_Rect *location);
void toggleMusic(); // toggles music on and off