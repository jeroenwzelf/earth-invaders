#pragma once

#include "GraphicObject.h"
#include "Animation.h"

class Enemy : public GraphicObject {
	public:
		Enemy(Animation A);
		void draw_object() override;
		void move() override;
	private:
		void draw_shadow();
		float random(float LO, float HI);
		void setMaterial() override;
	public:
		const std::string name = "Enemy";
		Animation animation;
		float r, g, b;
		float value;
};