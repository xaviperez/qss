// ----------------------------------------------------------------
// LICENSE
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non - commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain.We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors.We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
// ----------------------------------------------------------------

/*
#include <iostream>

#include "SDL\include\SDL.h"
#include "SDL_image\include\SDL_image.h"
#include "SDL_mixer\include\SDL_mixer.h"
*/

/* ----------------------------------------------------------------
IMG_Init(IMG_INIT_PNG); // we only need png
IMG_Quit();
SDL_CreateTextureFromSurface(renderer, IMG_Load("ship.png")); // returns a pointer to the texture we can later draw
SDL_DestroyTexture(tex);
SDL_QueryTexture(tex, nullptr, nullptr, &w, &h); // query width and height of a loaded texture
SDL_RenderCopy(renderer, tex, &section, &destination); // section of the texture and destination on the screen
SDL_RenderPresent(renderer); // swap buffers, stall if using vsync

Mix_Init(MIX_INIT_OGG); // we only need ogg   
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // standard values   
Mix_PlayMusic(music, -1); // play music
fx = Mix_LoadWAV("laser.wav"); // load short audio fx
Mix_PlayChannel(-1, fx, 0); // play audio fx
SDL_GetTicks(); // for timers, returns ms since app start

Mix_FreeMusic(music);
Mix_FreeChunk(fx_shoot);
Mix_CloseAudio();
Mix_Quit();

SDL_PollEvent(&event); // query all input events, google possible contents of "event"
SDL_HasIntersection(&react_a, &react_b); // checks for quad overlap
*/

// ----------------------------------------------------------------

#include "QSS.h"

int main(int argc, char* args[])
{
	QSS game = QSS();

	while (game.isRunning()) {
		game.handleEvents();
		game.update();
		game.render();
	}

	return 0;
}
