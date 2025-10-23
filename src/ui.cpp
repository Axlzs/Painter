#include <SDL3_ttf/SDL_ttf.h>
#include "ui.hpp"

void Camera::updateZoom(SDL_FRect& canvas){
    canvas.x*=zoom;
    canvas.y*=zoom;
    canvas.w*=zoom;
    canvas.h*=zoom;

    totalZoom*=zoom;
}

Button::Button(const std::string& type, int x, int y, SDL_Texture* spritesheet)
    : buttonInfo(buttonData.at(type)), uiTexture(spritesheet){
    srcRect = { (float)buttonInfo.x, (float)buttonInfo.y, (float)buttonInfo.size, (float)buttonInfo.size };
    dstRect = { static_cast<float>(x), static_cast<float>(y),
                static_cast<float>(buttonInfo.size), static_cast<float>(buttonInfo.size) };
}

bool Button::mouseOverButton(int mouseX, int mouseY) {
    return (mouseX >= dstRect.x &&
            mouseX <  dstRect.x + dstRect.w &&
            mouseY >= dstRect.y &&
            mouseY <  dstRect.y + dstRect.h);
}

void Button::render(SDL_Renderer* renderer) const {
    if (uiTexture) {
        SDL_RenderTexture(renderer, uiTexture, &srcRect, &dstRect);
    }
}

bool checkClick(int mouseX, int mouseY, SDL_FRect rect){
    return (mouseX >= rect.x &&
            mouseX <  rect.x + rect.w &&
            mouseY >= rect.y &&
            mouseY <  rect.y + rect.h);
}