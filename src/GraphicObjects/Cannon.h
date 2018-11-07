#pragma once

#include "GraphicObject.h"
#include "Animation.h"

class Cannon : public GraphicObject {
	public:
		Cannon(Animation A);
		void draw_object() override;
		void move() override {}
		void shoot();
	private:
		void setMaterial() override;
	public:
		const std::string name = "Cannon";
	private:
		Animation animation;
};