#pragma once

#include "HUDitem.h"

class Tooltip : public HUDitem {
	public:
		Tooltip(float w, float h)
				: HUDitem(w, h) { init(); }
		void init() override;
		void draw() override;
		void setTooltip(std::string T, int time);
	private:
		const float border = 20.0f;
		float r, g, b;
		int text_width, text_height;
		std::vector<std::string> text;
		int timer;
};