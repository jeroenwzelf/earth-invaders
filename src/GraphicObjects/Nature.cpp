#include "Nature.h"

Nature::Nature(Texture *T, float s) : texture(T) {
	setRotation(0.0f, 0.0f, 0.0f);
	size = s; half_size = size / 2;
	setPosition(random(-100.0f, 100.0f), 0.0, random(-100.0f, 100.0f));
}

float Nature::random(float LO, float HI) {
	return ( LO + static_cast <float>(rand()) / ( static_cast <float>(RAND_MAX/(HI-LO)) ) );
}

void Nature::draw_object() {
    glPushMatrix();

    // undo all rotations
	float modelview[16];
    glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
    for (int i=0; i < 3; ++i) 
        for (int j=0; j < 3; ++j) {
            if (i==j) modelview[i*4+j] = 1.0;
            else modelview[i*4+j] = 0.0;
        }
    glLoadMatrixf(modelview);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glNormal3f (0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_size, -half_size, 0.0f);  // bottom left
		glTexCoord2f(1.0f, 0.0f); glVertex3f( half_size, -half_size, 0.0f);  // bottom right
		glTexCoord2f(1.0f, 1.0f); glVertex3f( half_size,  half_size, 0.0f);  // top right
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_size,  half_size, 0.0f);  // top left
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Nature::setMaterial() {
	glColor3f(1.0f, 1.0f, 1.0f);
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
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