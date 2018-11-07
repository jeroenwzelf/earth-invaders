 #pragma once

#include <irrKlang.h>
#include <string>

class SoundEngine {
	public:
		SoundEngine();
		void play_win();
		void play_startup();
		void play_newwave();
		void play_alert();
		void boss_cry();
		void boss_death();
		void play_countdown(int i);
		
		void play_pause();
		void play_shot();
		void play_explosion();
		void play_explosions();

		void play_music(bool boss);
		void stop_music();
		~SoundEngine();
	private:
		const std::string filePath = "src/media/";
		void play_fx(const std::string folder, const std::string fileName);
		irrklang::ISound* music;
		irrklang::ISoundEngine* engine;
};