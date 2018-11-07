#include "GraphicObject.h"

void GraphicObject::draw() {
	glPushMatrix();
	glTranslatef(x, y, z);
    glRotatef(xr, 1.0, 0.0, 0.0);
    glRotatef(yr, 0.0, 1.0, 0.0);
    glRotatef(zr, 0.0, 0.0, 1.0);
    setMaterial();
    draw_object();
    glPopMatrix();
}

bool GraphicObject::hits(float X, float Y, float Z) {
	float dx = x - X;
	float dy = y - Y;
	float dz = z - Z;
	return ( sqrt(dx * dx + dy * dy + dz * dz) < half_size );
}