#include "Cannon.h"

Cannon::Cannon(Animation A) : animation(A) {
	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	size = 5.0f; half_size = size / 2.0f;
}

void Cannon::draw_object() { 
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
        glNormal3f (1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_size, -half_size, 0.0f);  // bottom left
        glTexCoord2f(1.0f, 0.0f); glVertex3f( half_size, -half_size, 0.0f);  // bottom right
        glTexCoord2f(1.0f, 1.0f); glVertex3f( half_size,  half_size, 0.0f);  // top right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_size,  half_size, 0.0f);  // top left
	glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Cannon::shoot() {
	animation.init();
	animation.start();
}

void Cannon::setMaterial() {
	glColor3f(1.0f, 1.0f, 1.0f);
	static const GLfloat diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    static const GLfloat ambient[]  = { 0.05, 0.05, 0.2, 0.0 };
    static const GLfloat no_mat[]   = {  0.0,  0.0,  0.0, 1.0 };
    static const GLfloat shininess[]= {  30.0 };
 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	animation.Bind();
}