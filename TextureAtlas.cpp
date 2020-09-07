#include <iostream>
#include <fstream> 

#include "TextureAtlas.h"
#include "json\json.h"
#include "SDL_rect.h"
#include "SDL_surface.h"
#include "SDL_image.h"
#include "Global.h"

TextureAtlas::TextureAtlas(const char* jsonFileName, const char* imageFileName, const SDL_Renderer* sdlRenderer) {
	renderer = sdlRenderer;
	std::ifstream fileStream = std::ifstream(jsonFileName, std::ifstream::binary);
	Json::Value root;
	fileStream >> root;
	const Json::Value frames = root["frames"];

	for (unsigned int index = 0; index < frames.size(); ++index)
	{
		std::string key = frames[index]["filename"].asString();

		SDL_Rect rect = SDL_Rect();
		rect.x = frames[index]["frame"]["x"].asInt();
		rect.y = frames[index]["frame"]["y"].asInt();
		rect.w = frames[index]["frame"]["w"].asInt();
		rect.h = frames[index]["frame"]["h"].asInt();

		subtextures.insert(std::make_pair(key, rect));
	}

	loadTexture(imageFileName);
}

TextureAtlas::~TextureAtlas() {
	if (texture != nullptr)
		delete(texture);

	subtextures.clear();
}

SDL_Rect TextureAtlas::getRect(const char* key) const {
	return subtextures.at(key);
}

const SDL_Texture* TextureAtlas::getTexture() const {
	return texture;
}

void TextureAtlas::loadTexture(const char* fileName)
{
	SDL_Surface* surface = IMG_Load(fileName);
	if (surface == nullptr)
	{
		std::cerr << "IMG_Load Failed: " << IMG_GetError() << std::endl;
		return;
	}

	texture = SDL_CreateTextureFromSurface((SDL_Renderer*)renderer, surface);
	if (texture == nullptr)
	{
		std::cerr << "SDL_CreateTextureFromSurface Failed: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_FreeSurface(surface);
}
