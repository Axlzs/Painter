#include "mouse.hpp"



void DrawBrush(SDL_Renderer *renderer, int x, int y, int size, SDL_Color color, MouseType type) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (type == MouseType::RECT) {
        SDL_FRect rect = { (float)(x - size/2), (float)(y - size/2), (float)size, (float)size };
        SDL_RenderFillRect(renderer, &rect);
    } else if (type == MouseType::CIRCLE) {
        // naive filled circle (brute force)
        for (int dy = -size/2; dy <= size/2; dy++) {
            for (int dx = -size/2; dx <= size/2; dx++) {
                if (dx*dx + dy*dy <= (size/2)*(size/2)) {
                    SDL_RenderPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }
}
