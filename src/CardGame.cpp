// Hari Ganesan 1/17/13
// cardgame class for magic-hat

#include "CardGame.hpp"

CardGame::CardGame(ifstream &infile) : winningPlayer(NULL), turn(0), 
																			 tricksTaken(0), currentLesson("") {
	// initialize players
	for (int i = 0; i < NUM_PLAYERS; i++) {
		Player *newPlayer = new Player(i);
		players[i] = newPlayer;
		felt[i] = NULL;
	}

	// first player is dealer (first)
	dealer = players[3];

	// set partners
	for (int i = 0; i < NUM_PLAYERS/2; i++) {
		players[i]->partner = players[i+2];
	}
	for (int i = NUM_PLAYERS/2; i < NUM_PLAYERS; i++) {
		players[i]->partner = players[i-2];
	}

	// keep track of seeded numbers
	srand(time(NULL));

	if (!infile) {
		testing = false;
		// fill up deck (in order)
		for (int i = 0; i < DECK_SIZE; i++) {
			Card *card = new Card(i/13, i % 13);
			deck[i] = card;
		}
	} else {
		testing = true;
		// fill deck from file (to be dealt in order)
		readCardsCL(infile);
	}

	// fill up discard
	for (int i = 0; i < DECK_SIZE; i++) {
		discard[i] = NULL;
	}
}

// TODO: delete cards if alloc'd
CardGame::~CardGame() {
	delete[] players;
}

void CardGame::beginPlay() {
	display = PLAYING;

	dealCards();
}

void CardGame::dealCards() {
	int numPlayersLeft = NUM_PLAYERS;
	int playerArray[NUM_PLAYERS];
	for (int i = 0; i < NUM_PLAYERS; i++)
		playerArray[i] = i;

	for (int i = 0; i < DECK_SIZE; i++) {
		if (numPlayersLeft == 0) {
			cerr << "error: dealing cards" << endl;
			return;
		}

		Player *p;
		int randNum;

		if (!testing) {
			randNum = rand() % numPlayersLeft;
			p = getPlayer(playerArray[randNum]);
		} else {
			randNum = 0;
			p = getPlayer(playerArray[0]);
		}

		if (p->nCards == FULL_HAND_LENGTH) {
			numPlayersLeft--;
			i--;

			while (++randNum < NUM_PLAYERS) {
				playerArray[randNum - 1] = playerArray[randNum];
			}			
		} else {
			Card *c = getCard();

			int j = 0;
			while (p->hand[j] != NULL)
				j++;
			p->hand[j] = c;
			p->nCards++;
			p->nCardsBySuit[c->suit]++;
		}
	}
}

Card *CardGame::getCard() {
	int x = 0;

	while (deck[x] == NULL && x != DECK_SIZE)
		x++;

	if (x == DECK_SIZE)
		return NULL;
	
	Card *ptr = deck[x];
	deck[x] = NULL;
	return ptr;
}

const char *CardGame::getSuit(int suit) {
	if (suit == SPADES)
		return "S";
	else if (suit == HEARTS)
		return "H";
	else if (suit == DIAMONDS)
		return "D";
	else if (suit == CLUBS)
		return "C";
	else if (suit == NOTRUMP)
		return "NT";
	else
		return NULL;
}

const char *CardGame::getNumber(int number) {
	if (number == ACE)
		return "A";
	else if (number == TWO)
		return "2";
	else if (number == THREE)
		return "3";
	else if (number == FOUR)
		return "4";
	else if (number == FIVE)
		return "5";
	else if (number == SIX)
		return "6";
	else if (number == SEVEN)
		return "7";
	else if (number == EIGHT)
		return "8";
	else if (number == NINE)
		return "9";
	else if (number == TEN)
		return "10";
	else if (number == JACK)
		return "J";
	else if (number == QUEEN)
		return "Q";
	else if (number == KING)
		return "K";
	else
		return NULL;
}

Player *CardGame::getPlayer(int player) {
	Player *p = players[player];
	return p;
}

Card **CardGame::getFelt() {
	return felt;
}

void CardGame::clearFelt() {
	tricksTaken++; // TODO: remember to reset at start of new round!
	winningPlayer->nTricks++;
	leadPlayer = winningPlayer;
	winningPlayer = NULL;
	winningCard = NULL;
	leadSuit = -1;

	//clear felt into discard
	int j = 0;
	while (discard[j++] != NULL) {
		if (j == DECK_SIZE) {
			return;
		}
	}

	for (int i = 0; i < NUM_PLAYERS; i++) {
		discard[j++] = felt[i];
		felt[i] = NULL;
	}
}

void CardGame::printHand(int player) {
	Player *p = getPlayer(player);
	cout << "player " << player << ": " << endl;
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] != NULL) {
			cout << "suit: " << p->hand[i]->suit; 
			cout << ", number: " << p->hand[i]->number << endl;
		}	
	}
}

void CardGame::readCardsCL(ifstream &infile) {
	int suit, number;
	
	// suit number player1 /n etc... player2
	for (int i = 0; i < NUM_PLAYERS; i++) {
		for (int j = 0; j < FULL_HAND_LENGTH; j++) {
			if (!(infile >> number >> suit)) {
				cerr << "error: reading cards from CL" << endl;
				return;
			}

			Card *card = new Card(suit, number);
			deck[i*13+j] = card;
		}
	}
}
