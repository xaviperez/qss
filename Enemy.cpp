#include <math.h>
#include "Enemy.h"
#include "GameObject.h"
#include "Pool.h"
#include "Score.h"

Enemy::Enemy(float x, float y, float z, std::string fileName, int index) : GameObject::GameObject(x, y, z, fileName, 2.0, false) {
	_collisionLayer = "enemy";
	_index = index;
}

Enemy::~Enemy() {}

void Enemy::init(Game* game) {
	GameObject::init(game);
	_explosionsPool = _game->getPool("explosions");
	_fxExplosion = _game->getSound("explosion");
}

void Enemy::update() {
	if (!_isEnabled) {
		return;
	}

	Uint32 ticks = SDL_GetTicks();

	_y = _startY + (25 * sin((ticks + (_index * 120)) / (float)100));
	_x -= _speed;

	if (_x < -64) {
		setEnabled(false);
	}
	
	GameObject* shot = _game->collision(this, "shot");
	if (shot != nullptr) {
		GameObject* explosion = _explosionsPool->Get();
		explosion->setPosition(_x, _y);
		explosion->setEnabled(true);
		Mix_PlayChannel(-1, _fxExplosion, 0);
		setEnabled(false);
		shot->setEnabled(false);
		Score::add(3);
	}

	GameObject::update();
}

void Enemy::spawn(float x, float y) {
	setPosition(x, y);
	_startY = y;
	_x = x + (_index * 64);
	setEnabled(true);
}