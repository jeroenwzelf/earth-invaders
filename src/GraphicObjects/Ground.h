#pragma once

#include "Texture.h"
#include "GraphicObject.h"

class Ground : public GraphicObject {
	public:
		Ground(int s, Texture *T);
		void draw_object() override;
		void move() override {}
	private:
		void setMaterial() override;
		void drawPlane(const int x_left, const int x_right,
					   const int z_left, const int z_right);
	public:
		const std::string name = "Ground";
	private:
		int ground_size;
		int level_subdivision;
		Texture* texture;
};