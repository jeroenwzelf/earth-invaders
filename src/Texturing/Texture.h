#pragma once

#include "GL/glew.h"
#include "GL/glut.h"

#include "../../lib/SOIL.h"

#include <string>

class Texture {
	public:
		Texture(const std::string T, const std::string &fileName);
		void Bind() const;
		GLuint texturebuff;
		std::string name;
};