#include "HighscoreHandler.h"

#include "limits.h"

HighscoreHandler::HighscoreHandler() {
	update_highscores();
}

void HighscoreHandler::new_score(int points) {
	std::string name = get_name();
	unsigned int place = is_highscore((unsigned int) points);
	std::string newhighscore = std::to_string(points) + '\t' + name;

	if (place != INT_MAX) {
		std::string line;
		unsigned int i = 0;
		std::ifstream file("HIGHSCORES.md");
		if (file.is_open()) {
			std::ofstream output("HIGHSCORES_NEW.md");
			while ( std::getline(file, line) ) {
				if (i != place+1) output << line << std::endl;
				else output << newhighscore << std::endl;
				++i;
			}
			file.close();
			output.close();
			remove("HIGHSCORES.md");
			rename("HIGHSCORES_NEW.md", "HIGHSCORES.md");
		}
	}
	std::cout << "Highscore updated! Return to the game window." << std::endl;
}

unsigned int HighscoreHandler::is_highscore(unsigned int score) {
	unsigned int i = 0;
	while ( i < highscores.size() && score < highscores.at(i) ) ++i;
	if ( i == highscores.size() ) return INT_MAX;
	else return i;
}

std::string HighscoreHandler::get_name() {
	std::string name;
	std::cout << "Highscore name: ";
	std::getline(std::cin, name);
	return name;
}

void HighscoreHandler::update_highscores() {
	highscores.clear();
	std::ifstream file("HIGHSCORES.md");
	std::string line;
	if (file.is_open()) {
		unsigned int score;
		while (std::getline(file, line) && file >> score) highscores.push_back(score);
	}
}