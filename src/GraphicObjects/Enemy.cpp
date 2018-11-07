#include "Enemy.h"

#define SPAWN_RADIUS 50.0f

Enemy::Enemy(Animation A) : animation(A) {
    size = 7.0f;
    half_size = size / 2;
    setRotation(0.0f, 0.0f, 0.0f);
    setPosition(random(-SPAWN_RADIUS, SPAWN_RADIUS), random(40.0f, 90.0f), random(-SPAWN_RADIUS, SPAWN_RADIUS));
    r = random(0.0f, 1.0f); g = random(0.0f, 1.0f); b = random(0.0f, 1.0f);
    value = 100;
}

float Enemy::random(float LO, float HI) {
	return ( LO + static_cast <float>(rand()) / ( static_cast <float>(RAND_MAX/(HI-LO)) ) );
}

void Enemy::draw_object() { 
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

void Enemy::draw_shadow() {
    static const float pi_sqr = 2.0f * M_PI;
    int subdivisions = 20;
    float radius;
    // Shadow becomes bigger the closer the enemy is to the ground
    if (y > 10) radius = 10 * half_size / y;
    else radius = half_size;
    
    glColor3f(20 / y, 0.0f, 0.0f);

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

void Enemy::move() {
    int direction_x = 0; int direction_y = 0; int direction_z = 0;
    int move_roll = rand() % 100;
    int fall_roll = rand() % 100;

    if (fall_roll > 97) direction_y = -2;
    if (move_roll > 90) {
        direction_x = ( (rand() % 2) * 2 ) - 1;
        direction_z = ( (rand() % 2) * 2 ) - 1;
        // make sure enemies don't move outside a shootable radius
        if (x + direction_x > SPAWN_RADIUS) direction_x = -direction_x;
        if (z + direction_z > SPAWN_RADIUS) direction_z = -direction_z;
    }
    setPositionRelative(direction_x, direction_y, direction_z);
}

void Enemy::setMaterial() {
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