#include "GL/glew.h"
#include "GL/glut.h"
#include "glut_rendering.h"

#define DEF_FOV		90
#define DEF_ZBUFF_N 1
#define DEF_ZBUFF_F 10000
#define FULLSCREEN  true

/* -- For OpenGL it is easier to have callback functions that are not in classes  -- */

glut_rendering *glut_callback;
std::shared_ptr<Game> game_callback;

void reshapeCallback(const int w, const int h)
								{ glut_callback->reshape(w, h); }
void displayCallback()			{ glut_callback->display(); }
void glTimerCallback(int value) { glut_callback->glTimer(value); }
void inputCallback(const unsigned char key, const int x, const int y)
								{ game_callback->inputHandler->keyboardFunc(key, x, y); }
void inputUpCallback(const unsigned char key, const int x, const int y) 
								{ game_callback->inputHandler->keyboardUpFunc(key, x, y); }

/* -- -- */


glut_rendering::glut_rendering(int argc, char *argv[], std::shared_ptr<Game> g) {
	glut_callback = this;
	game_callback = g;
	init_glut(argc, argv);
}

void glut_rendering::init_glut(int argc, char *argv[]) {
	glMatrixMode(GL_PROJECTION);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // for transparent objects with textures with an alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_SMOOTH);

    // glut callback functions
	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);
	glutTimerFunc(50, glTimerCallback, 0);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(inputCallback);
	glutKeyboardUpFunc(inputUpCallback);


	if (FULLSCREEN) glutFullScreen();
	glutMainLoop();
}

void glut_rendering::glTimer(int value) {
	static int lastTime;
	int thisTime;
	float time;
	thisTime = glutGet(GLUT_ELAPSED_TIME);
	time = (thisTime - lastTime) * 0.001;
	lastTime = thisTime;
	if (!game_callback->paused) game_callback->update(time);

	glutPostRedisplay();

	glutTimerFunc(50, glTimerCallback, 0);
}

void glut_rendering::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game_callback->handleinput();

	render_3D();
		game_callback->setCameraPos(); 
		drawScene();

	render_2D();
		game_callback->hud->draw();
	
	glutSwapBuffers();
}

void glut_rendering::render_3D() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(DEF_FOV, (GLfloat)screen_width / (GLfloat)screen_height, DEF_ZBUFF_N, DEF_ZBUFF_F);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void glut_rendering::render_2D() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screen_width, screen_height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

float glut_rendering::distance_to_cam(GraphicObject* obj) {
	float dx = obj->x - game_callback->g_posX;
	float dy = obj->y - game_callback->g_posY;
	float dz = obj->z - game_callback->g_posZ;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

void glut_rendering::draw_furthest(GraphicObject_Vector & objects,
									std::vector<float> & distances) {
	float furthest_d = 0;
	unsigned int i, furthest_i;
	for (i=0; i < objects.size(); ++i) {
		if (distances.at(i) == -1.0f)
			distances.at(i) = distance_to_cam( objects.at(i).get() );

		if (distances.at(i) > furthest_d) {
			furthest_d = distances.at(i);
			furthest_i = i;
		}
	}
	objects.at(furthest_i).get()->draw();
	objects.erase(objects.begin() + furthest_i);
	distances.erase(distances.begin() + furthest_i);
}

GraphicObject_Vector glut_rendering::getObjects() {
	GraphicObject_Vector objects;
	for (auto i : game_callback->nature) objects.push_back(i);
	for (auto i : game_callback->enemies) objects.push_back(i);
	for (auto i : game_callback->explosions) objects.push_back(i);
	for (auto i : game_callback->projectiles) objects.push_back(i);
	return objects;		
}

void glut_rendering::drawScene() {
	GraphicObject_Vector all_objects = getObjects();
	std::vector<float> all_objects_distance;
	for (unsigned int i=0; i < all_objects.size(); ++i)		// init all distances
		all_objects_distance.push_back(-1.0f);

	// draw non-transparent objects first
	for (auto i : game_callback->static_objects)
		i->draw();
	game_callback->car->draw();

	// draw transparent objects from furthest to closest
	while (!all_objects.empty())
		draw_furthest(all_objects, all_objects_distance);

	// draw objects that always have to be in the foreground
	game_callback->cannon->draw();
	game_callback->fireworks->draw();
}

void glut_rendering::reshape(const int w, const int h) {
	screen_width = w; screen_height = h;
	game_callback->hud->setScreenSize(w, h);
    glViewport(0, 0, (GLsizei)screen_width, (GLsizei)screen_height);
}