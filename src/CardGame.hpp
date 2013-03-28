// Hari Ganesan 1/24/13
// CardGame library file

#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

const int FULL_HAND_LENGTH = 13;
const int DECK_SIZE = 52;
const int NUM_PLAYERS = 4;
const int MAXIMUM_BID_COUNT = 60;

enum {
	SPADES,
	HEARTS,
	DIAMONDS,
	CLUBS,
	NOTRUMP,
	PASS,
	DOUBLE,
	REDOUBLE
};

enum {
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

enum {
	DECLARER,
	DEFENDER_ONE,
	DUMMY,
	DEFENDER_TWO
};

enum {
	BIDDING,
	PLAYING
};

struct Card {
	int suit;
	int number;

	Card(int s, int n) {
		suit = s;
		number = n;
	}
};

struct Bid {
	int suit;
	int number;
	int player;
	int round;
	
	//bool dble;
	//bool redble;
	//bool pass;

	bool opening;
	bool artificial;
	int strength;
};

class Player {
public:
	Card *hand[FULL_HAND_LENGTH];
	int name;
	int role;
	int difficulty;
	Player *partner;

	// keep track of cards for each suit
	int nCards;
	int nCardsBySuit[4];
	int nTricks;
	int hcp;

	Player(int n) : role(-1), difficulty(0), nCards(0), nTricks(0), hcp(0) {
		name = n;
		partner = NULL;

		for (int i = 0; i < 4; i++) {
			nCardsBySuit[i] = 0;
		}

		for (int i = 0; i < FULL_HAND_LENGTH; i++) {
			hand[i] = NULL;			
		}
	}
};

class CardGame {
protected:
	Player *players[NUM_PLAYERS];
	Player *winningPlayer; // player currently winning hand
	Card *winningCard; // card currently winning trick
	int leadSuit;
	int trumpSuit;
	int score[2];
	int turn; // player whose turn it is
	int tricksTaken; // 0-12
	Card *deck[DECK_SIZE];
	Card *discard[DECK_SIZE];
	int discardCardsBySuit[4];
	Card *felt[NUM_PLAYERS];

public:
	int display;
	Player *dealer;
	Player *leadPlayer;

	CardGame();
	~CardGame();
	void beginPlay();
	void dealCards();
	Card *getCard();
	const char *getSuit(int suit);
	const char *getNumber(int number);
	Player *getPlayer(int player);
	Card **getFelt();
	void clearFelt();
	void printHand(int player);
	void drawHand(int player, int y_location);
};

class BridgeGame: public CardGame {
	int leadSuit;
	int trumpSuit;
public:
	int nBids;
	Bid *finalBid;
	Bid *bidHistory[MAXIMUM_BID_COUNT];
	int consecutivePasses;

	BridgeGame();
	void beginPlay();
	void playCard(int player, Card *card);
	bool winningTrick(Card *card); // checks to see if card is winning trick
	bool playRandomCard(int player);
	bool playRandomLegalCard(int player);
	void setBid(int player, int number, int suit);
	Card *chooseCard(int player);
	Card *chooseLowest(int player, int suit);
	Card *chooseLowestWinning(int player, int suit);
	Card *chooseHighest(int player, int suit);
	Card *chooseJunk(int player);
	int chooseLongestSuit(int player);
	Card *chooseNthHighestCardBySuit(int player, int suit, int n);
	int choosePreferredSuit(int player);
};
