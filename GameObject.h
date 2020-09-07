#pragma once

#include "CollisionLayer.h"
#include "SDL_rect.h"

class Game;
class TextureAtlas;
class SDL_Renderer;
class SDL_Texture;

class GameObject {
public:
	GameObject(float x, float y, float z, const char* fileName, float zoomFactor = 1.0, bool isEnabled = true);
	~GameObject();

	virtual void init(Game* game);
	virtual void update();
	virtual void render();

	float getZindex();
	void setPosition(float x, float y);
	void setEnabled(bool isEnabled);
	inline bool isEnabled() { return _isEnabled;  }
	SDL_Rect getCollisionArea();
	inline CollisionLayer getCollisionLayer() { return _collisionLayer; }

protected:

	bool _isEnabled = false;
	bool _isVisible = false;
	float _x = 0.0F;
	float _y = 0.0F;
	float _z = 0.0F;
	float _zoomFactor = 1.0F;
	const char* _fileName = nullptr;
	CollisionLayer _collisionLayer = CollisionLayer::None;
	TextureAtlas* _textureAtlas = nullptr;
	SDL_Renderer* _renderer = nullptr;
	SDL_Texture* _texture = nullptr;
	SDL_Rect _sourceRect = SDL_Rect();
	SDL_Rect _destinationRect = SDL_Rect();
	Game* _game = nullptr;
	void updateDestinationRect();
};