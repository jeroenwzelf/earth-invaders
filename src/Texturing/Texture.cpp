#include "Texture.h"

Texture::Texture(const std::string T, const std::string &fileName) {
	name = T;
	const std::string filePath = "src/media/";
	texturebuff = SOIL_load_OGL_texture
	(
		(filePath + fileName).c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y
	);
	if (texturebuff == 0) {
		printf( "SOIL loading error: '%s'", SOIL_last_result() );
		printf(" at: '%s'\n", (filePath + fileName).c_str());
	}
}

void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, texturebuff);
}