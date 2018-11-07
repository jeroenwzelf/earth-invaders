#pragma once

#include "GraphicObject.h"
#include "Texture.h"

class Car : public GraphicObject {
	public:
		Car(Texture *T);
		void draw_object() override;
		void move() override {}
	private:
		void setMaterial() override;
	public:
		const std::string name = "Car";
	private:
		Texture *texture;
};