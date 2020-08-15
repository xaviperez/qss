#pragma once

#include <iostream>
#include <fstream>

#include "SDL.h"
#include "SDL_image.h"
#include "json\json.h"

class TextureAtlas {
public:
	TextureAtlas(std::string fileName, SDL_Renderer* renderer);
	~TextureAtlas();

	SDL_Rect* getRect(std::string key) const;
	SDL_Texture* getTexture() const;

private:
	std::map<std::string, SDL_Rect*> _subtextures;
	SDL_Texture* _texture;

	void loadTexture(std::string fileName, SDL_Renderer* renderer);
};
