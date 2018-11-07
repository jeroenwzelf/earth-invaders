#include "Game.h"

// sin(), cos(), INT_MAX
#include <limits.h>
#include <math.h>
#define _USE_MATH_DEFINES

#define MAX_HEALTH 3
#define SHOT_DELAY 5
#define NUM_START_ENEMIES 10

float random(float LO, float HI) {
	return ( LO + static_cast <float>(rand()) / ( static_cast <float>(RAND_MAX/(HI-LO)) ) );
}

Game::Game(float screen_w, float screen_h) {
	// init light, hud, inputHandler
	lighthandler.clear();
	lighthandler.enable_main_light();
	hud = std::make_shared<HUD>(screen_w, screen_h, &sprites);
	inputHandler = std::make_shared<InputHandler>();

	// init game objects
	fireworks = std::make_shared<Fireworks>(sprites.getTexture("Particle"));
	init_camera(); spawn_static_objects(); spawn_car(); set_health(MAX_HEALTH);

	game_end = true; lost = false;
	hud->intro_message_show();
}

void Game::new_game() {
	game_end = false; lost = false; paused = false;
	hud->intro_message_remove();
	hud->setTooltip("", 0);

	// reset objects
	enemies.clear(); start_wave(1);
	clear_objects(); init_car();

	// reset state
	set_health(MAX_HEALTH); set_score(0);
	shooting_timer = 0; alert_timer = 0;
	init_camera();
	music_play();
	soundengine.play_startup();
}

void Game::init_camera() {
	g_posX = 0.0;
	g_posY = 8.0;
	g_posZ = 50.0;
	g_orientation = 0.0;
}

void Game::init_car() {
	cannon->setPosition(0.0f, 4.8f, 0.0f);
	car->setPosition(0.0f, 0.0f, 0.0f);
}

void Game::spawn_car() {
	cannon = std::make_shared<Cannon>(sprites.getAnimation("Cannon"));
	car = std::make_shared<Car>(sprites.getTexture("Car"));
	init_car();
}

void Game::spawn_static_objects() {
	static_objects.clear();
	// Ground
	std::shared_ptr<Ground> ground = std::make_shared<Ground>(50, sprites.getTexture("Ground_normal"));
	static_objects.push_back(ground);
	// Grass
	for (int i=0; i < 80; ++i) {
		int rnd = rand() % 2;
		std::shared_ptr<Nature> n;
		if (rnd == 1) n = std::make_shared<Nature>(sprites.getTexture("Grass"), 5.0f);
		else n = std::make_shared<Nature>(sprites.getTexture("Flower"), 3.0f);
		nature.push_back(n);
	}
	// Skybox
	std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>(sprites.getTexture("Skybox_normal"));
	static_objects.push_back(skybox);
}

void Game::spawn_enemies(int num) {
	for (int i=0; i < num; ++i) {
		std::shared_ptr<Enemy> E = std::make_shared<Enemy>(sprites.getAnimation("Enemy"));
		enemies.push_back(E);
	}
}

void Game::spawn_boss() {
	std::shared_ptr<Boss> B = std::make_shared<Boss>(sprites.getAnimation("Boss"));
	enemies.push_back(B);
}

void Game::clear_objects() { projectiles.clear(); explosions.clear(); fireworks->clear(); }

void Game::start_wave(int w) {
	enemies.clear();
	wave = w;
	// boss waves
	if (w % 3 == 0) {
		soundengine.boss_cry();
		bosswave = true;
		alert_timer = 70;
		spawn_boss();
		if (music_playing) music_play();
	}
	// normal waves
	else {
		soundengine.play_newwave();
		spawn_enemies(w * 10);
		if (bosswave) {
			bosswave = false;
			if (music_playing) music_play();
		}
	}
	hud->setWave(w, bosswave);
}

void Game::alert() {
	soundengine.play_alert();
	lighthandler.new_light(0, 10, 0, 5.0f, 0.0f, 0.0f, 1.0f, 10);
	hud->setTooltip("ALERT! ALERT! ALERT!", 40);
}

void Game::moveCannonRelativeToCam(const bool &to_left) {
	float x, z;
	if (to_left) {
		x = cos((g_orientation + 180) / 180.0 * M_PI);
		z = sin((g_orientation + 180) / 180.0 * M_PI);
		car->RotateToPoint(g_orientation + 180);
	}
	else {
		x = cos(g_orientation / 180.0 * M_PI);
		z = sin(g_orientation / 180.0 * M_PI);
		car->RotateToPoint(g_orientation);
	}
	cannon->setPositionRelative(x, 0, z);
	car->setPositionRelative(x, 0, z);
}

void Game::updateSpriteRotations() {
	cannon->RotateToPoint(g_orientation);
	for (auto i : enemies)
		i->RotateToPoint(g_orientation);
	for (auto i : projectiles)
		i->RotateToPoint(g_orientation);
	for (auto i : explosions)
		i->RotateToPoint(g_orientation);
	fireworks->RotateToPoint(g_orientation);
}

void Game::handleinput() {
	if (!game_end) {
		// keypress continuous actions (in keys_down)
		for (unsigned int i = 0; i < inputHandler->keys_down.size(); ++i) {
			unsigned char key = inputHandler->keys_down.at(i);
			switch(key) {
				case 'd':	// move right
					if (paused) {
						g_orientation--;
						g_posX = 50 * cos((g_orientation + 90) / 180.0 * M_PI);
						g_posZ = 50 * sin((g_orientation + 90) / 180.0 * M_PI);
					}
					else { moveCannonRelativeToCam(false); }
					break;
				case 'a':	// move left
					if (paused) {
						g_orientation++;
						g_posX = 50 * cos((g_orientation + 90) / 180.0 * M_PI);
						g_posZ = 50 * sin((g_orientation + 90) / 180.0 * M_PI);
					}
					else { moveCannonRelativeToCam(true); }
					break;
				case 'r':	// reset car
					init_car();
					break;
				case 'f':	// shoot cannon
					if (shooting_timer == 0 && !paused) shoot();
					break;
			}
		}
		// keypress event actions (in keys_pressed)
		for (unsigned int i = 0; i < inputHandler->keys_pressed.size(); ++i) {
			unsigned char key = inputHandler->keys_pressed.at(i);
			switch(key) {
				case 'm':	// play/stop music
					if (!music_playing) music_play();
					else music_stop();
					break;
				case 'p':	// pause time
					if (paused) unpause();
					else pause();
					break;
				case '=': next_wave(); break; // cheater!
				case 'q':	// quit
				case 27 :
					exit(0);
					break;
			}
		}
	}
	// keypress event actions for before/after game
	else {
		for (unsigned int i = 0; i < inputHandler->keys_pressed.size(); ++i) {
			unsigned char key = inputHandler->keys_pressed.at(i);
			switch(key) {
				case 'r': new_game(); break;
				case 'q':
				case  27: exit(0); break;
			}
		}
	}
	inputHandler->keys_pressed.clear();
	updateSpriteRotations();
	glutPostRedisplay();
}

void Game::pause() {
	paused = true;
	soundengine.play_pause();
	for (auto i : projectiles)	dynamic_cast<Rocket*>(i.get())->animation.stop();
	for (auto i : explosions)	dynamic_cast<Explosion*>(i.get())->animation.stop();
	if (bosswave)	for (auto i : enemies)	dynamic_cast<Boss*> (i.get())->animation.stop();
	else 			for (auto i : enemies)	dynamic_cast<Enemy*> (i.get())->animation.stop();
}

void Game::unpause() {
	paused = false;
	soundengine.play_pause();
	for (auto i : projectiles)	dynamic_cast<Rocket*>(i.get())->animation.start();
	for (auto i : explosions)	dynamic_cast<Explosion*>(i.get())->animation.start();
	if (bosswave)	for (auto i : enemies)	dynamic_cast<Boss*> (i.get())->animation.start();
	else 			for (auto i : enemies)	dynamic_cast<Enemy*> (i.get())->animation.start();
}

void Game::update_score(int s) { score += s; hud->setScore(score); }
void Game::set_score(int s)    { score  = s; hud->setScore(score); }

void Game::update_health(int h) {
	health += h;
	if (health >= 0) {
		hud->setHealth(health);
		soundengine.play_countdown(health);
	}
}

void Game::set_health(int h) {
	health = h;
	hud->setHealth(health);
}

void Game::shoot() {
	soundengine.play_shot();
	dynamic_cast<Cannon*>(cannon.get())->shoot();
	std::shared_ptr<Rocket> P = std::make_shared<Rocket>(cannon->x, cannon->y+1.0f, cannon->z,
																 sprites.getAnimation("Rocket"));
	projectiles.push_back(P);
	shooting_timer = SHOT_DELAY;
}

void Game::explode(Enemy *P) {
	soundengine.play_explosion();
	update_score(P->value);
	lighthandler.new_light(P->x, P->y, P->z, P->r / 0.5, P->g / 0.5, P->b / 0.5, 0.1f, 8);
	fireworks->FireworksAt(P->x, P->y, P->z, P->r, P->g, P->b);
	std::shared_ptr<Explosion> E = std::make_shared<Explosion>(P->x, P->y, P->z,
															   sprites.getAnimation("Explosion"), 0);
	explosions.push_back(E);
}

void Game::explode(Boss *B) {
	soundengine.boss_death();
	update_score(B->value);
	lighthandler.new_light(B->x, B->y, B->z, B->r / 0.5, B->g / 0.5, B->b / 0.5, 0.1f, 8);
	fireworks->FireworksAt(B->x, B->y, B->z, B->r, B->g, B->b);
	// Lots of epic explosions!
	for (int i=0; i < 20; ++i) {
		int rnd = rand() % 160;
		int rnd_x = (rand() % 40) - 20;
		int rnd_y = (rand() % 20) - 10;
		int rnd_z = (rand() % 40) - 20;
		std::shared_ptr<Explosion> E = std::make_shared<Explosion>(B->x+rnd_x, B->y+rnd_y, B->z+rnd_z,
															   sprites.getAnimation("Explosion"), rnd);
		explosions.push_back(E);
	}
	soundengine.play_explosions();
}

void Game::damage(Boss *B, std::shared_ptr<GraphicObject> P) {
	B->health -= 5;
	hud->setBossHealth(B->health);
	std::shared_ptr<Explosion> E = std::make_shared<Explosion>(P->x, P->y, P->z,
															   sprites.getAnimation("Explosion"), 0);
	explosions.push_back(E);
	soundengine.play_explosion();
}

void Game::music_play() {
	if (music_playing) soundengine.stop_music();
	soundengine.play_music(bosswave);
	music_playing = true;
}

void Game::music_stop() {
	soundengine.stop_music();
	music_playing = false;
}

void Game::lose() {
	// lose, but continue one frame so the HUD tooltip is updated
	if (!lost) {
		lost = true;
		if (highscorehandler.is_highscore((unsigned int)score) != INT_MAX) {
			soundengine.play_win();
			hud->setTooltip("You got a high score! Please insert your name in the terminal. (ALT+TAB) ", -1);
		}
	}
	else {
		music_stop();
		pause();
		game_end = true;
		highscorehandler.new_score(score);
		hud->setTooltip("Press R to start a new game. ", -1);
	}
}

void Game::update(float time) {
	if (!game_end) {
		if (health == 0) lose();
		out_of_bounds_check();
		// kill explosions that are finished animating
		for (unsigned int i=0; i < explosions.size(); ++i) {
			if (explosions.at(i)->size == 0) explosions.erase(explosions.begin() + i);
		}
		// move all enemies and check if they're touching the ground
		for (unsigned int i=0; i < enemies.size(); ++i) {
			enemies.at(i)->move();
			if (enemies.at(i)->y < 1) {
				enemies.erase(enemies.begin() + i);
				if (bosswave) set_health(0);
				else update_health(-1);
			}
		}
		lighthandler.update();
		fireworks->update(time);
		// move all projectiles
		for (unsigned int i=0; i < projectiles.size(); ++i) {
			std::shared_ptr<GraphicObject> P = projectiles.at(i);
			P->move();
			// remove projectiles that are too high
			if (P->y > 100.0f) projectiles.erase(projectiles.begin() + i);
			else {
				// projectiles deal damage when they hit a boss
				unsigned int j=0;
				if (bosswave) {
					while (j < enemies.size()) {
						Boss* B = dynamic_cast<Boss*>( enemies.at(j).get() );
						if (enemies.at(j)->hits(P->x, P->y, P->z)) {
							damage(B, P);
							if (B->health <= 0) {
								explode(B);
								enemies.erase(enemies.begin() + j);
							}
							projectiles.erase(projectiles.begin() + i);
							++i;
						}
						++j;
					}
				}
				// explode projectiles that hit enemies
				else {
					while (j < enemies.size()) {
						auto enemy = enemies.at(j);
						if (enemy->hits(P->x, P->y, P->z)) {
							explode( dynamic_cast<Enemy*>( enemy.get() ) );
							projectiles.erase(projectiles.begin() + i);
							enemies.erase(enemies.begin() + j);
							++i;
						}
						++j;
					}
				}
			}
		}
		if (alert_timer > 0 && alert_timer-- % 16 == 0) alert();
		if (shooting_timer > 0) --shooting_timer;
		if (enemies.empty()) next_wave();
	}
}

void Game::next_wave() {
	hud->setTooltip("Wave " + std::to_string(wave) + " survived! ", 100);
	update_score(wave * 100);
	start_wave(++wave);
}

void Game::out_of_bounds_check() {
	const static float out_of_bounds_radius = 80.0f;
	float x = car->x; float y = car->y;
	float distance = sqrt(x * x + y * y);
	if ( distance > out_of_bounds_radius )
		hud->setTooltip("Press R to reset your cannon! ", 20);
}

void Game::setCameraPos() {
	glRotatef(g_orientation, 0.0, 1.0, 0.0);
	glTranslatef(-g_posX, -g_posY, -g_posZ);
}