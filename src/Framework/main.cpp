#include "GL/glew.h"
#include "GL/glut.h"
#include "glut_rendering.h"

// using srand(time(NULL))
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// For some reason, LIACS computers give a segfault whenever I try to link -lGL
// For some reason, it works when I force the compiler to think that it needs pthreads
// so it actually links the -pthread library
#if defined(__unix__)
#include <pthread.h>
void* simpleFunc(void*) { return NULL; }
void forcePTHreadLink() {
	pthread_t t1;
	pthread_create(&t1, NULL, &simpleFunc, NULL);
}
#endif

#define DEF_TITLE "Earth Invaders"

void initWindow(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(DEF_TITLE);
	glewExperimental = true;
	glewInit();
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	initWindow(argc, argv);
	
    float screen_w = glutGet(GLUT_WINDOW_WIDTH);
    float screen_h = glutGet(GLUT_WINDOW_HEIGHT);

	std::shared_ptr<Game> g = std::make_shared<Game>(screen_w, screen_h);
	glut_rendering renderer(argc, argv, g);
	return 0;
}