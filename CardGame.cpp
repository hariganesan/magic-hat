// Hari Ganesan 1/17/13
// cardgame class for magic-hat

#include "CardGame.hpp"

CardGame::CardGame() : winningPlayer(NULL), trumpSuit(-1), turn(0), nBids(0) {
	// set display to bidding
	display = BIDDING;
	bid[0] = -1;
	bid[1] = -1;

	//initialize bid history
	for (int i = 0; i < 60; i++) {
		bidHistory[i][0] = -1;
		bidHistory[i][1] = -1;
	}

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

void CardGame::playCard(int player, Card *card) {
	if (!card) {
		cerr << "error: no card requested" << endl;
		return;
	}

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
			p->nCards--;
			p->nCardsBySuit[card->suit]--;
			discardCardsBySuit[card->suit]++;
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

	if (++turn == NUM_PLAYERS)
		turn = 0;
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
	if (nBids == 0 ||
			suit == PASS || suit == DOUBLE ||
			number > bid[0] || // next level
		 (number == bid[0] && suit > bid[1])) { // higher suit
		
		// TODO: move to begin of playing
		if (suit != PASS && suit != DOUBLE) {
			bid[0] = number;
			bid[1] = suit;
			trumpSuit = suit;
		}
		
		bidHistory[nBids][0] = number;
		bidHistory[nBids++][1] = suit;
	} else {
		// spit out some error message
		cerr << "cannot bid under current bid" << endl;
	}
}

Card *CardGame::chooseCard(int player)  {
	Player *p = getPlayer(player);
	Player *d = p->partner;
	int trumpsLeft = 13 - discardCardsBySuit[trumpSuit];

	if (turn == 0) {
	//	if (p->role == DECLARER) {
			// remember to set in player class!
			// i have trumps and others still have trumps,
			// so play lowest trump suit
			if (p->nCardsBySuit[trumpSuit] > 0 &&
					trumpsLeft - p->nCardsBySuit[trumpSuit] - d->nCardsBySuit[trumpSuit] > 0) {
				return chooseLowest(player, trumpSuit);
			// TODO: let partner rough trump
			 //else if (d->nCardsBySuit[trumpSuit] > 0 && (suit = ))
		} else {
			return chooseJunk(player);
		}
	//	}
	} else if (turn == 1) {
		// TODO: finesses
		// play lowest card of lead suit
		if (p->nCardsBySuit[leadSuit] > 0) {
			return chooseLowest(player, leadSuit);
		// rough a trick
		} else if (p->nCardsBySuit[trumpSuit] > 0) {
			return chooseLowest(player, trumpSuit);
		// discard junk
		} else {
			return chooseJunk(player);
		}
	} else if (turn == 2) {
		// play highest card of lead suit
		if (p->nCardsBySuit[leadSuit] > 0) {
			return chooseHighest(player, leadSuit);
		// rough a trick (if your partner isn't winning)
		} else if (d != winningPlayer && p->nCardsBySuit[trumpSuit] > 0) {
			return chooseLowestWinning(player, trumpSuit);
		// discard junk
		} else {
			return chooseJunk(player);
		}
	} else if (turn == 3) {
		// play highest card of lead suit
		if (p->nCardsBySuit[leadSuit] > 0) {
			return chooseHighest(player, leadSuit);
		// rough a trick (if your partner isn't winning)
		// TODO: rough a roughed trick
		} else if (d != winningPlayer && p->nCardsBySuit[trumpSuit] > 0) {
			return chooseLowestWinning(player, trumpSuit);
		// discard junk
		} else {
			return chooseJunk(player);
		}			
	}

	return NULL;
} 

Card *CardGame::chooseLowest(int player, int suit) {
	Player *p = getPlayer(player);
	Card *lowestSoFar = NULL;

	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] == NULL)
			continue;
		else if (p->hand[i]->suit == suit && 
						(lowestSoFar == NULL || p->hand[i]->number < lowestSoFar->number))
			lowestSoFar = p->hand[i];
	}

	return lowestSoFar;
}

Card *CardGame::chooseLowestWinning(int player, int suit) {
	Player *p = getPlayer(player);
	Card *lowestSoFar = NULL;

	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] == NULL)
			continue;
		else if (p->hand[i]->suit == suit &&
						 winningTrick(p->hand[i]) &&
						(lowestSoFar == NULL || p->hand[i]->number < lowestSoFar->number))
			lowestSoFar = p->hand[i];
	}
	
	if (!lowestSoFar)
		return chooseJunk(player);

	return lowestSoFar;
}

Card *CardGame::chooseHighest(int player, int suit) {
	Player *p = getPlayer(player);
	Card *highestSoFar = NULL;

	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] == NULL)
			continue;
		else if (p->hand[i]->suit == suit && 
						(highestSoFar == NULL || p->hand[i]->number > highestSoFar->number))
			highestSoFar = p->hand[i];
	}

	return highestSoFar;
}

Card *CardGame::chooseJunk(int player) {
	Player *p = getPlayer(player);

	// find longest suit
	int longestSuit = -1;
	int longestSuitLength = 1;

	for (int i = 0; i < 4; i++) {
		if (i == trumpSuit)
			continue;

		if (p->nCardsBySuit[i] >= longestSuitLength) {
			longestSuit = i;
			longestSuitLength = p->nCardsBySuit[i];
		}
	}

	// only trumps left
	if (longestSuit == -1)
		return chooseLowest(player, trumpSuit);

	return chooseLowest(player, longestSuit);
}
