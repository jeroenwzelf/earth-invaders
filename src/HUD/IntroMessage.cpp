#include "IntroMessage.h"

void IntroMessage::init() {
	x = 0.5f; y = 0.5f;
	r = 0.3f; g = 0.3f; b = 0.8f;
	name = "IntroMessage";
	setIntroMessage();
}

void IntroMessage::draw() {
	draw_box(x_screen, y_screen, 800, 800, r, g, b, true);
	draw_paragraph_center(message, x_screen, y_screen);
	draw_image(x_screen, y_screen, 387, 445, &animation);
}

void IntroMessage::setIntroMessage() {
	message.clear();
	message.push_back("!!!ALIEN INVASION ALERT!!!");
	message.push_back("Aliens are invading your beloved Earth!");
	message.push_back("Shoot the aliens before they reach the ground and get the chance to attack by");
	message.push_back("shooting them with your cannon-mounted car.");
	for (int i=0; i < 40; ++i) message.push_back("");	// space for the image
	message.push_back("Earth relies on you to save it!");
	message.push_back("");
	message.push_back("Press R to start the invasion.");
}