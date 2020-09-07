#include <cmath>

#include "Global.h"
#include "QSS.h"
#include "ParallaxLayer.h"
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Shot.h"
#include "Score.h"
#include "Pool.h"
#include "SDL_mixer.h"

QSS::QSS() : Game::Game(GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT) {
	loadTextureAtlas(ASSETS_DIR ATLAS_JSON_FILE, ASSETS_DIR ATLAS_PNG_FILE);
	playMusic(ASSETS_DIR MUSIC_FILE);
	initParallax();
	initPools();
	initSounds();
	initScore();
	initPlayer();
}

QSS::~QSS() {
}

void QSS::initParallax() {
	int posY[] = { BACKGROUND_0_POS_Y, BACKGROUND_1_POS_Y, BACKGROUND_2_POS_Y, BACKGROUND_3_POS_Y, BACKGROUND_4_POS_Y };
	const char* fileNames[] = { BACKGROUND_0_TEXTURE, BACKGROUND_1_TEXTURE, BACKGROUND_2_TEXTURE, BACKGROUND_3_TEXTURE, BACKGROUND_4_TEXTURE };

	for (int i = 0; i < NUM_PARALLAX_LAYERS; i++) {
		int speed = i == 0 ? 0 : std::pow(2, i) * PARALLAX_SPEED;
		addGameObject(new ParallaxLayer(posY[i], i, fileNames[i], speed, SCREEN_WIDTH));
	}
}

void QSS::initPools() {
	Pool* shotsPool = new Pool();
	for (int i = 0; i < POOL_SIZE; i++) {
		Shot* shot = new Shot(SHOT_POS_X, SHOT_POS_Y, SHOT_POS_Z, SHOT_TEXTURE);
		addGameObject(shot);
		shotsPool->Add(shot);
	}
	_pools.insert(std::make_pair(Pools::Shots, shotsPool));

	Pool* explosionsPool = new Pool();
	for (int i = 0; i < POOL_SIZE; i++) {
		Explosion* explosion = new Explosion(EXPLOSION_POS_X, EXPLOSION_POS_Y, EXPLOSION_POS_Z, EXPLOSION_TEXTURE);
		addGameObject(explosion);
		explosionsPool->Add(explosion);
	}
	_pools.insert(std::make_pair(Pools::Explosions, explosionsPool));

	Pool* enemiesPool = new Pool();
	for (int i = 0; i < POOL_SIZE; i++) {
		Enemy* enemy = new Enemy(ENEMY_POS_X, ENEMY_POS_Y, ENEMY_POS_Z, ENEMY_TEXTURE, i);
		addGameObject(enemy);
		enemiesPool->Add(enemy);
	}
	_pools.insert(std::make_pair(Pools::Enemies, enemiesPool));

}

void QSS::initSounds() {
	_sounds.clear();
	_sounds.insert(std::make_pair(Sounds::Explosion, Mix_LoadWAV(ASSETS_DIR SOUND_EXPLOSION_FILE)));
	_sounds.insert(std::make_pair(Sounds::Laser, Mix_LoadWAV(ASSETS_DIR SOUND_LASER_FILE)));
}

void QSS::spawnEnemies() {
	Pool* enemiesPool = getPool(Pools::Enemies);
	int y = (rand() % SPAWN_ENEMY_HEIGHT) + SPAWN_ENEMY_PADDING;

	for (int i = 0; i < NUM_ENEMIES; i++) {
		Enemy* enemy = (Enemy*) enemiesPool->Get();
		enemy->spawn(SCREEN_WIDTH, y);
	}
}

void QSS::update() {
	if (frame > SPAWN_INTERVAL) {
		frame = 0;
		spawnEnemies();
	}

	Game::update();
	frame++;
}

void QSS::initScore() {
	Score::reset();
	addGameObject(new Score(SCORE_POS_X, SCORE_POS_Y, SCORE_POS_Z, SCORE_TEXTURE));
}

void QSS::initPlayer() {
	addGameObject(new Player(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z, PLAYER_TEXTURE));
}