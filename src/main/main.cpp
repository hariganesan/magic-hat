// Hari Ganesan 1/16/13
// magic-hat: for card games (bridge)

#include "Render.cpp"

using namespace std;

// font
const char *fontpath = "assets/fonts/chintzy.ttf";

// music
Mix_Music *music = NULL;
const char *musicpath = "assets/music/senomar.mid";

void runGame(ifstream &infile);

int main(int argc, char *argv[]) {
	// check command line args
	ifstream infile;
	ofstream outfile;
	if (argc == 1) {
		infile.open(NULL);
	} else if (argc == 3 && strcmp(argv[1], "-t") == 0) {
		infile.open(argv[2]);

		if (!infile) {
			cerr << "error: unable to read file" << endl;
			return EXIT_FAILURE;
		}
	} else if (argc == 3 && strcmp(argv[1], "-g") == 0) {
		// generate (random) hands to file
		stringstream ss;
		ss << "out/" << argv[2];
		outfile.open(ss.str().c_str());
		infile.open(NULL);
		BridgeGame *g = new BridgeGame(infile);
		g->dealCards();
		for (int i = 0; i < NUM_PLAYERS; i++) {
			g->printHand(outfile, i);
			outfile << endl;
		}
		return EXIT_SUCCESS;
	} else {
		cerr << "usage: " << argv[0] << " [-t] (infile) | [-g] (outfile)" << endl;
		return EXIT_FAILURE;
	}

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

	runGame(infile);

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void runGame(ifstream &infile) {
	BridgeGame *g = new BridgeGame(infile);
	g->font = TTF_OpenFont(fontpath, 16);
	g->font32 = TTF_OpenFont(fontpath, 32);

	// make a 2d array of bidding buttons
	Button *bids[5][7];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			bids[i][j] = new Button(100+i*BID_BUTTON_WIDTH,100+j*BID_BUTTON_HEIGHT,
														  BID_BUTTON_WIDTH, BID_BUTTON_HEIGHT);
		}
	}

	// extra bid buttons
	Button *BTN_pass = new Button(150, 300, 50, 25);
	Button *BTN_double = new Button(250, 300, 50, 25);
	Button *BTN_play = new Button(650, 400, 50, 25);

	// navigation buttons
	Button *BTN_nav_back = new Button(NAV_BACK_X, NAV_BACK_Y, NAV_BUTTON_W, NAV_BUTTON_H);
	Button *BTN_nav_for = new Button(NAV_FOR_X, NAV_FOR_Y, NAV_BUTTON_W, NAV_BUTTON_H);
	Button *BTN_nav_run = new Button(NAV_RUN_X, NAV_RUN_Y, NAV_BUTTON_W, NAV_BUTTON_H);

	// menu buttons
	Button *BTN_start = new Button(500, 250, 100, 50);
	Button *BTN_tutorial = new Button(200, 250, 150, 50);

	// player card buttons
	Button *userCards[FULL_HAND_LENGTH];
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		userCards[i] = new Button(HAND_USER_X-5+i*50, HAND_USER_Y-5, 50, 20);
	}

	// event bools
	SDL_Event event;
	bool isRunning = true;
	bool space = false;
	bool bidSet = false;

	while (isRunning) {
		// EVENTS
		// TODO: change functions to variables!
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
									g->setBid(g->playerTurn, j+1, i);
									bidSet = true;
								}
							}
						}
						if (BTN_play->handleEvents(event.button.x, event.button.y)) {
							if (bidSet) {
								g->beginPlay();
							}
						} else if (BTN_pass->handleEvents(event.button.x, event.button.y)) {
							g->setBid(g->playerTurn, -1, PASS);
							bidSet = true;
						} else if (BTN_double->handleEvents(event.button.x, event.button.y)) {
							g->setBid(g->playerTurn, -1, DOUBLE);
							bidSet = true;
						}
					} else if (event.button.button == SDL_BUTTON_LEFT && g->display == MAIN) {
						if (BTN_start->handleEvents(event.button.x, event.button.y)) {
							g->display = BIDDING;
						} else if (BTN_tutorial->handleEvents(event.button.x, event.button.y)) {
							g->display = TUTORIAL;
							g->currentLesson = "src/script/lesson1.JSON";
							g->loadSlides(g->currentLesson.c_str());
							g->currentSlide = 0;
						}
					} else if (event.button.button == SDL_BUTTON_LEFT && g->display == TUTORIAL) {
						if (BTN_nav_back->handleEvents(event.button.x, event.button.y)) {
							g->prevSlide();
						} else if (BTN_nav_for->handleEvents(event.button.x, event.button.y)) {
							g->nextSlide();
						} else if (BTN_nav_run->handleEvents(event.button.x, event.button.y)) {
							if (!g->scenarioRan)
								g->runScenario();
						}
					} else if (event.button.button == SDL_BUTTON_LEFT && g->display == PLAYING) {
						if (g->playerTurn == 3) {
							Player *p = g->getPlayer(3);
							for (int i = 0, j = 0; i < FULL_HAND_LENGTH && j < FULL_HAND_LENGTH; i++) {
								while (p->hand[j] == NULL && ++j < FULL_HAND_LENGTH)
									;
								if (j >= FULL_HAND_LENGTH)
									continue;
								
								if (userCards[i]->handleEvents(event.button.x, event.button.y)) {
									g->playCard(3, p->hand[j]); // may not be i!
									g->cardsOnFelt++;
									g->playerTurn = 0;
								}

								j++;
							}
						}
					}
					break;
				default: ;
			}
		}

		// LOGIC
		if ((g->display == PLAYING && space) || 
			  (g->display == TUTORIAL && g->runTimer > 0 && g->runTimer-- % 12 == 1)) {
			if (g->cardsOnFelt == 4) {
				g->clearFelt();
				g->cardsOnFelt = 0;
				g->playerTurn = g->leadPlayer->name;
			} else {
				Card *c = g->chooseCard(g->playerTurn);
				g->playCard(g->playerTurn, c);
				g->cardsOnFelt++;
				
				if (++g->playerTurn >= 4) {
					g->playerTurn = 0;
				}
			}

			space = false;


		} else if (g->display == BIDDING) {
			// TODO: make graphic
			if (g->consecutivePasses == 3) {
				g->beginPlay();
			}
		} else if (g->display == TUTORIAL) {
			;// ???
		}

		// RENDERING
		render(g);
	}

	TTF_CloseFont(g->font);
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
