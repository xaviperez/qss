#pragma once

#include "Game.h"

class QSS : public Game {

public:

	QSS();
	~QSS();

	void update() override;

private:
	int frame = 0;
	void initParallax();
	void initPools();
	void initSounds();
	void initScore();
	void spawnEnemies();
	void initPlayer();
};