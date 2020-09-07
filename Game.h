#pragma once

#include <vector>
#include <map>

#include "CollisionLayer.h"
#include "Pools.h"
#include "Sounds.h"

class SDL_Renderer;
class TextureAtlas;
class GameObject;
class Pool;
class SDL_Window;
class Mix_Chunk;
class _Mix_Music;

class Game {

public:
	Game(const char* title, int width, int height);
	~Game();

	void handleEvents();
	virtual void update();
	void render();

	inline bool isRunning() { return _isRunning; }
	inline SDL_Renderer* getRenderer() { return _renderer; }
	void loadTextureAtlas(const char* jsonFileName, const char* imageFileName);
	inline TextureAtlas* getTextureAtlas() { return _textureAtlas; }
	void addGameObject(GameObject* gameObject);
	void playMusic(const char* fileName);
	GameObject* collision(GameObject* gameObject, CollisionLayer collisionLayer);
	Pool* getPool(Pools key);
	Mix_Chunk* getSound(Sounds key);

protected:
	std::vector<GameObject*> _gameObjects = {};
	std::map<Pools, Pool*> _pools = {};
	std::map<Sounds, Mix_Chunk*> _sounds = {};
	bool _isRunning = false;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	TextureAtlas* _textureAtlas = nullptr;
	_Mix_Music* _music = nullptr;

	void deleteGameObjects();
	void deletePools();
	void deleteSounds();
	void deleteMusic();
};