#include <SDL3/SDL.h>
#include <iostream>
#include "Static_variables.hpp"
#include "mouse.hpp"
#include "canvas.hpp"
#include <bits/stdc++.h>

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("Drawing App", WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOWWIDTH, WINDOWHEIGHT);
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && 
                event.button.button == SDL_BUTTON_LEFT && show_menu == false) {
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

                BresenhalmActivate(renderer, prev_x, prev_y, x, y, BRUSHSIZE, RED, brushType);
                prev_x = x;
                prev_y = y;
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_TAB) {    // toggle menu
                    show_menu = !show_menu;
                }
                if (event.key.key == SDLK_UP) {     // increase brush size
                    BRUSHSIZE++;
                }
                if (event.key.key == SDLK_DOWN) {   // decrease brush size
                    if(BRUSHSIZE>0){
                        BRUSHSIZE--;
                    }
                }
                if (event.key.key == SDLK_C) {      // set brush to circle
                    brushType = MouseType::CIRCLE;
                }
                if (event.key.key == SDLK_R) {      // set brush to rect
                    brushType = MouseType::RECT;
                }
                if (event.key.key == SDLK_DELETE) { // delete everything
                    clearCanvas(renderer, texture);
                }
            }

        }
        

        // Render to window
        SDL_SetRenderTarget(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);

        // Draw menu if active
        if (show_menu) {
            menuScreen(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Cap at ~62 FPS
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
