#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(std::string fileName, SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}