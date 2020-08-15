#pragma once

#include "GameObject.h"

class Enemy : public GameObject {

public:

	Enemy(float x, float y, float z, std::string fileName, int index);
	~Enemy();

	void update() override;
	void init(Game* game) override;
	void spawn(float x, float y);

private:
	float _startY = 0.0f;
	float _speed = 8.0;
	int _index = 0;
	Mix_Chunk* _fxExplosion;
	Pool* _explosionsPool;
};
