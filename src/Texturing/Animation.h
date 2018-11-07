#pragma once

#include "Texture.h"

#include <string>
#include <vector>

class Animation {
	public:
		Animation(std::string A, std::string extention, 
					int size, int animation_delay, bool loop);
		void init();
		void start();
		void stop();
		void Bind();
		bool running;
		std::string name;
	private:
		void update();
	private:
		std::vector<Texture> animation;
		int current, size, delay, timer;
		bool looping;
};