#pragma once

#include "HUDitem.h"

class BossHealth : public HUDitem {
	public:
		BossHealth(float w, float h)
				: HUDitem(w, h) { init(); }
		void update_health(float h);
		void update_size();
		void init() override;
		void draw() override;
	public:
		float health;
		float height, height_half, length, length_half, length_health;
};