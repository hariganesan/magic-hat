// Hari Ganesan 1/17/13
// player/cardgame class for magic-hat

#include "Player.h"

CardGame::CardGame() {
	// keep track of seeded numbers
	srand(time(NULL));

	for (int i = 0; i < NUM_PLAYERS; i++) {
		Player *newPlayer = new Player(i);
		players[i] = newPlayer;
		felt[i] = NULL;
	}

	// generate random number list 1-52
	int numArray[DECK_SIZE];
	int randNumArray[DECK_SIZE];
	int randNum;
	for (int i = 0; i < DECK_SIZE; i++)
		numArray[i] = i;

	for (int i = 0; i < DECK_SIZE; i++) {
		randNum = rand() % (DECK_SIZE-i);
		randNumArray[i] = numArray[randNum];

		for (int j = randNum; j < DECK_SIZE; j++)
			numArray[j] = numArray[j+1];
	}

	// fill up deck
	for (int i = 0; i < DECK_SIZE; i++) {
		randNum = randNumArray[i];
		Card *card = new Card(randNum/13, randNum % 13);
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

void CardGame::fillHand(int player) {
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		Player *p = getPlayer(player);
		Card *c = getCard();
		p->hand[i] = c;
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

void CardGame::playCard(int player, int suit, int number) {
	Card *card;
	Player *p = getPlayer(player);
	bool cardFound = false;
	int j = 0;
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i]->suit == suit && p->hand[i]->number == number) {
			// put card on felt
			while (felt[j++] != NULL)
				;

			card = p->hand[i];
			felt[j] = card;
			p->hand[i] = NULL;
			cardFound = true;
			break;
		}
	}

	if (!cardFound) {
		fprintf(stderr, "error: card not found");
		return;
	}

	// card is lead card
	if (j == 0) {
		winningCard = card;
		winningPlayer = players[player];
		//leadPlayer = player;
		leadSuit = card->suit;
	// card currently is winning trick			
	} else if (winningTrick(card)) {
		winningCard = card;
		winningPlayer = players[player];
	}

	// last card, clear hand
	if (j == NUM_PLAYERS - 1) {
		clearFelt();
	}
}

void CardGame::playCard(int player, Card *card) {
	// remove card from hand
	Player *p = getPlayer(player);
	bool cardFound = false;
	int j = 0;
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] == card) {
			// put card on felt
			while (felt[j] != NULL)
				j++;

			felt[j] = card;
			p->hand[i] = NULL;
			cardFound = true;
			break;
		}
	}

	if (!cardFound) {
		fprintf(stderr, "error: card not found");
		return;
	}

	// card is lead card
	if (j == 0) {
		winningCard = card;
		winningPlayer = getPlayer(player);
		//leadPlayer = player;
		leadSuit = card->suit;
	// card currently is winning trick			
	} else if (winningTrick(card)) {
		winningCard = card;
		winningPlayer = getPlayer(player);
	}

	// last card, clear hand
	if (j == NUM_PLAYERS - 1) {
		clearFelt();
	}
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
	cout << "clearing felt" << endl;
	winningPlayer->tricks++;
	leadPlayer = winningPlayer;
	winningPlayer = NULL;
	winningCard = NULL;

	//TODO: clear felt into discard
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
