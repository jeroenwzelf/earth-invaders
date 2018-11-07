#include "Fireworks.h"
#include "GL/glew.h"
#include "GL/glut.h"

Fireworks::Fireworks(Texture *T) : texture(T) {
	clear();
}

void Fireworks::clear() {
	for (int i=0; i < MAX_PARTICLES; ++i) {
		particles[i].alive = false;
	}
}

void Fireworks::draw() {
	setMaterial();
	for (int i=0; i < MAX_PARTICLES; ++i) {
		if (particles[i].alive) {
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
				glColor3f(particles[i].r, particles[i].g, particles[i].b);
				draw_particle(particles[i]);
			glDisable(GL_TEXTURE_2D);
    		glEnable(GL_LIGHTING);
    		glPopMatrix();
		}
	}
}

void Fireworks::draw_particle(const particle & p) {
	float half_size = p.width / (2 * p.age) ;
	glTranslatef(p.x, p.y, p.z);
	glRotatef(rotation, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
        glNormal3f (1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_size, -half_size, 0.0f);  // bottom left
        glTexCoord2f(1.0f, 0.0f); glVertex3f( half_size, -half_size, 0.0f);  // bottom right
        glTexCoord2f(1.0f, 1.0f); glVertex3f( half_size,  half_size, 0.0f);  // top right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_size,  half_size, 0.0f);  // top left
	glEnd();
}

void Fireworks::RotateToPoint(float angle) {
	rotation = -angle;
}

void Fireworks::update(float time) {
	for (int i = 0; i < MAX_PARTICLES; ++i) {
		if (particles[i].alive) {
			// kill particle if it has outlived its age
			if (particles[i].age > PARTICLE_MAXAGE)
				particles[i].alive = false;
			else {
				if (particles[i].color_disco)
					particles[i].setRGB(random(0.0f, 1.0f), random(0.0f, 1.0f), random(0.0f, 1.0f));
			// calculate particle movement
				gravity(particles[i], time);
				particles[i].y += particles[i].v_y * time;
				particles[i].x += particles[i].v_x * time;
				particles[i].z += particles[i].v_z * time;
				++particles[i].age;
			}
		}
	}
}

void Fireworks::gravity(particle & p, float time) {
	if (p.y > 0.0f) p.v_y -= 9.81 * time;
	else {
		p.y = 0;
		p.v_y *= -0.25;
		p.v_x *=  0.7;
		p.v_z *=  0.7;
	}
}

void Fireworks::FireworksAt(float X, float Y, float Z, float R, float G, float B) {
	int rnd = rand() % 5;
	switch (rnd) {
		case 0: Firework0(X, Y, Z, R, G, B); break;
		case 1: Firework1(X, Y, Z, R, G, B); break;
		case 2: Firework2(X, Y, Z, R, G, B); break;
		case 3: Firework3(X, Y, Z, R, G, B); break;
		case 4:
		default: Firework4(X, Y, Z, R, G, B); break;
	}
}

// Generic fireworks
void Fireworks::Firework0(float X, float Y, float Z, float R, float G, float B) {
	// Speedy particles
	int j;
	for (int i=0; i < 40; ++i) {
		j = findNextSpot();
		particles[j].setPos(X, Y, Z);
		particles[j].setRGB(R, G, B);
		particles[j].setVel(random(-40.0f, 40.0f), random(10.0f, 20.0f), random(-40.0f, 40.0f));
		particles[j].enable(random(15.0f, 20.0f), false);
	}
	// Falling particles
	for (int i=0; i < 20; ++i) {
		j = findNextSpot();
		particles[j].setPos(X, Y, Z);
		particles[j].setVel(random(-10.0f, 10.0f), random(0.0f, 5.0f), random(-10.0f, 10.0f));
		particles[j].enable(random(25.0f, 30.0f), true);
	}
}

// Big boom fireworks
void Fireworks::Firework1(float X, float Y, float Z, float R, float G, float B) {
	int i = findNextSpot();
	particles[i].setPos(X, Y, Z);
	particles[i].setVel(0, random(0, 5), 0);
	particles[i].enable(random(80, 250), true);
}

// Cylinder fireworks
void Fireworks::Firework2(float X, float Y, float Z, float R, float G, float B) {
	static const float pi_sqr = 2.0f * M_PI;
    float radius = 10;
	int j;
	for (int a=0; a < 10; ++a) {
		for (int i=0; i < 80; ++i) {
			j = findNextSpot();
			particles[j].setPos(X, Y, Z);
			particles[j].setRGB(R, G, B);
			particles[j].setVel(radius * cos(i * pi_sqr / 80) , a ,  radius * sin(i * pi_sqr / 80));
			particles[j].enable(random(10.0f, 15.0f), false);
		}
	}
}

// Death Star explosion fireworks
void Fireworks::Firework3(float X, float Y, float Z, float R, float G, float B) {
	static const float pi_sqr = 2.0f * M_PI;
    const float radius = 5;
	int j;
	for (int a=0; a < 10; ++a) {
		for (int i=0; i < 80; ++i) {
			j = findNextSpot();
			float circleCOS = radius * cos(i * pi_sqr / 80);
			float circleSIN = radius * sin(i * pi_sqr / 80);
			float smalla = 0.2 * a;

			particles[j].setPos(X + circleCOS, Y, Z + circleSIN);
			particles[j].setVel(smalla * circleSIN, smalla * circleCOS, smalla * circleSIN);
			particles[j].enable(random(10.0f, 15.0f), true);
		}
	}
}

// Circle fireworks
void Fireworks::Firework4(float X, float Y, float Z, float R, float G, float B) {
	static const float pi_sqr = 2.0f * M_PI;
    const int subdivisions = 40;
    const float radius = 5;

    for (int i=0; i < subdivisions; ++i) {
    	bool disco;
    	particles[i].setPos(X + radius * cos(i * pi_sqr / subdivisions), Y, Z + radius * sin(i * pi_sqr / subdivisions));
    	particles[i].setVel(5 * radius * cos(i * pi_sqr / subdivisions), 0, 5 * radius * sin(i * pi_sqr / subdivisions));
    	particles[i].setRGB(R, G, B);
    	if (i % 2 == 0) disco = true; else disco = false;
    	particles[i].enable(random(10.0f, 15.0f), disco);
    }
}

// finds index of unused particle
int Fireworks::findNextSpot() {
	for (int i=0; i < MAX_PARTICLES; ++i) {
		if (!particles[i].alive) return i;
	}
	return rand() % MAX_PARTICLES;
}

float Fireworks::random(float LO, float HI) {
	return ( LO + static_cast <float>(rand()) / ( static_cast <float>(RAND_MAX/(HI-LO)) ) );
}

void Fireworks::setMaterial() {
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