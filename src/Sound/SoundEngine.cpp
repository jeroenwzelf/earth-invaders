#include "SoundEngine.h"

SoundEngine::SoundEngine() {
	engine = irrklang::createIrrKlangDevice();
}

void SoundEngine::play_startup(){ play_fx("", "World/change1.wav"); }
void SoundEngine::play_newwave(){ play_fx("", "World/wave.wav" ); 	}
void SoundEngine::play_alert()  { play_fx("", "World/alert.wav"); 	}
void SoundEngine::play_pause()  { play_fx("", "World/pause.wav"); 	}
void SoundEngine::play_win()	{ play_fx("", "Vox/scored.wav" ); 	}
void SoundEngine::play_shot()	{ play_fx("", "Cannon/shot.wav"); 	}
void SoundEngine::boss_cry()	{ play_fx("", "Boss/cry.wav"); 		}
void SoundEngine::boss_death()	{ play_fx("", "Boss/cry_slow.wav"); }

void SoundEngine::play_explosions() { play_fx("", "Explosion/explosions.wav"); }

void SoundEngine::play_explosion() {
	const std::string folder = "Explosion/";
	int rnd = rand() % 2;
	if (rnd == 1)	play_fx(folder, "explode1.wav");
	else 			play_fx(folder, "explode2.wav");
}

void SoundEngine::play_countdown(int i) {
	const std::string folder = "Vox/";
	switch(i) {
		case 0: play_fx(folder, "count0.wav"); break;
		case 1: play_fx(folder, "count1.wav"); break;
		case 2: play_fx(folder, "count2.wav"); break;
	}
}

void SoundEngine::play_music(bool boss) {
	std::string fileName;
	if (boss) fileName = filePath + "Music/level11.ogg";
	else fileName = filePath + "Music/AcidicInvaders.ogg";
	music = engine->play2D(fileName.c_str(), true, false, true);
}
void SoundEngine::stop_music() {
	if (music) {
		music->stop();
		music->drop();
		music = 0; // music->roll() ?
	}
}

void SoundEngine::play_fx(const std::string folder, const std::string fileName) {
	const std::string file = filePath + folder + fileName;
	engine->play2D(file.c_str(), false, false, false);
}

SoundEngine::~SoundEngine() {
	engine->drop();
}