// Hari Ganesan 3/21/13
// Decisions: BridgeGame extension

#include "CardGame.hpp"

Card *BridgeGame::chooseCard(int player)  {
	Player *p = getPlayer(player);
	Player *d = p->partner;
	int trumpsLeft = 13 - discardCardsBySuit[trumpSuit];

	if (p->role == DECLARER || p->role == DUMMY) {
		if (turn == 0) {
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
	} else if (p->role == DEFENDER_ONE || p->role == DEFENDER_TWO) {
		if (turn == 0) {
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
	}

	return NULL;
} 

Card *BridgeGame::chooseLowest(int player, int suit) {
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

Card *BridgeGame::chooseLowestWinning(int player, int suit) {
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

// conditional on if winning the trick
Card *BridgeGame::chooseHighest(int player, int suit) {
	Player *p = getPlayer(player);
	Card *highestSoFar = NULL;

	for (int i = 0; i < FULL_HAND_LENGTH; i++) {
		if (p->hand[i] == NULL)
			continue;
		else if (p->hand[i]->suit == suit && 
						(highestSoFar == NULL || p->hand[i]->number > highestSoFar->number))
			highestSoFar = p->hand[i];
	}

	if (winningTrick(highestSoFar))
		return highestSoFar;

	return chooseLowest(player, suit);
}

Card *BridgeGame::chooseJunk(int player) {
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
