#include "Animation.h"

Animation::Animation(std::string A, std::string extention,
					int filecount, int animation_delay, bool loop)
					: name(A), size(filecount-1), delay(animation_delay), looping(loop) {
	init();
	for (int i=0; i < filecount; ++i) {
		std::string file = std::to_string(i) + extention;
		Texture t(name, name + "/" + file);
		animation.push_back(t);
	}
	start();
}

void Animation::init()  { current = 0; timer = 0;	}
void Animation::start() { running = true;			}
void Animation::stop()  { running = false;			}

void Animation::Bind() {
	update();
	animation.at(current).Bind();
}

void Animation::update() {
	if (running) {
		++timer;
		if (timer > delay) {
			timer = 0;
			++current;
		}
		// after last animation
		if (current > size) {
			current = 0;
			if (!looping) stop();
		}
	}
}