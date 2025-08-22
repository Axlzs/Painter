#include "canvas.hpp"
int extern WINDOWWIDTH;
int extern WINDOWHEIGHT;
SDL_Color extern GLOBALBACKGROUND;

void clearCanvas(SDL_Renderer *renderer, SDL_Texture *texture){
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, GLOBALBACKGROUND.r, GLOBALBACKGROUND.g, GLOBALBACKGROUND.b, GLOBALBACKGROUND.a);
    SDL_RenderClear(renderer); // deletes just the texture
    SDL_SetRenderTarget(renderer, NULL);
}

void menuScreen(SDL_Renderer *renderer){
    SDL_FRect menuRect = {0, 0, (float)WINDOWWIDTH, (float)WINDOWHEIGHT};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);  // semi-transparent black
    SDL_RenderFillRect(renderer, &menuRect);
}