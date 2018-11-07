#include "HUDitem.h"

#define FONT GLUT_BITMAP_8_BY_13

HUDitem::HUDitem(float w, float h) {
	setScreenSize(w, h);
	active = false;
}

void HUDitem::draw_image(float x, float y, float w, float h, Animation* image) {
	// center box coordinates
	x = x + ( -w / 2.0f );
	y = y + ( -h / 2.0f );
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0f, 1.0f, 1.0f);
	image->Bind();
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2i(  x ,	 y	);
		glTexCoord2f(0.0, 0.0); glVertex2i(  x ,	y+h );
		glTexCoord2f(1.0, 0.0); glVertex2i( x+w,	y+h );
		glTexCoord2f(1.0, 1.0); glVertex2i( x+w,	 y	);
	glEnd();

    glDisable(GL_TEXTURE_2D);
}

void HUDitem::draw_image(float x, float y, float w, float h, Texture* image) {
	// center box coordinates
	x = x + ( -w / 2.0f );
	y = y + ( -h / 2.0f );
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0f, 1.0f, 1.0f);
	image->Bind();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2i(  x ,	 y	);
		glTexCoord2f(1.0, 0.0); glVertex2i(  x ,	y+h );
		glTexCoord2f(1.0, 1.0); glVertex2i( x+w,	y+h );
		glTexCoord2f(0.0, 1.0); glVertex2i( x+w,	 y	);
	glEnd();

    glDisable(GL_TEXTURE_2D);
}

void HUDitem::draw_box(float x, float y, float w, float h, float r, float g, float b, bool center) {
	// center box coordinates
	if (center) {
		x = x + ( -w / 2.0f );
		y = y + ( -h / 2.0f );
	}

	// Inside of box
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
		glVertex2i(  x ,	 y	);
		glVertex2i(  x ,	y+h );
		glVertex2i( x+w,	y+h );
		glVertex2i( x+w,	 y	);
	glEnd();

	// Outside of box
	glLineWidth(3);

	glColor3f(std::max(r + 0.2f, 1.0f), std::max(g + 0.2f, 1.0f), std::max(b + 0.2f, 1.0f));
	glBegin(GL_LINE_STRIP);
		glVertex2i(	x+w,	 y	);
		glVertex2i(  x , 	 y	);
		glVertex2i(  x , 	y+h );
	glEnd();

	glColor3f(std::min(r - 0.2f, 0.0f), std::min(g - 0.2f, 0.0f), std::min(b - 0.2f, 0.0f));
	glBegin(GL_LINE_STRIP);
		glVertex2i(  x ,	y+h );
		glVertex2i( x+w,	y+h );
		glVertex2i( x+w,	 y	);
	glEnd();

	glLineWidth(1);
}

void HUDitem::draw_paragraph_center(std::vector<std::string> paragraph, float x, float y) {
	float line = 0;
	float paragraphheight = paragraph.size() * FONT_H;
	for (auto i : paragraph) {
		// center line coordinates
		float linewidth = i.size() * FONT_W;
		float x_line = x + (-linewidth / 2.0f);
		float y_line = ( y + (line * FONT_H) ) + ( -paragraphheight / 2.0f ) + (FONT_H) / 1.5;

		draw_text( i, x_line, y_line );
		++line;
	}
}

void HUDitem::draw_text(std::string text, float x, float y) {
	glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(x, y);
    for (char& c : text) {
    	glutBitmapCharacter(FONT, (int)c);
    }
}

void HUDitem::setScreenSize(float w, float h) {
	screen_width = w;
	screen_height = h;
	x_screen = x * screen_width;
	y_screen = y * screen_height;
}