#pragma once

#include "GameObject.h"

class ParallaxLayer : public GameObject {

public:

	ParallaxLayer(float y, float z, const char* fileName, int speed, int screenWidth);
	~ParallaxLayer();

	void update() override;
	void render() override;

private:

	int _speed;
	int _screenWidth;
};
