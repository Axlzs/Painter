#include <cmath>
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
void BresenhalmActivate(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int size, SDL_Color color, MouseType type) {
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
        DrawBrush(renderer, x, y, size, color, type);
    }

    // ensure last point is drawn
    DrawBrush(renderer, x2, y2, size, color, type);
}
