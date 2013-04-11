// Hari Ganesan 3/7/13
// bridgegame class for magic-hat

#include "CardGame.hpp"

BridgeGame::BridgeGame(ifstream &infile) : CardGame(infile), trumpSuit(-1),
																		 nBids(0), consecutivePasses(0) {
	// set display to bidding
	display = BIDDING;

	//initialize bid history
	finalBid = NULL;
	for (int i = 0; i < MAXIMUM_BID_COUNT; i++)
		bidHistory[i] = NULL;
}

void BridgeGame::beginPlay() {
	display = PLAYING;
	dealCards();

	// decide roles based on bids
	for (int i = 0; bidHistory[i] != NULL; i++) {
		if (bidHistory[i]->suit == finalBid->suit &&
			// make sure bid is made by player or partner!
			 (bidHistory[i]->player == finalBid->player ||
			 	bidHistory[i]->player == getPlayer(finalBid->player)->partner->name)) {
			for (int j = 0; j < NUM_PLAYERS; j++) {
				if (bidHistory[i]->player + j < NUM_PLAYERS) {
					getPlayer(bidHistory[i]->player + j)->role = j;
				} else {
					getPlayer(bidHistory[i]->player + j - 4)->role = j;
				}
			}

			break;
		}
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

// deprecated
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

// deprecated
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

void BridgeGame::setBid(int player, int number, int suit) {
	if (nBids == 0 ||
			suit == PASS || suit == DOUBLE ||
			number > finalBid->number || // next level
		 (number == finalBid->number && suit > finalBid->suit)) { // higher suit
		
		bidHistory[nBids] = new Bid();
		bidHistory[nBids]->player = player;
		bidHistory[nBids]->number = number;
		bidHistory[nBids]->suit = suit;

		// TODO: need to make decisions!
		bidHistory[nBids]->opening = false;
		bidHistory[nBids]->artificial = false;
		bidHistory[nBids]->strength = 0;

				// TODO: move to begin of playing
		if (suit != PASS && suit != DOUBLE) {
			finalBid = bidHistory[nBids];
			trumpSuit = suit;

			consecutivePasses = 0;
		} else {
			consecutivePasses++;
		}

		nBids++;

	} else {
		// spit out some error message
		cerr << "cannot bid under current bid" << endl;
	}
}
