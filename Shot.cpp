#include "Shot.h"

Shot::Shot(float x, float y, float z, std::string fileName) : GameObject::GameObject(x, y, z, fileName, 2.0, false) {
	_collisionLayer = "shot";
}

Shot::~Shot() {}

void Shot::update() {
	if (!_isEnabled) {
		return;
	}

	_x += _speed;

	if (_x > 640) {
		setEnabled(false);
	}

	GameObject::update();
}