#pragma once

#include "GameObject.h"
#include "SDL_rect.h""

class Game;

class Score : public GameObject {

public:
	Score(float x, float y, float z, const char* fileName);
	~Score();

	void init(Game* game) override;
	void render() override;
	void renderNumber(int number, int x, int y);

	static void reset();
	static void add(int score);
	static int getCurrent();
	static int getMaximum();

private:

	static int _current;
	static int _maximum;

	int _textureX = 0;
	int _textureY = 0;
	SDL_Rect _maxRect = SDL_Rect();
	SDL_Rect _destMaxRect = SDL_Rect();
};