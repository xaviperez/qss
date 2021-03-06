#include "Player.h"
#include "Game.h"
#include "Input.h"
#include "Shot.h"
#include "Pool.h"
#include "Score.h"
#include "Global.h"
#include "SDL_mixer.h"

Player::Player(float x, float y, float z, const char* fileName) : GameObject::GameObject(x, y, z, fileName, ZOOM_X2) {
	_collisionLayer = CollisionLayer::Player;

	state = PlayerState::Spawn;
	_x = SPAWN_X;
}

Player::~Player() {}

void Player::init(Game* game) {
	GameObject::init(game);
	_shotsPool = _game->getPool(Pools::Shots);
	_explosionsPool = _game->getPool(Pools::Explosions);
	_fxShot = _game->getSound(Sounds::Laser);
	_fxExplosion = _game->getSound(Sounds::Explosion);
}

void Player::update() {
	if (!_isEnabled) {
		return;
	}

	if (state == PlayerState::Spawn) {
		spawn();
	}

	if (state == PlayerState::Alive) {
		_x += Input::getHorizontalAxis() * _speed;
		_y += Input::getVerticalAxis() * _speed;

		if (Input::isButtonDown()) {
			shoot();
		}

		if (_game->collision(this, CollisionLayer::Enemy) != nullptr) {
			die();
		}
	}

	if (state == PlayerState::Dead) {
		if (_frame > DIE_DURATION) {
			_frame = 0;
			state = PlayerState::Spawn;
		}
	}

	GameObject::update();
	_frame++;
}

void Player::shoot() {
	Uint32 ticks = SDL_GetTicks();
	
	if (ticks - _lastShotTicks < 250) {
		return;
	}

	_lastShotTicks = ticks;

	GameObject* shot = _shotsPool->Get();
	shot->setPosition(_x, _y);
	shot->setEnabled(true);
	Mix_PlayChannel(-1, _fxShot, 0);
}

void Player::die() {
	state = PlayerState::Dead;
	GameObject* explosion = _explosionsPool->Get();
	explosion->setPosition(_x, _y);
	explosion->setEnabled(true);
	Mix_PlayChannel(-1, _fxExplosion, 0);
	_x = SPAWN_X;
	_frame = 0;
	Score::reset();
}

void Player::spawn() {
	_isVisible = _frame % 3 == 0;
	_x += _speed;

	if (_frame > SPAWN_DURATION) {
		_frame = 0;
		state = PlayerState::Alive;
		_isVisible = true;
	}
}