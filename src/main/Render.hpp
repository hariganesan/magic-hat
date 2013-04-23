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

// font
TTF_Font *font;
const char *fontpath = "assets/fonts/chintzy.ttf";

// music
Mix_Music *music = NULL;
const char *musicpath = "assets/music/senomar.mid";

void render(BridgeGame *g);
void SDL_GL_RenderText(const char *text, SDL_Color color, SDL_Rect *location);
void SDL_GL_RenderPNG(const char *image, SDL_Rect *location);
void toggleMusic(); // toggles music on and off