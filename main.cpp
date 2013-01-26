// Hari Ganesan 1/16/13
// magic-hat: for card games (bridge)

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_opengl.h"
#include "SDL_ttf/SDL_ttf.h"
#include <iostream>
#include <string>
#include "Player.h"

// window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// font
TTF_Font *font;
const char *fontpath = "chintzy.ttf";

// music
Mix_Music *music = NULL;
const char *musicpath = "nonst.mid";

using namespace std;

void runGame();
void render(CardGame *g);
void SDL_GL_RenderText(const char *text, SDL_Color color, SDL_Rect *location);
void toggleMusic(); // toggles music on and off

int main(int argc, char **argv) {
	// initialize sdl, ttf, and opengl
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// initialize window properties
	SDL_WM_SetCaption("Magic Hat", NULL);
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL);
	glClearColor(0, 0, 0, 1); // RGBA
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // viewable part of the window
	glShadeModel(GL_SMOOTH); // add a gradient
	glMatrixMode(GL_PROJECTION); // 2D drawing
	glLoadIdentity(); // save state
	glDisable(GL_DEPTH_TEST); // disable 3D drawing

	//initialize audio properties
	int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16;
  int audio_channels = 2;
  int audio_buffers = 4096;
  
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    exit(1);
  } else {
  	toggleMusic();
  }

	runGame();

	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void runGame() {
	font = TTF_OpenFont(fontpath, 16);
	//SDL_Color fontColor = {200, 200, 200};
	bool isRunning = true;
	int playerTurn = 0;
	CardGame *g = new CardGame();
	SDL_Event event;

	for (int i = 0; i < NUM_PLAYERS; i++) {
		g->fillHand(i);
	}

	//g->playRandomCard(0);
	//g->playRandomCard(1);
	//g->playRandomCard(2);

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || 
				 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
				isRunning = false;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_m) {
				toggleMusic();
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) {
				g->playRandomCard(playerTurn);
				if (++playerTurn >= 4) {
					playerTurn = 0;
				}
			}
		}
		
		render(g);
	}
}

void render(CardGame *g) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// TODO: change to 0,1 for depth
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1); // set matrix
	SDL_Color fontColor = {200, 200, 200};
	SDL_Rect location;
	Player *p;

	////////////////
	// BEGIN DRAWING
	////////////////

	// HANDS

	for (int i = 0; i < NUM_PLAYERS; i++) {
		p = g->getPlayer(i);	

		location.x = 50;
		location.y = i*50+400;

		for (int i = 0; i < FULL_HAND_LENGTH; i++) {
			if (p->hand[i] != NULL) {
				SDL_GL_RenderText(g->getNumber(p->hand[i]->number), fontColor, &location);
				location.x += 20;
				
				SDL_GL_RenderText(g->getSuit(p->hand[i]->suit), fontColor, &location);
				location.x += 30;
			}	
		}
	}

	// FELT

	Card** felt = g->getFelt();
	location.x = 200;
	location.y = 200;

	for (int i = 0; i < NUM_PLAYERS; i++) {
		if (felt[i] != NULL) {
			SDL_GL_RenderText(g->getNumber(felt[i]->number), fontColor, &location);
			location.x += 20;
				
			SDL_GL_RenderText(g->getSuit(felt[i]->suit), fontColor, &location);
			location.x += 40;
		}
	}

	////////////////
	// END DRAWING
	////////////////

	glPopMatrix();
	SDL_GL_SwapBuffers();
	SDL_Delay(33); // frame rate 30ms
	return;
}

void SDL_GL_RenderText(const char *text, SDL_Color color, SDL_Rect *location) {
	SDL_Surface *initial;
	SDL_Surface *intermediary;
	//SDL_Rect rect;
	int w,h;
	GLuint texture;
	
	// Use SDL_TTF to render our text 
	initial = TTF_RenderText_Blended(font, text, color);
	
	// Convert the rendered text to a known format 
	w = initial->w;
	h = initial->h;
	
	intermediary = SDL_CreateRGBSurface(0, w, h, 32, 
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(initial, 0, intermediary, 0);
	
	// Tell GL about our new texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, 
			GL_UNSIGNED_BYTE, intermediary->pixels );
	
	// GL_NEAREST looks horrible, if scaled... 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

	// prepare to render our texture 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	// Draw a quad at location 
	glBegin(GL_QUADS);
		// Recall that the origin is in the lower-left corner
		//  That is why the TexCoords specify different corners
		//  than the Vertex coors seem to. 
		glTexCoord2f(0.0f, 0.0f); 
			glVertex2f(location->x    , location->y);
		glTexCoord2f(1.0f, 0.0f); 
			glVertex2f(location->x + w, location->y);
		glTexCoord2f(1.0f, 1.0f); 
			glVertex2f(location->x + w, location->y + h);
		glTexCoord2f(0.0f, 1.0f); 
			glVertex2f(location->x    , location->y + h);
	glEnd();
	
	// Bad things happen if we delete the texture before it finishes 
	glFinish();
	
	// return the deltas in the unused w,h part of the rect 
	location->w = initial->w;
	location->h = initial->h;
	
	// Clean up 
	SDL_FreeSurface(initial);
	SDL_FreeSurface(intermediary);
	glDeleteTextures(1, &texture);
}

void toggleMusic() {
	if (music == NULL) {
		music = Mix_LoadMUS(musicpath);

		// play infinite times
		Mix_PlayMusic(music, -1);
	} else {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}
}
