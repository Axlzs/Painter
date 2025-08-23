#include <cmath>
#include <iostream>
#include "mouse.hpp"


MouseType BRUSHTYPE = MouseType::RECT;
int extern WINDOWWIDTH;
int extern WINDOWHEIGHT;

void DrawBrush(SDL_Renderer *renderer, int x, int y, int size, SDL_Color color, MouseType type) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (type == MouseType::RECT) {
        SDL_FRect rect = { (float)(x - size/2), (float)(y - size/2), (float)size, (float)size };
        SDL_RenderFillRect(renderer, &rect);
    } else if (type == MouseType::CIRCLE) {
        for (int dy = -size/2; dy <= size/2; dy++) {
            for (int dx = -size/2; dx <= size/2; dx++) {
                if (dx*dx + dy*dy <= (size/2)*(size/2)) {
                    SDL_RenderPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }
}
void BresenhalmActivate(SDL_Renderer* renderer, SDL_Texture* texture, int x1, int y1, int x2, int y2, int size, SDL_Color color, MouseType type) {
    std::cout<<"no outline"<<std::endl;
    
    // Distance between points
    int dx = x2 - x1;
    int dy = y2 - y1;
    float dist = sqrt(dx*dx + dy*dy);

    // step size: smaller = smoother line
    float step = 1.0f; 

    for (float i = 0; i < dist; i += step) {
        float t = i / dist;  // normalized [0,1]
        int x = (int)std::lerp((float)x1, (float)x2, t);
        int y = (int)std::lerp((float)y1, (float)y2, t);
        SDL_SetRenderTarget(renderer, texture);
        DrawBrush(renderer, x, y, size, color, type);
    }

    // ensure last point is drawn
    DrawBrush(renderer, x2, y2, size, color, type);
}

void MakeOutline(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int size, MouseType type){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    SDL_SetRenderTarget(renderer, texture); // selects the layer, the coursor is on
    SDL_SetRenderDrawColor(renderer, 0,0,0,0); // sets the color to invisible
    SDL_RenderClear(renderer); // immediately overlays the invisible color
    SDL_SetRenderDrawColor(renderer, 0,0,0,180);
    if (type == MouseType::RECT) {
        std::cout<<"i identify as an outline"<<std::endl;
        SDL_FRect rect = { (float)(x - size/2), (float)(y - size/2), (float)size, (float)size };
        SDL_RenderRect(renderer, &rect); // draws the textrue
    }
    SDL_SetRenderTarget(renderer, NULL); // deselects this layer 

}