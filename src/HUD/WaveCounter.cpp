#include "WaveCounter.h"

void WaveCounter::init() {
	x = 0.02; y = 0.05;
	wave = 0;
	name = "WaveCounter";
}

void WaveCounter::draw() {
	draw_text("Wave: " + std::to_string(wave), x_screen, y_screen);
}

void WaveCounter::setWave(int w) {
	wave = w;
}