#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <SDL3/SDL.h>

enum class MouseType {
    RECT,
    CIRCLE
};

extern MouseType BRUSHTYPE;

void DrawBrush(SDL_Renderer *renderer, int x, int y, int size, SDL_Color color, MouseType type);
void BresenhalmActivate(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int size, SDL_Color color, MouseType type);


#endif
