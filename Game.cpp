#include <iostream>

#include "Game.h"
#include "GameObject.h"
#include "TextureAtlas.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Input.h"

Game::Game(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init Failed: " << SDL_GetError() << std::endl;
		return;
	}
	
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "IMG_Init Failed: " << IMG_GetError() << std::endl;
		return;
	}

	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG) {
		auto x = Mix_GetError();
		std::cerr << "Mix_Init Failed: " << Mix_GetError() << std::endl;
		return;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (_window == NULL) {
		std::cerr << "SDL_CreateWindow Failed: " << SDL_GetError() << std::endl;
		return;
	}

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == NULL) {
		std::cerr << "SDL_CreateRenderer Failed: " << SDL_GetError() << std::endl;
		return;
	}

	_isRunning = true;
	_pools.clear();
}

Game::~Game() {
	Mix_CloseAudio();

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	deleteGameObjects();
	deletePools();
	deleteSounds();
	deleteMusic();

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
		case SDL_KEYUP:
			Input::keyUp(event.key.keysym);
			break;
		case SDL_KEYDOWN:
			Input::keyDown(event.key.keysym);
			break;
		default:
			break;
	}
}

void Game::update() {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->update();
	}
}

void Game::render() {
	SDL_RenderClear(_renderer);
	for (GameObject* gameObject : _gameObjects) {
		gameObject->render();
	}
	SDL_RenderPresent(_renderer);
}

void Game::loadTextureAtlas(const char* jsonFileName, const char* imageFileName) {
	_textureAtlas = new TextureAtlas(jsonFileName, imageFileName, _renderer);
}

void Game::addGameObject(GameObject* gameObject) {
	gameObject->init(this);
	
	int pos = 0;
	for (GameObject* current : _gameObjects) {
		if (current->getZindex() > gameObject->getZindex()) {
			break;
		}
		pos++;
	}

	_gameObjects.insert(_gameObjects.begin() + pos, gameObject);
}

void Game::playMusic(const char* fileName) {
	_music = Mix_LoadMUS(fileName);
	Mix_PlayMusic(_music, -1);
}

GameObject* Game::collision(GameObject* gameObject, CollisionLayer collisionLayer) {

	if (gameObject == nullptr || !gameObject->isEnabled())
		return nullptr;;

	for (auto& candidate : _gameObjects) {
		if (candidate == nullptr || !candidate->isEnabled())
			continue;

		bool isDifferentGameObject = gameObject != candidate;
		bool isCollisionLayer = candidate->getCollisionLayer() == collisionLayer;
		bool hasCollision = SDL_HasIntersection(&gameObject->getCollisionArea(), &candidate->getCollisionArea()) == SDL_TRUE;

		if (isDifferentGameObject && isCollisionLayer && hasCollision) {
			return candidate;
		}
	}

	return nullptr;
}

Pool* Game::getPool(Pools key) {
	return _pools[key];
}

Mix_Chunk* Game::getSound(Sounds key) {
	return _sounds[key];
}

void Game::deleteGameObjects() {
	for (GameObject* gameObject : _gameObjects) {
		delete(gameObject);
	}
}

void Game::deletePools() {
	for (std::map<Pools, Pool*>::iterator itr = _pools.begin(); itr != _pools.end(); itr++)
	{
		delete(itr->second);
	}
	_pools.clear();
}

void Game::deleteSounds() {
	for (std::map<Sounds, Mix_Chunk*>::iterator itr = _sounds.begin(); itr != _sounds.end(); itr++)
	{
		Mix_FreeChunk(itr->second);
	}
	_sounds.clear();
}

void Game::deleteMusic() {
	if (_music != nullptr)
		Mix_FreeMusic(_music);
}