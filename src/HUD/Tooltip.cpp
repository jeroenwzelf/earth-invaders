#include "Tooltip.h"

void Tooltip::init() {
	text_width = 0;
	x = 0.5f; y = 0.85f;
	r = 0.3f; g = 0.3f; b = 0.8f;
	timer = -1;
	name = "Tooltip";
}

void Tooltip::setTooltip(std::string T, int time) {
	timer = time;
	text.clear();
	text_width = 0;
	std::string line;
	int size = 0;
	for (std::string::size_type i = 0; i < T.size(); ++i) {
		char c = T[i];
		if (i == T.size()-1 || c == '\n') {
			text.push_back(line);
			line.clear();
			if (size > text_width) text_width = size;
			size = 0;
		}
		else {
			line += c;
			size += FONT_W;
		}
	}
	text_height = text.size() * FONT_H;
}

void Tooltip::draw() {
	if (timer == 0) active = false;
	else if (timer > 0) timer--;
	draw_box(x_screen, y_screen, text_width+border, text_height+border, r, g, b, true);
	draw_paragraph_center(text, x_screen, y_screen);
}