// Hari Ganesan 1/24/13
// Player library file

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

const int FULL_HAND_LENGTH = 13;
const int DECK_SIZE = 52;
const int NUM_PLAYERS = 4;

enum {
	SPADES,
	HEARTS,
	DIAMONDS,
	CLUBS,
	NOTRUMP
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

struct Card {
	int suit;
	int number;

	Card(int s, int n) {
		suit = s;
		number = n;
	}
};

struct Player {
	Card *hand[FULL_HAND_LENGTH];
	int name;
	int role;
	int tricks;
	int difficulty;

	Player(int n) {
		role = 0;
		tricks = 0;
		difficulty = 0;
		name = n;

		for (int i = 0; i < FULL_HAND_LENGTH; i++) {
			hand[i] = NULL;			
		}
	}
};

class CardGame {
	Player *players[NUM_PLAYERS];
	Player *leadPlayer;
	Player *winningPlayer;
	Card *winningCard;
	int leadSuit;
	int trumpSuit;
	int bid[2];
	int score[2];
	Card *deck[DECK_SIZE];
	Card *felt[NUM_PLAYERS];

public:
	CardGame();
	~CardGame();
	void fillHand(int player);
	Card *getCard();
	Player *getPlayer(int player);
	void playCard(int player, int suit, int number);
	void playCard(int player, Card *card);
	bool winningTrick(Card *card);
	void clearFelt();
	void printHand(int player);
	void drawHand(int player, int y_location);
	bool playRandomCard(int player);
};
