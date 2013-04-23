// Hari Ganesan 3/21/13
// Tutorial: CardGame extension

#include "CardGame.hpp"

bool CardGame::loadSlides(const char *file) {
	// parse JSON
	/*Json::Reader reader;
	if (!reader.parse(lesson, slides)) {
		cerr << "error: parsing JSON slides" << endl;
		return false;
	}*/

	ifstream is(file);
	Value value;
	read_stream(is, value);
	slides = value.get_array();


	return true;
}

void CardGame::displaySlide(int slideNumber) {
	//Json::Value currentSlide = slides[slideNumber];
  const Object& currentSlide = slides[slideNumber].get_obj();


	// draw box

	// draw navigation

	// draw info
}