// Hari Ganesan 3/11/13
// magic-hat: render file

#include "Render.hpp"

using namespace std;

// possible arguments for glBegin(): GL_POINTS, GL_LINES, GL_LINE_STRIP, 
// GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLYGON
void render(BridgeGame *g) {
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
				if (g->finalBid == NULL ||
						i+1 > g->finalBid->number || // next level
		 			 (i+1 == g->finalBid->number && j > g->finalBid->suit)) { // higher suit
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
		for (int i = 0; g->bidHistory[i] != NULL; i++) {
			location.x = bidder*50 + 450;
			if (g->bidHistory[i]->suit == PASS) {
				SDL_GL_RenderText("PASS", TEXT_WHITE, &location);
			} else if (g->bidHistory[i]->suit == DOUBLE) {
				SDL_GL_RenderText("DBLE", TEXT_WHITE, &location);
			} else {
				ss << g->bidHistory[i]->number;
				SDL_GL_RenderText(ss.str().c_str(), TEXT_WHITE, &location);
				location.x += 20;
				SDL_GL_RenderText(g->getSuit(g->bidHistory[i]->suit), TEXT_WHITE, &location);
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

		// FINAL BID
		
		ss << g->finalBid->number;
		location.x = 700;
		SDL_GL_RenderText(ss.str().c_str(), TEXT_RED, &location);
		location.x += 20;
		SDL_GL_RenderText(g->getSuit(g->finalBid->suit), TEXT_RED, &location);
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
