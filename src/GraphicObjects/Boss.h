#pragma once

#include "GraphicObject.h"
#include "Animation.h"

class Boss : public GraphicObject {
	public:
		Boss(Animation A);
		void draw_object() override;
		void move() override;
	private:
		void draw_shadow();
		float random(float LO, float HI);
		void setMaterial() override;
	public:
		const std::string name = "Boss";
		Animation animation;
		float r, g, b;
		float value;
		float health;

		bool falling;
		int falltimer;
		bool moving;
		int movetimer;
};