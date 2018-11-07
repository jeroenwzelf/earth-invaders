#pragma once

#include "GraphicObject.h"
#include "Animation.h"

class Rocket : public GraphicObject {
	public:
		Rocket(float X, float Y, float Z, Animation A);
		void draw_object() override;
		void move() override;
	private:
		void setMaterial() override;
	public:
		const std::string name = "Rocket";
		Animation animation;
	private:
		float speed;
		int animation_index;
};