#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <SDL3/SDL.h>
#include <vector>

enum class MouseType {
    RECT,
    CIRCLE
};

class Mouse {
    public:

        float x1 = -1; // previous x for moving 
        float y1 = -1; // previous y for moving 
        float x2;
        float y2;

        bool drawing = false;
        bool erasing = false;
        bool updateZoom = false;
        bool moving = false;

        int brushsize = 10;
        int currentSize = 10;
        int eraserSize = 20;
        int strokesToRedo = 0;

        SDL_Color brushColor = {255, 0, 0, 255};
        SDL_Color currentColor = {255, 0, 0, 255};
        SDL_Color red = {255, 0, 0, 255};
        MouseType brushType = MouseType::RECT;
    
    void enableEraser(bool value);
    void enableDrawing(bool value);
    void enableZoom(bool value);
    void enableMoving(bool value);

    void changeBrushSize(int amount);
    void changeBrushType(MouseType type);
};

extern MouseType BRUSHTYPE;

void createStroke(int x, int y, SDL_Color currentcolor, int currentsize, MouseType brushtype, int strokestoredo);
void addStroke(int x, int y);
void DrawBrush(SDL_Renderer *renderer, int x, int y, MouseType type, SDL_Color color, int brushsize);
void BresenhalmActivate(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, MouseType type, SDL_Color color, int brushsize);
void drawStroke(SDL_Renderer* renderer, SDL_Texture* texture);
void reDrawStrokes(SDL_Renderer* renderer, SDL_Texture* texture);
void undoStroke(int& strokestoredo);
void redoStroke(int& strokestoredo);
void MakeOutline(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, int currentsize, MouseType brushtype);
void changeBrushSize(int x);
void changeBrushType(MouseType type);
void changeEraser();

#endif