#pragma once

#include "HUDitem.h"

class IntroMessage : public HUDitem {
	public:
		IntroMessage(float w, float h, Animation A)
				: HUDitem(w, h), animation(A) { init(); }
		void init() override;
		void draw() override;
		void setIntroMessage();
	private:
		const float border = 20.0f;
		float r, g, b;
		Animation animation;
		std::vector<std::string> message;
};