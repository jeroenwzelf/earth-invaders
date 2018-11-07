#pragma once

#include "HUDitem.h"

class PointCounter : public HUDitem {
	public:
		PointCounter(float w, float h)
				: HUDitem(w, h) { init(); }
		void init() override;
		void draw() override;
		void setPoints(int p);
	public:
		int points;
};