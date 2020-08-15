#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "TextureAtlas.h"
#include "Position.h"

class GameObject;

class Pool;

class Game {

public:
	Game(std::string title, int width, int height);
	~Game();

	void handleEvents();
	virtual void update();
	void render();

	inline bool isRunning() { return _isRunning; }
	inline SDL_Renderer* getRenderer() { return _renderer; }
	void loadTextureAtlas(std::string fileName);
	inline TextureAtlas* getTextureAtlas() { return _textureAtlas; }
	void addGameObject(GameObject* gameObject);
	void playMusic(std::string fileName);
	GameObject* collision(GameObject* gameObject, std::string collisionLayer);
	Pool* getPool(std::string key);
	Mix_Chunk* getSound(std::string key);

protected:
	std::vector<GameObject*> _gameObjects = {};
	std::map<std::string, Pool*> _pools = {};
	std::map<std::string, Mix_Chunk*> _sounds = {};
	bool _isRunning = false;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	TextureAtlas* _textureAtlas = nullptr;
	Mix_Music* _music = nullptr;
};