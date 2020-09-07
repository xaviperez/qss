#include "ParallaxLayer.h"
#include "SDL.h"

ParallaxLayer::ParallaxLayer(float y, float z, const char* fileName, int speed, int screenWidth) : GameObject::GameObject(0, y, z, fileName) {
	_speed = speed;
	_screenWidth = screenWidth;
}

ParallaxLayer::~ParallaxLayer() {}

void ParallaxLayer::update() {

	if (_speed > 0) {
		Uint32 ticks = SDL_GetTicks();
		float posX = ticks * _speed / 1000.0F;
		
		_x = - posX;
		GameObject::update();
	}
}

void ParallaxLayer::render() {
	int offsetX = static_cast<int>(_x) % _screenWidth;

	_destinationRect.x = offsetX;
	_destinationRect.y = static_cast<int>(_y);
	SDL_RenderCopy(_renderer, _texture, &_sourceRect, &_destinationRect);
	
	offsetX += _screenWidth;

	_destinationRect.x = offsetX;
	_destinationRect.y = static_cast<int>(_y);
	SDL_RenderCopy(_renderer, _texture, &_sourceRect, &_destinationRect);
}