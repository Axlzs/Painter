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
    {"paint_brush",  {0,    256,    128,    2}},
    {"bucket",       {0,    512,    128,    2}},
    {"pencil",       {128,  0,      128,    2}},
    {"spray_paint",  {256,  128,    128,    2}},
    {"erase",        {128,   512,   128,    2}}
};

class Button{
    public:
    SDL_Texture* uiTexture = nullptr; // screen layer
    std::string buttonType;
    SDL_FRect dstRect;      // part of the sprite sheet where a single buttons is
    SDL_FRect srcRect;      // button sprite sheet
    bool inside = false;
    Buttons& buttonInfo;

/*
1. get button type
2. retrieve button location in sprite sheet
3. assign that location to button rect
4. render
*/
    
    Button(std::string type, int x, int y, SDL_Texture* spritesheet)
        : buttonType(type), buttonInfo(buttonData.at(type)), uiTexture(spritesheet)
    {
        // Source rectangle (cut from spritesheet)
        srcRect.x = buttonInfo.x;
        srcRect.y = buttonInfo.y;
        srcRect.w = buttonInfo.size;
        srcRect.h = buttonInfo.size;

        // Destination rectangle (where to draw on screen)
        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = buttonInfo.size;
        dstRect.h = buttonInfo.size;
    }

    SDL_FRect getFRect() const {
        SDL_FRect fr;
        fr.x = static_cast<float>(button.x);
        fr.y = static_cast<float>(button.y);
        fr.w = static_cast<float>(button.w);
        fr.h = static_cast<float>(button.h);
        return fr;
    }

    bool mouseOverButton(int mouseX, int mouseY) {
        return (mouseX >= dstRect.x &&
                mouseX <  dstRect.x + dstRect.w &&
                mouseY >= dstRect.y &&
                mouseY <  dstRect.y + dstRect.h);
    }

    void render(SDL_Renderer* renderer) const {
        if (uiTexture) {
            SDL_RenderTexture(renderer, uiTexture, &srcRect, &dstRect);
        } else {
            // fallback: draw colored rect
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderFillRect(renderer, &dstRect);
        }
    }

};

inline const std::string Button_location = "icons/buttons.png";

