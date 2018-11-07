#include "HUD.h"

#include "Tooltip.h"
#include "Health.h"
#include "BossHealth.h"
#include "PointCounter.h"
#include "WaveCounter.h"
#include "IntroMessage.h"

HUD::HUD(float w, float h, Sprites* S) : sprites(S) {
	screen_width = w; screen_height = h;

	std::shared_ptr<IntroMessage> intro_message = std::make_shared<IntroMessage>(w, h, sprites->getAnimation("Tutorial"));
	HUDitems.push_back(intro_message);

	std::shared_ptr<Tooltip> tooltip = std::make_shared<Tooltip>(w, h);
	HUDitems.push_back(tooltip);

	std::shared_ptr<PointCounter> pointcounter = std::make_shared<PointCounter>(w, h);
	pointcounter->active = true;
	HUDitems.push_back(pointcounter);

	std::shared_ptr<WaveCounter> wavecounter = std::make_shared<WaveCounter>(w, h);
	wavecounter->active = true;
	HUDitems.push_back(wavecounter);

	std::shared_ptr<Health> health = std::make_shared<Health>(w, h, sprites->getAnimation("Heart"));
	health->active = true;
	HUDitems.push_back(health);

	std::shared_ptr<BossHealth> bosshealth = std::make_shared<BossHealth>(w, h);
	HUDitems.push_back(bosshealth);

	init();
}

void HUD::init() { for (auto i : HUDitems) i->init(); }
void HUD::draw() { for (auto i : HUDitems) if (i->active) i->draw(); }

void HUD::setScore(int score) {
	PointCounter* pointcounter = dynamic_cast<PointCounter*>(getHUDitem("PointCounter"));
	pointcounter->setPoints(score);
}

void HUD::setWave(int wave, bool bosswave) {
	BossHealth* bosshealth = dynamic_cast<BossHealth*>(getHUDitem("BossHealth"));
	if (bosswave) {
		bosshealth->update_health(100);
		bosshealth->active = true;
	}
	else bosshealth->active = false;
	WaveCounter* wavecounter = dynamic_cast<WaveCounter*>(getHUDitem("WaveCounter"));
	wavecounter->setWave(wave);
}

void HUD::intro_message_show() {
	getHUDitem("IntroMessage")->active = true;
}

void HUD::intro_message_remove() {
	getHUDitem("IntroMessage")->active = false;
}

void HUD::setTooltip(std::string text, int time) {
	Tooltip* tooltip = dynamic_cast<Tooltip*>(getHUDitem("Tooltip"));
	if (text.empty()) tooltip->active = false;
	else {
		tooltip->setTooltip(text, time);
		tooltip->active = true;
	}
}

void HUD::setBossHealth(float h) {
	dynamic_cast<BossHealth*>(getHUDitem("BossHealth"))->update_health(h);
}

void HUD::setHealth(int h) {
	dynamic_cast<Health*>(getHUDitem("Health"))->health = h;
}

void HUD::setScreenSize(float w, float h) {
	screen_width = w;
	screen_height = h;
	for (auto i : HUDitems) {
		i->setScreenSize(screen_width, screen_height);
	}
}

HUDitem* HUD::getHUDitem(const std::string item) {
	for (auto i : HUDitems) {
		if (i->name == item) return i.get();
	}
	printf("HUD item name not found for '%s'\n", item.c_str());
	return NULL;
}