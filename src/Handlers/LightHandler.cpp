#include "LightHandler.h"

LightHandler::LightHandler() {
	glEnable(GL_LIGHTING); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	clear();
}

void LightHandler::clear() {
	for (int i=0; i < GL_MAX_LIGHTS; ++i) {
		lights[i].enabled = false;
		lights[i].lifetime = -1;
		lights[i].intensity = 0;
		lights[i].r = 0; lights[i].g = 0; lights[i].b = 0;
	}
}

void LightHandler::enable_main_light() {
	new_light(0.0f, 20.0f, 0.0f, 0.9f, 0.9f, 0.9f, 0.9f, -1);
}

void LightHandler::new_light(float X, float Y, float Z, float R, float G, float B, float brightness, float time) {
	int i = availableLight();
	if (i != -1) {
		lights[i].lifetime = time;
		lights[i].intensity = brightness;
		lights[i].r = R; lights[i].g = G; lights[i].b = B;

		const GLfloat diff[] = { lights[i].r, lights[i].g, lights[i].b, lights[i].intensity };
		const GLfloat spec[] = { 1, 1, 1 };
		const GLfloat ambt[] = { 0, 0, 0 };
		GLfloat position[] = { X, Y, Z, 2 };

		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, spec);
		glLightfv(GL_LIGHT0 + i, GL_POSITION, position);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambt);
		enable(i);
	}
}

void LightHandler::update() {
	for (int i=0; i < GL_MAX_LIGHTS; ++i) {
		if (lights[i].enabled) {
			if (lights[i].lifetime == 0) disable(i);
			else if (lights[i].lifetime > 0) {
				lights[i].lifetime--;
			}
		}
	}
}

void LightHandler::enable(int light) {
	lights[light].enabled = true;
	glEnable(GL_LIGHT0 + light);
}

void LightHandler::disable(int light) {
	lights[light].enabled = false;
	lights[light].lifetime = -1;
	glDisable(GL_LIGHT0 + light);
}

int LightHandler::availableLight() {
	for (int i=0; i < GL_MAX_LIGHTS; ++i) {
		if (!lights[i].enabled) return i;
	}
	return -1;
}