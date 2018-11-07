#include "Boss.h"

#define RADIUS 50.0f

Boss::Boss(Animation A) : animation(A) {
    size = 45.0f; half_size = size / 2;
    setRotation(0.0f, 0.0f, 0.0f);
    setPosition(random(-10.0f, 10.0f), 70.0f, random(-10.0f, 10.0f));
    r = random(0.5f, 1.0f); g = random(0.5f, 1.0f); b = random(0.5f, 1.0f);
    value = 1000;
    health = 100;

    falling = true;
    falltimer = 100;
}

float Boss::random(float LO, float HI) {
	return ( LO + static_cast <float>(rand()) / ( static_cast <float>(RAND_MAX/(HI-LO)) ) );
}

void Boss::draw_object() { 
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glNormal3f (1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_size, -half_size, 0.0f);  // bottom left
        glTexCoord2f(1.0f, 0.0f); glVertex3f( half_size, -half_size, 0.0f);  // bottom right
        glTexCoord2f(1.0f, 1.0f); glVertex3f( half_size,  half_size, 0.0f);  // top right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_size,  half_size, 0.0f);  // top left
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    draw_shadow();
}

void Boss::draw_shadow() {
    static const float pi_sqr = 2.0f * M_PI;
    int subdivisions = 20;
    float radius;
    // Shadow becomes bigger the closer the boss is to the ground
    if (y > 10) radius = 10 * size / y;
    else radius = size;
    
    glColor3f(20 / y, 0.2f, 0.2f);

    glEnable(GL_COLOR_MATERIAL);
    glNormal3f (0.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, -y + 0.1f, 0.0f);
        for(int i=0; i <= subdivisions; ++i) {
            glVertex3f(radius * cos(i * pi_sqr / subdivisions),
                       -y + 0.1f,
                       radius * sin(i * pi_sqr / subdivisions));
        }
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
}

void Boss::move() {
    static float direction_x; static float direction_z;

    if (moving) {
        setPositionRelative(direction_x, 0.0f, direction_z);
        if (movetimer > 0) movetimer--;
        else moving = false;
    }
    else if (rand() % 500 > 485) {
        moving = true; movetimer = 30;
        direction_x = ( ( (rand() % 2) * 2 ) - 1 ) * 0.3;
        direction_z = ( ( (rand() % 2) * 2 ) - 1 ) * 0.3;
        // make sure enemies don't move outside a shootable radius
        if (x + direction_x > RADIUS) direction_x = -direction_x;
        if (z + direction_z > RADIUS) direction_z = -direction_z;
    }
    if (falling) {
        setPositionRelative(0, -0.2, 0);
        if (falltimer > 0) falltimer--;
        else falling = false;
    }
    else if (rand() % 500 > 490) { falling = true; falltimer = 20; }
}

void Boss::setMaterial() {
    glColor3f(r, g, b);
    GLfloat diffuse[]  = { r, g, b, 1.0f };
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