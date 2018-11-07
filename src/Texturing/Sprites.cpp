#include "Sprites.h"

Sprites::Sprites() {
	textures.push_back(Texture("Ground_normal", "World/ground.jpg"));
	textures.push_back(Texture("Skybox_normal", "World/skybox.jpg"));
	textures.push_back(Texture("Particle", "Firework/particle.tga"));
	textures.push_back(Texture("Grass", "World/grass.png"));
	textures.push_back(Texture("Flower", "World/flower.png"));

	animations.push_back(Animation("Enemy", ".tga", 2, 20, true));
	animations.push_back(Animation("Boss", ".png", 4, 20, true));
	animations.push_back(Animation("Rocket", ".png", 2, 15, true));
	animations.push_back(Animation("Explosion", ".tga", 16, 2, false));
	animations.push_back(Animation("Heart", ".png", 4, 30, true));
	animations.push_back(Animation("Tutorial", ".png", 1, 1, false));

	Animation cannon("Cannon", ".png", 8, 2, false);
	cannon.stop();
	animations.push_back(cannon);

	int rnd = rand() % 5;
	Texture car("Car", "Cars/" + std::to_string(rnd) + ".bmp");
	textures.push_back(car);
}

Animation Sprites::getAnimation(const std::string T) {
	for (Animation a : animations) if (a.name == T) return a;
	printf("Animation name not found for '%s'\n", T.c_str());
	return Animation("", "", 0, 0, false);
}

Texture* Sprites::getTexture(const std::string T) {
	for (Texture &t : textures) if (t.name == T) return &t;
	printf("Texture name not found for '%s'\n", T.c_str());
	return NULL;
}

Sprites::~Sprites() {
	textures.clear();
}