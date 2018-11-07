#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class HighscoreHandler {
	public:
		HighscoreHandler();
		void new_score(int points);
		unsigned int is_highscore(unsigned int score);
	private:
		std::string get_name();
		void update_highscores();
		std::vector<unsigned int> highscores;
};