#include "Score.h"

int Score::_current = 0;
int Score::_maximum = 0;

Score::Score(float x, float y, float z, std::string fileName) : GameObject::GameObject(x, y, z, fileName) {}

Score::~Score() {}

void Score::init(Game* game) {
	GameObject::init(game);

	_sourceRect->w = FRAME_WIDTH;
	_sourceRect->h = FRAME_HEIGHT;
	_textureX = _sourceRect->x;
	_textureY = _sourceRect->y;

	updateDestinationRect();

	_maxRect = _textureAtlas->getRect("max.png");
	_destMaxRect.x = static_cast<int>(_x) - 84;
	_destMaxRect.y = static_cast<int>(_y);
	_destMaxRect.w = static_cast<int>(_maxRect->w);
	_destMaxRect.h = static_cast<int>(_maxRect->h);
}

void Score::render() {
	renderNumber(_maximum, _x, _y);
	renderNumber(_current, _x, _y + 32);
	SDL_RenderCopy(_renderer, _texture, _maxRect, &_destMaxRect);
}

void Score::reset() {
	Score::_current = 0;
}

void Score::add(int score) {
	Score::_current += score;

	if (Score::_current > Score::_maximum) {
		Score::_maximum = Score::_current;
	}
}

int Score::getCurrent() {
	return Score::_current;
}

int Score::getMaximum() {
	return Score::_maximum;
}

void Score::renderNumber(int number, int x, int y) {
	for (int i = 0; i < 5; i++) {
		int digit = number % 10;
		number /= 10;

		_sourceRect->x = _textureX + (digit * FRAME_WIDTH);
		_destinationRect.x = x + ((4 - i) * FRAME_WIDTH);
		_destinationRect.y = y;
		SDL_RenderCopy(_renderer, _texture, _sourceRect, &_destinationRect);
	}
}