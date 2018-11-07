#pragma once

#include "Texture.h"
#include "Animation.h"

#include <string>
#include <vector>

class Sprites {
	public:
		Sprites();
		Texture* getTexture(const std::string T);
		Animation getAnimation(const std::string T);
		~Sprites();
	private:
		std::vector<Texture> textures;
		std::vector<Animation> animations;
};