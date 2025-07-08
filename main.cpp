#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <unistd.h>

class Button{
    public:
    SDL_Rect button;
    bool inside = false;
    
    Button(int x,int y,int width,int height){
        button.x = x;
        button.y = y;
        button.w = width;
        button.h = height;
    }

    SDL_FRect getFRect() const {
        SDL_FRect fr;
        fr.x = static_cast<float>(button.x);
        fr.y = static_cast<float>(button.y);
        fr.w = static_cast<float>(button.w);
        fr.h = static_cast<float>(button.h);
        return fr;
    }

    bool mouseOverButton(int mouseX, int mouseY){
        return (mouseX>=button.x &&
            mouseX<button.w &&
            mouseY>=button.y &&
            mouseY<button.h);
    }

    void render(SDL_Renderer* renderer) const {
        SDL_FRect dstRect = getFRect();
        if (iconTexture) {
            SDL_RenderTexture(renderer, iconTexture, NULL, &dstRect);
        } else {
            // Draw a colored rectangle as fallback
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderFillRect(renderer, &button);
        }
    }

};

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;

    SDL_Surface *iconSurface;
    SDL_Surface *iconSurface1;
    SDL_Texture *iconTexture;
    SDL_Texture *iconTexture1;

    int prev_x = -1, prev_y = -1;
    bool drawing = false;
    bool running = true;
    Button eraseButton(0,0,50,50);
    Button drawButton(50,0,50,50);
    SDL_FRect dstRect = eraseButton.getFRect();
    SDL_FRect dstRect1 = drawButton.getFRect();

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("Drawing App", 1024, 768, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                               SDL_TEXTUREACCESS_TARGET, 1024, 768);
    ////////////////////////////////////////////////////////////////

    iconSurface = SDL_LoadBMP("icons/erase_icon.bmp");
    if(!iconSurface) {
        std::cout<<"no surface"<<SDL_GetError()<<std::endl;
        return 1;
    }
    iconSurface1 = SDL_LoadBMP("icons/draw_icon.bmp");
    if(!iconSurface1) {
        std::cout<<"no surface"<<SDL_GetError()<<std::endl;
        return 1;
    }

    iconTexture = SDL_CreateTextureFromSurface(renderer, iconSurface);
    if (!iconTexture) {
        std::cout<<"no texture: "<<SDL_GetError()<<std::endl;
        return 2;
    }
    iconTexture1 = SDL_CreateTextureFromSurface(renderer, iconSurface1);
    if (!iconTexture1) {
        std::cout<<"no texture: "<<SDL_GetError()<<std::endl;
        return 2;
    }

    ////////////////////////////////////////////////////////////////

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && 
                event.button.button == SDL_BUTTON_LEFT) {
                drawing = true;
                prev_x = event.button.x;
                prev_y = event.button.y;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && 
                event.button.button == SDL_BUTTON_LEFT) {
                drawing = false;
            }

            if (event.type == SDL_EVENT_MOUSE_MOTION && drawing) {
                int x = event.motion.x;
                int y = event.motion.y;
                SDL_SetRenderTarget(renderer, texture);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                if (prev_x >= 0 && prev_y >= 0) {
                    SDL_RenderLine(renderer, prev_x, prev_y, x, y);
                }
                prev_x = x;
                prev_y = y;
            }
        }

        // Render to window
        SDL_SetRenderTarget(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        //buttons
        SDL_RenderTexture(renderer,iconTexture, NULL, &dstRect);
        SDL_RenderTexture(renderer,iconTexture1, NULL, &dstRect1);
        //buttons
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Cap at ~60 FPS
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
