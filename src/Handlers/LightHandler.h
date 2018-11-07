#pragma once

#include "GL/glew.h"
#include "GL/glut.h"

struct light {
	float intensity;
	float lifetime;
	float r, g, b;
	bool enabled;
};

class LightHandler {
	public:
		LightHandler();
		void clear();
		void enable_main_light();
		void new_light(float X, float Y, float Z,
					   float R, float G, float B, float brightness, float time);
		void update();
	private:
		int availableLight();
		void enable(int light);
		void disable(int light);
		light lights[GL_MAX_LIGHTS];
};