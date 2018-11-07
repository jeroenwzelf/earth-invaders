#pragma once

#include <vector>

class InputHandler {
	public:
		void keyboardFunc(const unsigned char key, const int x, const int y);
		void keyboardUpFunc(const unsigned char key, const int x, const int y);
		std::vector<unsigned char> keys_down;
		std::vector<unsigned char> keys_pressed;
};
