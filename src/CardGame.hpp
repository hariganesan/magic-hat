// Hari Ganesan 1/24/13
// CardGame library file

#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "SDL_ttf/SDL_ttf.h"
#include "json_spirit_reader_template.h"

using namespace std;
using namespace json_spirit;

const int FULL_HAND_LENGTH = 13;
const int DECK_SIZE = 52;
const int NUM_PLAYERS = 4;
const int MAXIMUM_BID_COUNT = 60;
const int MAX_SLIDE_COUNT = 100;

struct Slide {
	string topic;
	string info;
	int scenario;
	bool navForward;
	bool navBack;
	int navRun;
};

// suits and bids
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

// number values
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

// player roles
enum {
	DECLARER,
	DEFENDER_ONE,
	DUMMY,
	DEFENDER_TWO
};

// display types
enum {
	BIDDING,
	PLAYING,
	TUTORIAL,
	MAIN
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
	int honours;

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
	int score[2]; // running tally
	int turn; // player whose turn it is TODO: change to playerTurn
	int tricksTaken; // 0-12
	Card *deck[DECK_SIZE];
	Card *discard[DECK_SIZE];
	int discardCardsBySuit[4];
	Card *felt[NUM_PLAYERS];

public:
	int display;
	Player *dealer;
	Player *leadPlayer;
	bool testing;
	string currentLesson;
	Slide slides[MAX_SLIDE_COUNT];
	int currentSlide;
	TTF_Font *font;
	TTF_Font *font32;
	bool cardsDealt;
	int runTimer;
	int playerTurn;
	int cardsOnFelt;
	bool scenarioRan;

	CardGame(ifstream &infile);
	~CardGame();
	void beginPlay();
	void dealCards();
	Card *getCard();
	const char *getSuit(int suit);
	const char *getNumber(int number);
	Player *getPlayer(int player);
	Card **getFelt();
	void clearFelt();
	void printHand(ofstream &outfile, int player);
	void drawHand(int player, int y_location);
	void readCardsCL(ifstream &infile);
	void readCards(const char *file);
	void fillRemainingCards();
	// tutorial fns
	bool loadSlides(const char *file);
	void displaySlide(int slideNumber);
	void prevSlide();
	void nextSlide();
	void loadScenario();
	void runScenario();
};

class BridgeGame: public CardGame {
	int leadSuit;
	int trumpSuit;
public:
	int nBids;
	Bid *finalBid;
	Bid *bidHistory[MAXIMUM_BID_COUNT];
	int consecutivePasses;

	BridgeGame(ifstream &infile);
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
