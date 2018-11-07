#include "Ground.h"

Ground::Ground(int s, Texture *T) : texture(T) {
	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	ground_size = s;
	level_subdivision = 100;
}

void Ground::draw_object() {
	glEnable(GL_TEXTURE_2D);
	glNormal3d(0, 1, 0);
	float x_left, x_right, z_left, z_right;
	for (auto i=-level_subdivision; i<=level_subdivision; ++i) {
		for (auto j=-level_subdivision; j<=level_subdivision; ++j) {
			x_left = i * ground_size - 0.5 * ground_size;
			x_right = x_left + ground_size;
			z_left = j * ground_size - 0.5 * ground_size;
			z_right = z_left + ground_size;
			drawPlane(x_left, x_right, z_left, z_right);
		}
	}
	glDisable(GL_TEXTURE_2D);
}

void Ground::drawPlane(const int x_left, const int x_right,
					   const int z_left, const int z_right) {
	float delta = 0.0f;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,  0.0f); glVertex3f( x_right-delta, 0.0,  z_left+delta);
		glTexCoord2f(1.0f,  0.0f); glVertex3f( x_left+delta,  0.0,  z_left+delta);
		glTexCoord2f(1.0f,  1.0f); glVertex3f( x_left+delta,  0.0,  z_right-delta);
		glTexCoord2f(0.0f,  1.0f); glVertex3f( x_right-delta, 0.0,  z_right-delta);
	glEnd();
}

void Ground::setMaterial() {
	static const GLfloat diffuse[]	= { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat ambient[]	= { 0.05, 0.05, 0.2, 0.0 };
	static const GLfloat no_mat[]  	= {  0.0,  0.0,  0.0, 1.0 };
	static const GLfloat shininess[]= {  30.0 };
 
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	texture->Bind();
}