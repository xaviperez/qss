#pragma once

#include <map>
#include <string>

class SDL_Renderer;
class SDL_Rect;
class SDL_Texture;

class TextureAtlas {
public:
	TextureAtlas(const char* jsonFileName, const char* imageFileName, const SDL_Renderer* renderer);
	~TextureAtlas();

	SDL_Rect getRect(const char* key) const;
	const SDL_Texture* getTexture() const;

private:
	std::map<std::string, SDL_Rect> subtextures = {};
	const SDL_Texture* texture = nullptr;
	const SDL_Renderer* renderer = nullptr;

	void loadTexture(const char* fileName);
};
