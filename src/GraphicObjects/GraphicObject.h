#pragma once

#include "GL/glew.h"
#include "GL/glut.h"

#include <string>
#include <math.h>
#define USE_MATH_DEFINES

class GraphicObject {
	public:
		void draw();
		virtual void setMaterial() = 0;
		virtual void move() = 0;
		void setPosition(float X, float Y, float Z)				{ x  = X;  y  = Y;  z  = Z;  }
		void setRotation(float XR, float YR, float ZR)			{ xr = XR; yr = YR; zr = ZR; }
		void setPositionRelative(float X, float Y, float Z)		{ x += X;  y += Y;  z += Z;  }
		void setRotationRelative(float XR, float YR, float ZR)	{ xr+= XR; yr+= YR; zr+= ZR; }
		void RotateToPoint(float R) 							{ yr = -R; }
		bool hits(float X, float Y, float Z);
		virtual ~GraphicObject() {}
	private:
		virtual void draw_object() = 0;
	public:
		const std::string name;
		float size, half_size;
		float x, y, z;
		float xr, yr, zr;
};