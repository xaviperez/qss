#pragma once

#include "GameObject.h"

class Explosion : public GameObject {

	const int FRAME_WIDTH = 64;
	const int FRAME_HEIGHT = 64;
	const int FRAME_DURATION = 6;
	const int ANIMATION[6] = { 5, 4, 3, 2, 1, 0 };

public:

	Explosion(float x, float y, float z, const char* fileName);
	~Explosion();

	void init(Game* game) override;
	void update() override;

private:
	int _animationIndex = 0;
	int _frame = 0;
	int _textureX = 0;
	int _textureY = 0;
};
