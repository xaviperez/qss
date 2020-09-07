#include "Shot.h"
#include "Global.h"

Shot::Shot(float x, float y, float z, const char* fileName) : GameObject::GameObject(x, y, z, fileName, ZOOM_X2, false) {
	_collisionLayer = CollisionLayer::Shot;
}

Shot::~Shot() {}

void Shot::update() {
	if (!_isEnabled) {
		return;
	}

	_x += _speed;

	if (_x > SCREEN_WIDTH) {
		setEnabled(false);
	}

	GameObject::update();
}