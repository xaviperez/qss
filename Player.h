#pragma once

#include "GameObject.h"
#include "PlayerState.h"

class Mix_Chunk;
class Pool;

class Player : public GameObject {

public:

	Player(float x, float y, float z, const char* fileName);
	~Player();

	PlayerState state;

	void init(Game* game) override;
	void update() override;

private:
	const Uint32 SPAWN_DURATION = 60;
	const Uint32 DIE_DURATION = 60;
	const float SPAWN_X = -64.0;
	int _frame = 0;
	float _speed = 3.0;
	Uint32 _lastShotTicks = 0;
	Mix_Chunk* _fxShot;
	Mix_Chunk* _fxExplosion;
	Pool* _shotsPool;
	Pool* _explosionsPool;
	void shoot();
	void die();
	void spawn();
};
 