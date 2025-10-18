#ifndef UI_HPP
#define UI_HPP
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>


struct Buttons {
    int x;
    int y;
    int size;
    int states;
};

inline const std::unordered_map<std::string, Buttons> buttonData = {
//  INDEX             X,    Y,      SIZE,   STATES
    {"resize",       {0,    0,      64,    2}},
    {"paint_brush",  {128,  0,      64,    2}},
    {"bucket",       {256,  0,      64,    2}},
    {"pencil",       {0,    64,     64,    2}},
    {"spray_paint",  {128,  64,     64,    2}},
    {"erase",        {256,  64,     64,    2}}
};

class Camera{
public:
    SDL_FPoint offset = {0,0};
    float zoom = 1;
    float zoomin = 1.1;
    float zoomout = 0.9;
    float totalZoom = 1;


    void updateZoom(SDL_FRect& canvas);
};


class Button {
private:
    SDL_Texture* uiTexture;
    SDL_FRect dstRect;
    SDL_FRect srcRect;
    const Buttons& buttonInfo;
public:

    Button(const std::string& type, int x, int y, SDL_Texture* spritesheet);
    bool mouseOverButton(int mouseX, int mouseY);
    void render(SDL_Renderer* renderer) const;
};

bool checkClick(int mouseX, int mouseY, SDL_FRect rect);

#endif