#include "InputHandler.h"

void InputHandler::keyboardFunc(const unsigned char key, const int x, const int y) {
	keys_pressed.push_back(key);
	keys_down.push_back(key);
}

void InputHandler::keyboardUpFunc(const unsigned char key, const int x, const int y) {
	for ( auto i = keys_down.begin(); i != keys_down.end(); ) {
		if (*i == key) i = keys_down.erase(i);
		else ++i;
	}
}