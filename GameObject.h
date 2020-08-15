#pragma once

#include "Game.h"

class GameObject {
public:
	GameObject(float x, float y, float z, std::string fileName, float zoomFactor = 1.0, bool isEnabled = true);
	~GameObject();

	virtual void init(Game* game);
	virtual void update();
	virtual void render();

	float getZindex();
	void setPosition(float x, float y);
	void setEnabled(bool isEnabled);
	inline bool isEnabled() { return _isEnabled;  }
	SDL_Rect* getCollisionArea();
	inline std::string getCollisionLayer() { return _collisionLayer; }

protected:

	bool _isEnabled;
	bool _isVisible;
	float _x;
	float _y;
	float _z;
	float _zoomFactor;
	std::string _fileName;
	std::string _collisionLayer;
	TextureAtlas* _textureAtlas;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Rect* _sourceRect;
	SDL_Rect _destinationRect;
	Game* _game;
	void updateDestinationRect();
};