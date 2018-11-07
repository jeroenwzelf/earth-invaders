#pragma once

// Helpers
#include "HighscoreHandler.h"
#include "InputHandler.h"
#include "LightHandler.h"
#include "SoundEngine.h"
#include "Sprites.h"
#include "HUD.h"

// Objects
#include "GraphicObject.h"
#include "Cannon.h"
#include "Car.h"
#include "Enemy.h"
#include "Boss.h"
#include "Explosion.h"
#include "Ground.h" 
#include "Nature.h"
#include "Rocket.h"
#include "Skybox.h"

// Fireworks
#include "Fireworks.h"

typedef std::vector<std::shared_ptr<GraphicObject>> GraphicObject_Vector;

class Game {
	public:
		Game(float screen_w, float screen_h);
		void update(float time);
		void handleinput();
		void setCameraPos();
	private:
		// Initialisers
		void new_game();

		void init_camera();
		void init_car();
		void spawn_static_objects();
		void spawn_enemies(int num);
		void spawn_boss();
		void spawn_car();
		void clear_objects();

		// Updates
		void update_score(int s);
		void set_score(int s);
		void update_health(int h);
		void set_health(int h);

		void updateSpriteRotations();
		void out_of_bounds_check();

		// user generated actions
		void lose();
		void shoot();
		void pause();
		void unpause();
		void music_play();
		void music_stop();
		void next_wave();
		void start_wave(int w);
		void alert();
		void explode(Enemy *P);
		void explode(Boss *B);
		void damage(Boss *B, std::shared_ptr<GraphicObject> P);
		void moveCannonRelativeToCam(const bool &to_left);
	public:
		float g_posX, g_posY, g_posZ, g_orientation; // Camera
		// Game state
		bool paused;
		bool game_end, lost;
		int health;
		int score;
		int wave;
		bool bosswave;

		// Objects
		std::shared_ptr<GraphicObject> car;
		std::shared_ptr<GraphicObject> cannon;
		std::shared_ptr<Fireworks> fireworks;
		GraphicObject_Vector static_objects;
		GraphicObject_Vector nature;
		GraphicObject_Vector projectiles;
		GraphicObject_Vector explosions;
		GraphicObject_Vector enemies;

		// Helpers
		Sprites sprites;
		SoundEngine soundengine;
		LightHandler lighthandler;
		HighscoreHandler highscorehandler;
		
		std::shared_ptr<HUD> hud;
		std::shared_ptr<InputHandler> inputHandler;
	private:
		bool music_playing;
		int shooting_timer;
		int alert_timer;
};