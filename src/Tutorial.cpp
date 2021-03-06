// Hari Ganesan 3/21/13
// Tutorial: CardGame extension

#include "main/Render.hpp"

bool CardGame::loadSlides(const char *file) {
	// load json array
	ifstream is(file);
	Value v;
	read_stream(is, v);

	const Array& slideArray = v.get_array();
	for (Array::size_type j = 0; j != slideArray.size(); j++) {
		//load JSON object into Slide struct
		const Object& obj = slideArray[j].get_obj();

	  for (Object::size_type i = 0; i != obj.size(); i++) {
			const Pair& pair = obj[i];
			const string& name  = pair.name_;
			const Value&  value = pair.value_;

			if (name == "topic") {
				slides[j].topic = value.get_str();
			} else if (name == "info") {
				slides[j].info = value.get_str();
			} else if (name == "scenario") {
				slides[j].scenario = value.get_int();
			} else if (name == "nav_forward") {
				slides[j].navForward = value.get_bool();
			} else if (name == "nav_back") {
				slides[j].navBack = value.get_bool();
			} else if (name == "nav_run") {
				slides[j].navRun = value.get_int();
			} else {
				cerr << "error: unknown JSON name for some (name, value) pair" << endl;
				return false;
			}
	  }
	}

	return true;
}

void CardGame::displaySlide(int slideNumber) {
	SDL_Rect location;

  // OPENGL calls

	// draw box
	glColor3ub(0,0,0);
	glBegin(GL_QUADS);
	glVertex2f(NAV_BOX_X, NAV_BOX_Y);
	glVertex2f(NAV_BOX_X+NAV_BOX_W, NAV_BOX_Y);
	glVertex2f(NAV_BOX_X+NAV_BOX_W, NAV_BOX_Y+NAV_BOX_H);
	glVertex2f(NAV_BOX_X, NAV_BOX_Y+NAV_BOX_H);
	glEnd();

	// draw navigation
	if (slides[slideNumber].navForward) {
		glColor3ub(40,40,40);
		location.x = NAV_FOR_X+20;
		location.y = NAV_FOR_Y;
		glBegin(GL_LINE_LOOP);
		glVertex2f(NAV_FOR_X, NAV_FOR_Y);
		glVertex2f(NAV_FOR_X+NAV_BUTTON_W, NAV_FOR_Y);
		glVertex2f(NAV_FOR_X+NAV_BUTTON_W, NAV_FOR_Y+NAV_BUTTON_H);
		glVertex2f(NAV_FOR_X, NAV_FOR_Y+NAV_BUTTON_H);
		glEnd();
		SDL_GL_RenderText(this->font, "Next", TEXT_GRAY, &location);
	}
	
	if (slides[slideNumber].navBack) {
		glColor3ub(40,40,40);
		location.x = NAV_BACK_X+5;
		location.y = NAV_BACK_Y;
		glBegin(GL_LINE_LOOP);
		glVertex2f(NAV_BACK_X, NAV_BACK_Y);
		glVertex2f(NAV_BACK_X+NAV_BUTTON_W, NAV_BACK_Y);
		glVertex2f(NAV_BACK_X+NAV_BUTTON_W, NAV_BACK_Y+NAV_BUTTON_H);
		glVertex2f(NAV_BACK_X, NAV_BACK_Y+NAV_BUTTON_H);
		glEnd();
		SDL_GL_RenderText(this->font, "Previous", TEXT_GRAY, &location);
	}

	if (slides[slideNumber].navRun > 0 && scenarioRan == false) {
		glColor3ub(40,40,40);
		location.x = NAV_RUN_X+20;
		location.y = NAV_RUN_Y;
		glBegin(GL_LINE_LOOP);
		glVertex2f(NAV_RUN_X, NAV_RUN_Y);
		glVertex2f(NAV_RUN_X+NAV_BUTTON_W, NAV_RUN_Y);
		glVertex2f(NAV_RUN_X+NAV_BUTTON_W, NAV_RUN_Y+NAV_BUTTON_H);
		glVertex2f(NAV_RUN_X, NAV_RUN_Y+NAV_BUTTON_H);
		glEnd();
		SDL_GL_RenderText(this->font, "Run!", TEXT_GRAY, &location);
	}
	
	// draw info
	location.x = NAV_BOX_X+50;
	location.y = NAV_BOX_Y+50;
	SDL_GL_RenderText(this->font, slides[slideNumber].info.c_str(), TEXT_GRAY, &location);

}

void CardGame::prevSlide() {
	if (!slides[currentSlide].navBack)
		return;

	currentSlide--;
	if (slides[currentSlide].navRun > 0) {
		loadScenario();
	} else {
		cardsDealt = false;
	}
}

void CardGame::nextSlide() {
	if (!slides[currentSlide].navForward)
		return;

	currentSlide++;
	if (slides[currentSlide].navRun > 0) {
		loadScenario();
	} else {
		cardsDealt = false;
	}
}

void CardGame::loadScenario() {
	stringstream ss;
	ss << "src/scenarios/" << currentSlide << ".bridge";
	readCards(ss.str().c_str());
	for (int i = 0; i < NUM_PLAYERS; i++) {
		players[i]->role = i;
	}
	scenarioRan = false;
}

void CardGame::runScenario() {
	// DO SOMETHING COOL
	runTimer = 12*slides[currentSlide].navRun;
	scenarioRan = true;
}


void CardGame::readCards(const char *file) {
	ifstream infile;
	infile.open(file);

	if (!infile) {
		cerr << "error: unable to read file " << file << endl;
		return;
	}

	int suit, number;
	
	testing = true;
	// (player1) suit number /n suit... /n /n (player2) suit number ...
	for (int i = 0; i < NUM_PLAYERS; i++) {
		for (int j = 0; j < FULL_HAND_LENGTH; j++) {
			Player *p = getPlayer(i);

			if (infile && infile.peek() == '\n' && infile.ignore(1).peek() == '\n') {
				cout << "incomplete player" << endl;
				break; // go to next player
			} else if (infile && !(infile >> suit >> number)) {
				cerr << "error: reading cards from " << file << endl;
				return;
			}

			Card *c = new Card(suit, number);
			p->hand[j] = c;
			p->nCards++;
			p->nCardsBySuit[c->suit]++;
	}
		infile.ignore(1);
	}

	// clear felt and tricks
	cardsOnFelt = 0;
	playerTurn = 0;
	tricksTaken = 0;
	for (int i = 0; i < NUM_PLAYERS; i++) {
		felt[i] = NULL;
		getPlayer(i)->nTricks = 0;
	}

	cardsDealt = true;
}