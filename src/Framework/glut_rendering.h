#pragma once

#include "Game.h"
#include "GraphicObject.h"

typedef std::vector<std::shared_ptr<GraphicObject>> GraphicObject_Vector;

class glut_rendering {
	public:
		glut_rendering(int argc, char *argv[], std::shared_ptr<Game> g);
		void display();
		
		void reshape(const int w, const int h);
		void glTimer(int value);
	private:
		void init_glut(int argc, char *argv[]);

		void drawScene();
		void render_3D();	// turn on perspective rendering
		void render_2D();	// turn on orthogonal rendering
		
		// drawing objects from closest to furthest
		float distance_to_cam(GraphicObject* obj);
		void draw_furthest(GraphicObject_Vector & objects,
							std::vector<float> & distances);
		GraphicObject_Vector getObjects();
	private:
		int screen_width, screen_height;
};