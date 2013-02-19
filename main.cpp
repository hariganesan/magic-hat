// Hari Ganesan 1/16/13
// magic-hat: for card games (bridge)

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_opengl.h"
#include "SDL_ttf/SDL_ttf.h"
#include <iostream>
#include <string>
#include "CardGame.hpp"
#include "Elements.hpp"

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

using namespace std;

void runGame();
void render(CardGame *g);
void SDL_GL_RenderText(const char *text, SDL_Color color, SDL_Rect *location);
void SDL_GL_RenderPNG(const char *image, SDL_Rect *location);
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
	glClearColor(0, 0.4, 0.1, 1); // RGBA
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
  	//toggleMusic();
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
	int playerTurn = 0;
	int cardsOnFelt = 0;
	CardGame *g = new CardGame();

	// make a 2d array of bidding buttons
	Button *bids[5][7];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			bids[i][j] = new Button(100+i*BID_BUTTON_WIDTH,100+j*BID_BUTTON_HEIGHT,
														  BID_BUTTON_WIDTH, BID_BUTTON_HEIGHT);
		}
	}

	// pass
	Button *BTN_pass = new Button(150, 300, 50, 25);
	Button *BTN_double = new Button(250, 300, 50, 25);

	// navigation buttons
	Button *BTN_play = new Button(650, 400, 50, 25);

	// event bools
	SDL_Event event;
	bool isRunning = true;
	bool space = false;
	bool bidSet = false;

	while (isRunning) {
		// EVENTS
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT: isRunning = false; break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_q: isRunning = false; break;
						case SDLK_m: toggleMusic(); break;
						case SDLK_SPACE: space = true; break;
						default: ;
					}
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT && g->display == BIDDING) {
						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 7; j++) {
								if (bids[i][j]->handleEvents(event.button.x, event.button.y)) {
									g->setBid(j+1, i);
									bidSet = true;
								}
							}
						}
						if (BTN_play->handleEvents(event.button.x, event.button.y)) {
							if (bidSet) {
								g->display = PLAYING;
								g->dealCards();
							}
						} else if (BTN_pass->handleEvents(event.button.x, event.button.y)) {
							g->setBid(-1, PASS);
							bidSet = true;
						} else if (BTN_double->handleEvents(event.button.x, event.button.y)) {
							g->setBid(-1, DOUBLE);
							bidSet = true;
						}
					}
					break;
				default: ;
			}
		}

		// LOGIC
		if (space && g->display == PLAYING) {
			if (cardsOnFelt == 4) {
				g->clearFelt();
				cardsOnFelt = 0;
				playerTurn = g->leadPlayer->name;
			} else {
				//g->playRandomLegalCard(playerTurn);
				Card *c = g->chooseCard(playerTurn);
				g->playCard(playerTurn, c);
				cardsOnFelt++;
				
				if (++playerTurn >= 4) {
					playerTurn = 0;
				}
			}

			space = false;
		}
		
		// RENDERING
		render(g);
	}
}

// possible arguments for glBegin(): GL_POINTS, GL_LINES, GL_LINE_STRIP, 
// GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLYGON
void render(CardGame *g) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// TODO: change to 0,1 for depth
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1); // set matrix
	SDL_Color TEXT_WHITE = {220, 220, 220};
	SDL_Color TEXT_GRAY = {150, 150, 150};
	//SDL_Color TEXT_BLACK = {20, 20, 20};
	SDL_Color TEXT_RED = {200, 0, 0};
	SDL_Rect location;
	Player *p;

	////////////////
	// BEGIN DRAWING
	////////////////

	// BACKGROUND
	glColor4ub(0, 100, 30, 255);
	glBegin(GL_QUADS);
	glVertex2f(MARGIN, MARGIN);
	glVertex2f(WINDOW_WIDTH - MARGIN, MARGIN);
	glVertex2f(WINDOW_WIDTH - MARGIN, WINDOW_HEIGHT - MARGIN);
	glVertex2f(MARGIN, WINDOW_HEIGHT - MARGIN);
	glEnd();

	if (g->display == BIDDING) {

		// sample card
		location.x = 50;
		location.y = 50;
		//SDL_GL_RenderPNG("assets/images/test/1.png", &location);




		// BIDDING BOX

		location.x = 100;
		location.y = 100;
		stringstream ss;
		glColor4ub(200, 200, 200, 255);
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 5; j++) {
				// draw boxes
				glBegin(GL_LINE_LOOP);
				glVertex2f(location.x, location.y);
				glVertex2f(location.x+BID_BUTTON_WIDTH, location.y);
				glVertex2f(location.x+BID_BUTTON_WIDTH, location.y+BID_BUTTON_HEIGHT);
				glVertex2f(location.x, location.y+BID_BUTTON_HEIGHT);
				glEnd();

				// render bids
				ss << i+1;
				if (i+1 > g->bid[0] || // next level
		 			 (i+1 == g->bid[0] && j > g->bid[1])) { // higher suit
					SDL_GL_RenderText(ss.str().c_str(), TEXT_WHITE, &location);
					location.x += 20;
					SDL_GL_RenderText(g->getSuit(j), TEXT_WHITE, &location);
					location.x += 30;
				} else {
					// grayed out bids
					SDL_GL_RenderText(ss.str().c_str(), TEXT_GRAY, &location);
					location.x += 20;
					SDL_GL_RenderText(g->getSuit(j), TEXT_GRAY, &location);
					location.x += 30;					
				}
				ss.str("");
				ss.clear();
			}
			location.y += BID_BUTTON_HEIGHT;
			location.x -= 5*(20+30);
		}

		// BID TABLE
		location.x = 450;
		location.y = 100;
		SDL_GL_RenderText("W", TEXT_RED, &location);
		location.x += 50;
		SDL_GL_RenderText("N", TEXT_RED, &location);
		location.x += 50;
		SDL_GL_RenderText("E", TEXT_RED, &location);
		location.x += 50;
		SDL_GL_RenderText("S", TEXT_RED, &location);

		int bidder = g->dealer->name;
		location.y += 30;
		for (int i = 0; ;i++) {
			if (g->bidHistory[i][1] == -1) {
				break;
			}

			location.x = bidder*50 + 450;
			if (g->bidHistory[i][1] == PASS) {
				SDL_GL_RenderText("PASS", TEXT_WHITE, &location);
			} else if (g->bidHistory[i][1] == DOUBLE) {
				SDL_GL_RenderText("DBLE", TEXT_WHITE, &location);
			} else {
				ss << g->bidHistory[i][0];
				SDL_GL_RenderText(ss.str().c_str(), TEXT_WHITE, &location);
				location.x += 20;
				SDL_GL_RenderText(g->getSuit(g->bidHistory[i][1]), TEXT_WHITE, &location);
				ss.str("");
				ss.clear();
			}
			
			if (++bidder == NUM_PLAYERS) {
				bidder = 0;
				location.y += 25;
			}
		}

		// NAVIGATION
		location.x = 150;
		location.y = 300;
		SDL_GL_RenderText("Pass", TEXT_WHITE, &location);		
		location.x = 250;
		location.y = 300;
		SDL_GL_RenderText("Double", TEXT_WHITE, &location);		

		location.x = 650;
		location.y = 400;
		SDL_GL_RenderText("Play!", TEXT_WHITE, &location);

	// PLAYING
	} else if (g->display == PLAYING) {

		// HANDS

		// player 0
		p = g->getPlayer(0);
		location.x = 50;
		location.y = 150;

		for (int i = 0; i < FULL_HAND_LENGTH; i++) {
			if (p->hand[i] != NULL) {
				SDL_GL_RenderText(g->getNumber(p->hand[i]->number), TEXT_WHITE, &location);
				location.x += 20;
				
				SDL_GL_RenderText(g->getSuit(p->hand[i]->suit), TEXT_WHITE, &location);
				location.y += 25;
				location.x -= 20;
			}
		}

		// qplayer 1
		p = g->getPlayer(1);
		location.x = 80;
		location.y = 50;

		for (int i = 0; i < FULL_HAND_LENGTH; i++) {
			if (p->hand[i] != NULL) {
				SDL_GL_RenderText(g->getNumber(p->hand[i]->number), TEXT_WHITE, &location);
				location.x += 20;
				
				SDL_GL_RenderText(g->getSuit(p->hand[i]->suit), TEXT_WHITE, &location);
				location.x += 30;
			}	
		}

		// player 2
		p = g->getPlayer(2);
		location.x = 700;
		location.y = 150;

		for (int i = 0; i < FULL_HAND_LENGTH; i++) {
			if (p->hand[i] != NULL) {
				SDL_GL_RenderText(g->getNumber(p->hand[i]->number), TEXT_WHITE, &location);
				location.x += 20;
				
				SDL_GL_RenderText(g->getSuit(p->hand[i]->suit), TEXT_WHITE, &location);
				location.y += 25;
				location.x -= 20;
			}	
		}

		// player 3
		p = g->getPlayer(3);
		location.x = 80;
		location.y = 550;

		for (int i = 0; i < FULL_HAND_LENGTH; i++) {
			if (p->hand[i] != NULL) {
				SDL_GL_RenderText(g->getNumber(p->hand[i]->number), TEXT_WHITE, &location);
				location.x += 20;
				
				SDL_GL_RenderText(g->getSuit(p->hand[i]->suit), TEXT_WHITE, &location);
				location.x += 30;
			}	
		}

		// FELT

		Card** felt = g->getFelt();

		int cardLocations[4][2] =
		{{340, 250},
		{380, 220},
		{420, 250},
		{380, 280}};

		for (int i = 0; i < NUM_PLAYERS; i++) {
			if (felt[i] != NULL) {
				location.x = cardLocations[i][0];
				location.y = cardLocations[i][1];

				SDL_GL_RenderText(g->getNumber(felt[i]->number), TEXT_WHITE, &location);
				location.x += 20;
					
				SDL_GL_RenderText(g->getSuit(felt[i]->suit), TEXT_WHITE, &location);
			}
		}

		// SCORES

		location.x = 150;
		location.y = 10;
		stringstream ss;
		for (int i = 0; i < NUM_PLAYERS; i++) {
			p = g->getPlayer(i);
			ss << p->nTricks;
			SDL_GL_RenderText(ss.str().c_str(), TEXT_RED, &location);
			location.x += 150;
			ss.str("");
			ss.clear();
		}

		ss << g->bid[0];
		location.x = 700;
		SDL_GL_RenderText(ss.str().c_str(), TEXT_RED, &location);
		location.x += 20;
		SDL_GL_RenderText(g->getSuit(g->bid[1]), TEXT_RED, &location);
		ss.str("");
		ss.clear();
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
	int w,h;
	GLuint texture;

	if (!text) {
		cerr << "text not displayed" << endl;
		return;
	}
	
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

void SDL_GL_RenderPNG(const char *image, SDL_Rect *location) {
	SDL_Surface *surface;
	GLenum texture_format;
	GLint nColors;
	GLuint texture;

	int w,h;

	if ((surface = IMG_Load(image))) {
		w = surface->w;
		h = surface->h;

		// check for powers of 2
		if ((w & (w - 1)) != 0) {
			cerr << "warning: " << image << "'s width is not power of 2" << endl;
		}
		if ((h & (h - 1)) != 0) {
			cerr << "warning: " << image << "'s height is not power of 2" << endl;
		}

		// get number of channels in SDL surface
		nColors = surface->format->BytesPerPixel;
		if (nColors == 4) { // contains alpha
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
		} else if (nColors == 3) { // no alpha channel
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
		} else {
			cerr << "warning: the image is not truecolor..";
			cerr << "this will probably break" << endl;
      // this error should not go unhandled
		}

    // Have OpenGL generate a texture object handle for us
    glGenTextures( 1, &texture );

    // Bind the texture object
    glBindTexture( GL_TEXTURE_2D, texture );

    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D( GL_TEXTURE_2D, 0, nColors, w, h, 0,
                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );
	} else {
		cerr << "SDL could not load " << image << ":" << SDL_GetError() << endl;
		return;
	}    

	// Free the SDL_Surface only if it was successfully created
	if ( surface ) { 
		SDL_FreeSurface( surface );
	}

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Use nice (linear) scaling 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Use nice (linear) scaling

	glBegin (GL_QUADS);

	/*
	glNormal3f(0.0f, 0.0f, 1.0f);
	if (texturesOn) glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.3f, -3.5f, 0.0f); //bottom left

	if (texturesOn) glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.3f, -3.5f, 0.0f); //bottom right

	if (texturesOn) glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.3f, -4.5f, 0.0f); //top right

	if (texturesOn) glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.3f, -4.5f, 0.0f); //top left
*/

	glTexCoord2f(0.0f, 0.0f); 
	glVertex2f(location->x    , location->y);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex2f(location->x + w, location->y);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex2f(location->x + w, location->y + h);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex2f(location->x    , location->y + h);
	glEnd();

	glDisable(GL_TEXTURE_2D);

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
