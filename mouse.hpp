#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <SDL3/SDL.h>

enum class MouseType{
    RECT,
    CIRCLE
};

void DrawBrush(SDL_Renderer *renderer, int x, int y, int size, SDL_Color color, MouseType type);

#endif