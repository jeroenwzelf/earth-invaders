#pragma once

#include "GL/glew.h"
#include "GL/glut.h"

#include "Texture.h"
#include "Animation.h"

class HUDitem {
	public:
		HUDitem(float w, float h);
		virtual void init() = 0;
		virtual void draw() = 0;
		void setScreenSize(float w, float h);

		// Frequently used functions to easily draw things
		void draw_box(float x, float y, float w, float h, float r, float g, float b, bool center);
		void draw_image(float x, float y, float w, float h, Texture* image);
		void draw_image(float x, float y, float w, float h, Animation* image);
		void draw_paragraph_center(std::vector<std::string> paragraph, float x, float y);
		void draw_text(std::string text, float x, float y);
		virtual ~HUDitem() {}
	public:
		bool active;
		std::string name;

		float x, y;					// coords from 0.0f-1.0f
		float x_screen, y_screen;	// actual pixel coords
		float screen_width;
		float screen_height;
		static const int FONT_W = 8;
		static const int FONT_H = 13;
};