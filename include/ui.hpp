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
    {"resize",       {0,    0,      128,    2}},
    {"paint_brush",  {256,  0,      128,    2}},
    {"bucket",       {512,  0,      128,    2}},
    {"pencil",       {0,    128,    128,    2}},
    {"spray_paint",  {256,  128,    128,    2}},
    {"erase",        {512,  128,    128,    2}}
};

inline const std::string Button_location = "icons/buttons.png";

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


#endif