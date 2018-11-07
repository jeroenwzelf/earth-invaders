#pragma once

#include "HUDitem.h"

class Health : public HUDitem {
	public:
		Health(float w, float h, Animation A)
				: HUDitem(w, h), animation(A) { init(); }
		void init() override;
		void draw() override;
		void setAnimation(Animation A);
	public:
		int health;
		float heart_size, heart_size_half;
		float space_between;
		Animation animation;
};