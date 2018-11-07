#include "Car.h"

Car::Car(Texture *T) : texture(T) {
	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	size = 6.0f; half_size = size / 2;
}

void Car::draw_object() {
	glRotatef(-90, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBegin (GL_QUADS);
		/* bottom plane */
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, -2.0f, 0.1f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 6.0f, -2.0f, 0.1f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 6.0f,  2.0f, 0.1f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f,  2.0f, 0.1f);
		/* roof */
		glNormal3f (0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.3f, 0.3f); glVertex3f(-4.0f, -2.0f, 3.0f);
		glTexCoord2f(0.7f, 0.3f); glVertex3f( 2.0f, -2.0f, 3.0f);
		glTexCoord2f(0.7f, 0.7f); glVertex3f( 2.0f,  2.0f, 3.0f);
		glTexCoord2f(0.3f, 0.7f); glVertex3f(-4.0f,  2.0f, 3.0f);
		/* hood */
		glNormal3f (0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.3f); glVertex3f( 3.0f, -2.0f, 1.5f);
		glTexCoord2f(0.3f, 0.3f); glVertex3f( 6.0f, -2.0f, 1.5f);
		glTexCoord2f(0.3f, 0.7f); glVertex3f( 6.0f,  2.0f, 1.5f);
		glTexCoord2f(0.0f, 0.7f); glVertex3f( 3.0f,  2.0f, 1.5f);
		/* front */
		glNormal3f (0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.5f, 0.7f); glVertex3f( 6.0f, -2.0f, 0.0f);
		glTexCoord2f(0.5f, 0.85f);glVertex3f( 6.0f, -2.0f, 1.5f);
		glTexCoord2f(0.9f, 0.85f);glVertex3f( 6.0f,  2.0f, 1.5f);
		glTexCoord2f(0.9f, 0.7f); glVertex3f( 6.0f,  2.0f, 0.0f);
		/* back */
		glNormal3f (0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.7f, 0.3f); glVertex3f(-4.0f, -2.0f, 0.0f);
		glTexCoord2f(1.0f, 0.3f); glVertex3f(-4.0f, -2.0f, 3.0f);
		glTexCoord2f(1.0f, 0.7f); glVertex3f(-4.0f,  2.0f, 3.0f);
		glTexCoord2f(0.7f, 0.7f); glVertex3f(-4.0f,  2.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		/* right side */
		glNormal3f (0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, -2.0f, 0.0f);
		glTexCoord2f(0.0f, 0.3f); glVertex3f(-4.0f, -2.0f, 3.0f);
		glTexCoord2f(0.4f, 0.3f); glVertex3f( 2.0f, -2.0f, 3.0f);
		glTexCoord2f(0.5f, 0.15f);glVertex3f( 3.0f, -2.0f, 1.5f);
		glTexCoord2f(0.8f, 0.15f);glVertex3f( 6.0f, -2.0f, 1.5f);
		glTexCoord2f(0.8f, 0.0f); glVertex3f( 6.0f, -2.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		/* left side */
		glNormal3f (0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f,  2.0f, 0.0f);
		glTexCoord2f(0.8f, 1.0f); glVertex3f( 6.0f,  2.0f, 0.0f);
		glTexCoord2f(0.8f, 0.85f);glVertex3f( 6.0f,  2.0f, 1.5f);
		glTexCoord2f(0.5f, 0.85f);glVertex3f( 3.0f,  2.0f, 1.5f);
		glTexCoord2f(0.4f, 0.7f); glVertex3f( 2.0f,  2.0f, 3.0f);
		glTexCoord2f(0.0f, 0.7f); glVertex3f(-4.0f,  2.0f, 3.0f);
	glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Car::setMaterial() {
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
	texture->Bind();
}