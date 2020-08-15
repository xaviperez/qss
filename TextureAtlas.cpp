#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(std::string fileName, SDL_Renderer* renderer) {
	std::ifstream fileStream = std::ifstream(fileName.c_str(), std::ifstream::binary);
	Json::Value root;
	fileStream >> root;
	const Json::Value subtextures = root["frames"];

	for (unsigned int index = 0; index < subtextures.size(); ++index)
	{
		std::string key = subtextures[index]["filename"].asString();

		SDL_Rect* rect = new SDL_Rect();
		rect->x = subtextures[index]["frame"]["x"].asInt();
		rect->y = subtextures[index]["frame"]["y"].asInt();
		rect->w = subtextures[index]["frame"]["w"].asInt();
		rect->h = subtextures[index]["frame"]["h"].asInt();

		_subtextures[key] = rect;
	}

	std::string pngFileName = fileName.replace(fileName.end() - 4, fileName.end(), "png");
	loadTexture(pngFileName, renderer);
}

TextureAtlas::~TextureAtlas() {
}

SDL_Rect* TextureAtlas::getRect(std::string key) const {
	return _subtextures.at(key);
}

SDL_Texture* TextureAtlas::getTexture() const {
	return _texture;
}

void TextureAtlas::loadTexture(std::string fileName, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
	{
		std::cerr << "IMG_Load Failed: " << IMG_GetError() << std::endl;
		return;
	}

	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (_texture == nullptr)
	{
		std::cerr << "SDL_CreateTextureFromSurface Failed: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_FreeSurface(surface);
}
