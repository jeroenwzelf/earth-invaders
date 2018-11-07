#pragma once

#include "GraphicObject.h"
#include "Texture.h"

struct particle {
	float width;
	float r, g, b;
	float x, y, z;
	float v_x, v_y, v_z;
	bool color_disco;
	bool alive;
	int age;
	void setRGB(float R, float G, float B) 	{ r=R; g=G; b=B; }
	void setPos(float X, float Y, float Z) 	{ x=X; y=Y; z=Z; }
	void setVel(float X, float Y, float Z) 	{ v_x=X; v_y=Y; v_z=Z; }
	void enable(float w, bool disco)		{ alive=true; age=0; width=w; color_disco=disco; }
};

class Fireworks {
	public:
		Fireworks(Texture *T);
		void draw();
		void update(float time);
		void FireworksAt(float X, float Y, float Z, float R, float G, float B);
		void Firework0(float X, float Y, float Z, float R, float G, float B);
		void Firework1(float X, float Y, float Z, float R, float G, float B);
		void Firework2(float X, float Y, float Z, float R, float G, float B);
		void Firework3(float X, float Y, float Z, float R, float G, float B);
		void Firework4(float X, float Y, float Z, float R, float G, float B);
		void RotateToPoint(float angle);
		void clear();
	private:
		int findNextSpot();
		void draw_particle(const particle & p);
		void gravity(particle & p, float time);
		void setMaterial();
		float random(float LO, float HI);
	public:
		const std::string name = "Fireworks";
	private:
		Texture *texture;
		static const int MAX_PARTICLES = 2000;
		static const int PARTICLE_MAXAGE = 1000;
		float rotation;
		particle particles[MAX_PARTICLES];
};