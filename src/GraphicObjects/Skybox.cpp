#include "Skybox.h"

Skybox::Skybox(Texture *T) : texture(T) {
    setPosition(0.0f, 0.0f, 0.0f);
    setRotation(0.0f, 0.0f, 0.0f);
    size = 1000.0f;
}

void Skybox::draw_object() {
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
        // front face
        glNormal3f (0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.25f, 0.33f); glVertex3f(-size, -size,  size);  // bottom left
        glTexCoord2f(0.5f,  0.33f); glVertex3f( size, -size,  size);  // bottom right
        glTexCoord2f(0.5f,  0.66f); glVertex3f( size,  size,  size);  // top right
        glTexCoord2f(0.25f, 0.66f); glVertex3f(-size,  size,  size);  // top left
        // back face
        glNormal3f (0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.75f, 0.328f); glVertex3f( size,      -size,      -size);  // bottom left
        glTexCoord2f(1.0f,  0.328f); glVertex3f(-size-3.0f, -size,      -size);  // bottom right
        glTexCoord2f(1.0f,  0.66f);  glVertex3f(-size-3.0f,  size+1.0f, -size);  // top right
        glTexCoord2f(0.75f, 0.66f);  glVertex3f( size,       size+1.0f, -size);  // top left
        // top face
        glNormal3f (0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.25f, 0.66f); glVertex3f(-size,  size,  size);  // bottom left
        glTexCoord2f(0.5f,  0.66f); glVertex3f( size,  size,  size);  // bottom right
        glTexCoord2f(0.5f,  1.0f ); glVertex3f( size,  size, -size);  // top right
        glTexCoord2f(0.25f, 1.0f ); glVertex3f(-size,  size, -size);  // top left
        // right face
        glNormal3f (0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.50f, 0.33f); glVertex3f( size, -size,  size);  // bottom left
        glTexCoord2f(0.75f, 0.33f); glVertex3f( size, -size, -size);  // bottom right
        glTexCoord2f(0.75f, 0.66f); glVertex3f( size,  size, -size);  // top right
        glTexCoord2f(0.50f, 0.66f); glVertex3f( size,  size,  size);  // top left
        // left face
        glNormal3f (0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f,  0.33f); glVertex3f(-size, -size, -size);  // bottom left
        glTexCoord2f(0.25f, 0.33f); glVertex3f(-size, -size,  size);  // bottom right
        glTexCoord2f(0.25f, 0.66f); glVertex3f(-size,  size,  size);  // top right
        glTexCoord2f(0.0f,  0.66f); glVertex3f(-size,  size, -size);  // top left
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Skybox::setMaterial() {
    glColor3f(1.0f, 1.0f, 1.0f);
    GLfloat diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
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