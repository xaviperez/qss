#include "Game.h"
#include "GameObject.h"
#include "Input.h"

Game::Game(std::string title, int width, int height) {
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
	
	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	Mix_CloseAudio();
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
	for (auto& gameObject : _gameObjects) {
		gameObject->update();
	}
}

void Game::render() {
	SDL_RenderClear(_renderer);
	for (auto& gameObject : _gameObjects) {
		gameObject->render();
	}
	SDL_RenderPresent(_renderer);
}

void Game::loadTextureAtlas(std::string fileName) {
	_textureAtlas = new TextureAtlas(fileName, _renderer);
}

void Game::addGameObject(GameObject* gameObject) {
	gameObject->init(this);
	
	int pos = 0;
	for (auto& current : _gameObjects) {
		if (current->getZindex() > gameObject->getZindex()) {
			break;
		}
		pos++;
	}

	_gameObjects.insert(_gameObjects.begin() + pos, gameObject);
}

void Game::playMusic(std::string fileName) {
	_music = Mix_LoadMUS(fileName.c_str());
	Mix_PlayMusic(_music, -1);
}

GameObject* Game::collision(GameObject* gameObject, std::string collisionLayer) {

	if (gameObject == nullptr || !gameObject->isEnabled())
		return nullptr;;

	for (auto& candidate : _gameObjects) {
		if (candidate == nullptr || !candidate->isEnabled())
			continue;

		bool isDifferentGameObject = gameObject != candidate;
		bool isCollisionLayer = candidate->getCollisionLayer() == collisionLayer;
		bool hasCollision = SDL_HasIntersection(gameObject->getCollisionArea(), candidate->getCollisionArea()) == SDL_TRUE;

		if (isDifferentGameObject && isCollisionLayer && hasCollision) {
			return candidate;
		}
	}

	return nullptr;
}

Pool* Game::getPool(std::string key) {
	return _pools[key];
}

Mix_Chunk* Game::getSound(std::string key) {
	return _sounds[key];
}