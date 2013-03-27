// Hari Ganesan 1/16/13
// magic-hat: for card games (bridge)

#include "Render.cpp"

using namespace std;

void runGame();

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
	BridgeGame *g = new BridgeGame();

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
								g->beginPlay();
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
		if (g->display == PLAYING && space) {
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
		} else if (g->display == BIDDING) {
			if (g->consecutivePasses == 3) {
				g->beginPlay();
			}
		}
		
		// RENDERING
		render(g);
	}
}
