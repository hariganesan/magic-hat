// Hari Ganesan 3/21/13
// Tutorial: CardGame extension

#include "CardGame.hpp"

struct Slide {
	string topic;
	string info;
	int scenario;
	bool navForward;
	bool navBack;
	int navRun;
};

bool CardGame::loadSlides(const char *file) {
	// load json array
	ifstream is(file);
	Value value;
	read_stream(is, value);
	slides = value.get_array();

	return true;
}

void CardGame::displaySlide(int slideNumber) {
	//load JSON object into Slide struct
  const Object& obj = slides[slideNumber].get_obj();
  Slide slide;

  for (Object::size_type i = 0; i != obj.size(); ++i) {
		const Pair& pair = obj[i];
		const string& name  = pair.name_;
		const Value&  value = pair.value_;

		if (name == "topic") {
			slide.topic = value.get_str();
		} else if (name == "info") {
			slide.info = value.get_str();
		} else if (name == "scenario") {
			slide.scenario = value.get_int();
		} else if (name == "nav_forward") {
			slide.navForward = value.get_bool();
		} else if (name == "nav_back") {
			slide.navBack = value.get_bool();
		} else if (name == "nav_run") {
			slide.navRun = value.get_int();
		} else {
			cerr << "error: unknown JSON object name for some (name, value)"; << endl;
			return;
		}
  }

	// draw box
  
	// draw navigation

	// draw info
}