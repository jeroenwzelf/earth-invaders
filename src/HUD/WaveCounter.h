#pragma once

#include "HUDitem.h"

class WaveCounter : public HUDitem {
	public:
		WaveCounter(float w, float h)
				: HUDitem(w, h) { init(); }
		void init() override;
		void draw() override;
		void setWave(int w);
	public:
		int wave;
};