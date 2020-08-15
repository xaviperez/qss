#include <string>

#include "GameObject.h"

GameObject::GameObject(float x, float y, float z, std::string fileName, float zoomFactor, bool isEnabled) {
	setPosition(x, y);
	_z = z;
	_fileName = fileName;
	_zoomFactor = zoomFactor;
	setEnabled(isEnabled);
}

GameObject::~GameObject() {}

void GameObject::init(Game* game) {
	_game = game;
	_textureAtlas = _game->getTextureAtlas();
	_renderer = _game->getRenderer();
	_texture = _textureAtlas->getTexture();
	_sourceRect = _textureAtlas->getRect(_fileName);

	updateDestinationRect();
}

void GameObject::update() {
	if (!_isEnabled) {
		return;
	}

	_destinationRect.x = static_cast<int>(_x);
	_destinationRect.y = static_cast<int>(_y);
}

void GameObject::render() {
	if (!_isEnabled || !_isVisible) {
		return;
	}

	SDL_RenderCopy(_renderer, _texture, _sourceRect, &_destinationRect);
}

float GameObject::getZindex() {
	return _z;
}

void GameObject::setPosition(float x, float y) {
	_x = x;
	_y = y;

	_destinationRect.x = static_cast<int>(_x);
	_destinationRect.y = static_cast<int>(_y);
}

void GameObject::setEnabled(bool isEnabled) {
	_isEnabled = isEnabled;
	_isVisible = isEnabled;
}

SDL_Rect* GameObject::getCollisionArea() {
	return &_destinationRect;
}

void GameObject::updateDestinationRect() {
	_destinationRect.x = static_cast<int>(_x);
	_destinationRect.y = static_cast<int>(_y);
	_destinationRect.w = static_cast<int>(_sourceRect->w * _zoomFactor);
	_destinationRect.h = static_cast<int>(_sourceRect->h * _zoomFactor);
}