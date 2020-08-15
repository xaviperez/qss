#pragma once
#include "GameObject.h"

class Score : public GameObject {

public:
	Score(float x, float y, float z, std::string fileName);
	~Score();

	void init(Game* game) override;
	void render() override;
	void renderNumber(int number, int x, int y);

	static void reset();
	static void add(int score);
	static int getCurrent();
	static int getMaximum();

private:
	const int FRAME_WIDTH = 24;
	const int FRAME_HEIGHT = 27;

	static int _current;
	static int _maximum;

	int _textureX = 0;
	int _textureY = 0;
	SDL_Rect* _maxRect;
	SDL_Rect _destMaxRect;
};