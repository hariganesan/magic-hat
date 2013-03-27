// Hari Ganesan 3/7/13
// bridgegame class for magic-hat

#include "Decisions.cpp"

BridgeGame::BridgeGame() : CardGame(), trumpSuit(-1), nBids(0), consecutivePasses(0) {
	// set display to bidding
	display = BIDDING;
	bid[0] = -1;
	bid[1] = -1;

	//initialize bid history
	for (int i = 0; i < 60; i++) {
		bidHistory[i][0] = -1;
		bidHistory[i][1] = -1;
	}
}

void BridgeGame::playCard(int player, Card *card) {
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

bool BridgeGame::winningTrick(Card *card) {
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

bool BridgeGame::playRandomCard(int player) {
	Player *p = getPlayer(player);
	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] != NULL) {
			playCard(player, p->hand[i]);
			return true;
		}
	}

	return false;
}

bool BridgeGame::playRandomLegalCard(int player) {
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

void BridgeGame::setBid(int number, int suit) {
	if (nBids == 0 ||
			suit == PASS || suit == DOUBLE ||
			number > bid[0] || // next level
		 (number == bid[0] && suit > bid[1])) { // higher suit
		
		// TODO: move to begin of playing
		if (suit != PASS && suit != DOUBLE) {
			bid[0] = number;
			bid[1] = suit;
			trumpSuit = suit;

			consecutivePasses = 0;
		} else {
			consecutivePasses++;
		}
		
		bidHistory[nBids][0] = number;
		bidHistory[nBids++][1] = suit;
	} else {
		// spit out some error message
		cerr << "cannot bid under current bid" << endl;
	}
}
