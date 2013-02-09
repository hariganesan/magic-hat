// Hari Ganesan 1/17/13
// cardgame class for magic-hat

#include "CardGame.hpp"

CardGame::CardGame() {
	// set display to bidding
	display = BIDDING;
	bid[0] = -1;
	bid[1] = -1;
	trumpSuit = -1;
	winningPlayer = NULL;

	// initialize players
	for (int i = 0; i < NUM_PLAYERS; i++) {
		Player *newPlayer = new Player(i);
		players[i] = newPlayer;
		felt[i] = NULL;
	}

	// keep track of seeded numbers
	srand(time(NULL));

	// fill up deck (in order)
	for (int i = 0; i < DECK_SIZE; i++) {
		Card *card = new Card(i/13, i % 13);
		deck[i] = card;
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

		int randNum = rand() % numPlayersLeft;
		Player *p = getPlayer(playerArray[randNum]);

		if (p->numCards == FULL_HAND_LENGTH) {
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
			p->numCards++;
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

void CardGame::playCard(int player, Card *card) {
	// remove card from hand
	Player *p = getPlayer(player);
	bool cardFound = false;
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] == card) {
			// put card on felt
			if (felt[player] != NULL) {
				cerr << "error: felt already has card" << endl;
				return;
			}

			felt[player] = card;
			p->hand[i] = NULL;
			p->numCards--;
			cardFound = true;
			break;
		}
	}

	if (!cardFound) {
		cerr << "error: card not found" << endl;
		return;
	}

	// card is lead card
	if (winningPlayer == NULL) {
		winningCard = card;
		winningPlayer = getPlayer(player);
		leadSuit = card->suit;
	// card currently is winning trick			
	} else if (winningTrick(card)) {
		winningCard = card;
		winningPlayer = getPlayer(player);
	}

/*
	// last card, clear hand
	if (j == NUM_PLAYERS - 1) {
		clearFelt();
	} */
}

bool CardGame::winningTrick(Card *card) {
	// already trump
	if (winningCard->suit == trumpSuit && card->suit != trumpSuit) {
		return false;
	// first trump
	} else if (winningCard->suit != trumpSuit && card->suit == trumpSuit) {
		return true;
	// dumping card
	} else if (card->suit != leadSuit && card->suit != trumpSuit) {
		return false;
	// must be same suit
	} else if (card->number > winningCard->number) {
		return true;
	} else { // card.number < winningCard.number
		return false;
	}
}

void CardGame::clearFelt() {
	winningPlayer->tricks++;
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

bool CardGame::playRandomCard(int player) {
	Player *p = getPlayer(player);
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] != NULL) {
			playCard(player, p->hand[i]);
			return true;
		}
	}

	return false;
}

bool CardGame::playRandomLegalCard(int player) {
	Player *p = getPlayer(player);

	if (leadSuit != -1) {
		// if you have lead suit, play it
		for (int i = 0; i < FULL_HAND_LENGTH; i++) {
			if (p->hand[i] != NULL && p->hand[i]->suit == leadSuit) {
				playCard(player, p->hand[i]);
				return true;
			}
		}
	}

	// otherwise, play any card
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] != NULL) {
			playCard(player, p->hand[i]);
			return true;
		}
	}

	return false;
}

void CardGame::setBid(int number, int suit) {
	bid[0] = number;
	bid[1] = suit;
	trumpSuit = suit;
}
