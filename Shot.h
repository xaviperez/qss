#pragma once

#include "GameObject.h"

class Shot : public GameObject {

public:

	Shot(float x, float y, float z, std::string fileName);
	~Shot();

	void update() override;

private:
	float _speed = 12.0;
};
