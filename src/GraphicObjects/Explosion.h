#pragma once

#include "GraphicObject.h"
#include "Animation.h"

class Explosion : public GraphicObject {
	public:
		Explosion(float X, float Y, float Z, Animation A, int timer);
		void draw_object() override;
		void move() override {}
	private:
		void setMaterial() override;
	public:
		const std::string name = "Explosion";
		Animation animation;
	private:
		int start_timer;
};