#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <SDL3/SDL.h>

void clearCanvas(SDL_Renderer *renderer, SDL_Texture *texture);
void menuScreen(SDL_Renderer *renderer, SDL_FRect window);

#endif