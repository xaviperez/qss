#include "Explosion.h"

Explosion::Explosion(float x, float y, float z, const char* fileName) : GameObject::GameObject(x, y, z, fileName, 1.0, false) {}

Explosion::~Explosion() {}

void Explosion::init(Game* game) {
	GameObject::init(game);
	
	_sourceRect.w = FRAME_WIDTH;
	_sourceRect.h = FRAME_HEIGHT;
	_textureX = _sourceRect.x;
	_textureY = _sourceRect.y;

	updateDestinationRect();
}

void Explosion::update() {
	if (!_isEnabled) {
		return;
	}

	int frame = ANIMATION[_animationIndex];

	_frame++;

	if (_frame >= FRAME_DURATION) {
		_animationIndex++;
		_frame = 0;
	}

	if (_animationIndex > sizeof(ANIMATION) / sizeof(ANIMATION[0])) {
		_animationIndex = 0;
		setEnabled(false);
	}

	_sourceRect.x = _textureX + (frame * FRAME_WIDTH);
	
	GameObject::update();
}