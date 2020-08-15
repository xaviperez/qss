#include <cstdlib>
#include "QSS.h"
#include "ParallaxLayer.h"
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Shot.h"
#include "Score.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

QSS::QSS() : Game::Game("Quick Side Scroller", SCREEN_WIDTH, SCREEN_HEIGHT) {
	loadTextureAtlas("assets/qss.json");
	playMusic("assets/music.ogg");
	initParallax();
	initPools();
	initSounds();
	initScore();

	Player* player = new Player(50, 200, 10, "ship.png");
	addGameObject(player);
}

QSS::~QSS() {}

void QSS::initParallax() {
	int posY[] = { 0, 284, 266, 366, 347 };
	std::string fileNames[] = { "bg0.png", "bg1.png", "bg2.png", "bg3.png", "fg.png" };
	int numLayers = sizeof(posY) / sizeof(posY[0]);

	for (int i = 0; i < numLayers; i++) {
		int speed = i == 0 ? 0 : std::pow(2, i) * 30;
		addGameObject(new ParallaxLayer(posY[i], i, fileNames[i], speed, SCREEN_WIDTH));
	}
}

void QSS::initPools() {
	Pool* shotsPool = new Pool();
	for (int i = 0; i < 10; i++) {
		Shot* shot = new Shot(0, 0, 9, "shot.png");
		addGameObject(shot);
		shotsPool->Add(shot);
	}
	_pools.insert(std::make_pair("shots", shotsPool));

	Pool* explosionsPool = new Pool();
	for (int i = 0; i < 10; i++) {
		Explosion* explosion = new Explosion(0, 0, 11, "explosion.png");
		addGameObject(explosion);
		explosionsPool->Add(explosion);
	}
	_pools.insert(std::make_pair("explosions", explosionsPool));

	Pool* enemiesPool = new Pool();
	for (int i = 0; i < 10; i++) {
		Enemy* enemy = new Enemy(0, 0, 8, "enemy.png", i);
		addGameObject(enemy);
		enemiesPool->Add(enemy);
	}
	_pools.insert(std::make_pair("enemies", enemiesPool));

}

void QSS::initSounds() {
	_sounds.clear();
	_sounds.insert(std::make_pair("explosion", Mix_LoadWAV("assets/explosion.wav")));
	_sounds.insert(std::make_pair("laser", Mix_LoadWAV("assets/laser.wav")));
}

void QSS::spawnEnemies() {
	Pool* enemiesPool = getPool("enemies");
	int y = (rand() % 350) + 20;

	for (int i = 0; i < 10; i++) {
		Enemy* enemy = (Enemy*) enemiesPool->Get();
		enemy->spawn(640, y);
	}
}

void QSS::update() {
	if (_frame > SPAWN_INTERVAL) {
		_frame = 0;
		spawnEnemies();
	}

	Game::update();
	_frame++;
}

void QSS::initScore() {
	Score::reset();

	Score* score = new Score(508, 10, 20, "font.png");
	addGameObject(score);
}