#include <math.h>
#include "Global.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Game.h"
#include "Pool.h"
#include "Score.h"
#include "SDL.h"
#include "SDL_mixer.h"

Enemy::Enemy(float x, float y, float z, const char* fileName, int index) : GameObject::GameObject(x, y, z, fileName, ZOOM_X2, false) {
	_collisionLayer = CollisionLayer::Enemy;
	_index = index;
}

Enemy::~Enemy() {}

void Enemy::init(Game* game) {
	GameObject::init(game);
	_explosionsPool = _game->getPool(Pools::Explosions);
	_fxExplosion = _game->getSound(Sounds::Explosion);
}

void Enemy::update() {
	if (!_isEnabled) {
		return;
	}

	Uint32 ticks = SDL_GetTicks();

	_y = _startY + (ENEMY_WAVE_AMPLITUDE * sin((ticks + (_index * ENEMY_WAVE_SEPARATION)) / HUNDRED_PERCENT));
	_x -= _speed;

	if (_x < ENEMY_LEFT_EDGE) {
		setEnabled(false);
	}
	
	GameObject* shot = _game->collision(this, CollisionLayer::Shot);
	if (shot != nullptr) {
		GameObject* explosion = _explosionsPool->Get();
		explosion->setPosition(_x, _y);
		explosion->setEnabled(true);
		Mix_PlayChannel(-1, _fxExplosion, 0);
		setEnabled(false);
		shot->setEnabled(false);
		Score::add(NUM_POINTS);
	}

	GameObject::update();
}

void Enemy::spawn(float x, float y) {
	setPosition(x, y);
	_startY = y;
	_x = x + (_index * ENEMY_HORIZONTAL_SPACE);
	setEnabled(true);
}