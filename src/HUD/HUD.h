#pragma once

#include "HUDitem.h"
#include "Sprites.h"

#include <memory>

typedef std::vector<std::shared_ptr<HUDitem>> HUDitem_Vector;

class HUD {
	public:
		HUD(float w, float h, Sprites* S);
		void init();
		void draw();
		void setScreenSize(float w, float h);

		// user generated actions
		void intro_message_show();
		void intro_message_remove();
		void setScore(int score);
		void setWave(int wave, bool bosswave);
		void setTooltip(std::string text, int time);
		void setHealth(int h);
		void setBossHealth(float h);
	private:
		HUDitem* getHUDitem(const std::string item);
	private:
		Sprites* sprites;
		HUDitem_Vector HUDitems;
		float screen_width, screen_height;
};