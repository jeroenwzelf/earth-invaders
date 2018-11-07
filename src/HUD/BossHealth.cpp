#include "BossHealth.h"

void BossHealth::init() {
	name = "BossHealth";
	x = 0.5f; y = 0.05f;
	length = 1000.0f;
	height = 10.0f;
	length_half = length / 2;
	height_half = height / 2;
	health = 100;
}

void BossHealth::update_health(float h) {
	health = h;
	update_size();
}

void BossHealth::update_size() {
	length_health = length * ( health / 100 );
}

void BossHealth::draw() {
	draw_box(x_screen - length_half, y_screen - height_half, length, height, 0.0f, 0.0f, 0.0f, false);
	draw_box(x_screen - length_half, y_screen - height_half, length_health, height, 1.0f, 0.0f, 0.0f, false);
}