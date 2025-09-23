#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <SDL3/SDL.h>

enum class MouseType {
    RECT,
    CIRCLE
};

extern MouseType BRUSHTYPE;

void createStroke(int x, int y);
void addStroke(int x, int y);
void DrawBrush(SDL_Renderer *renderer, int x, int y, MouseType type, SDL_Color color, int brushsize);
void BresenhalmActivate(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, MouseType type, SDL_Color color, int brushsize);
void drawStroke(SDL_Renderer* renderer, SDL_Texture* texture);
void MakeOutline(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
void changeBrushSize(int x);
void changeBrushType(MouseType type);
void changeEraser();

#endif
