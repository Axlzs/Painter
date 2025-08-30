#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <iostream>
#include "Static_variables.hpp"
#include "mouse.hpp"
#include "canvas.hpp"
#include "ui.hpp"
#include <bits/stdc++.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Texture *outline;
    SDL_Texture *uiElements;
    SDL_Event event;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("Painter", WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOWWIDTH, WINDOWHEIGHT);
    outline = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOWWIDTH, WINDOWHEIGHT);
    

    ///////////////button definitions//////////////
    
    // Loading sprite sheet
    SDL_Surface* surface = IMG_Load(Button_location.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << SDL_GetError() << "\n";
        return 1;
    }
    SDL_Texture* buttonSheetTex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Creating button instances
    Button resizeButton("resize", 0, 0, buttonSheetTex);
    Button paint_brushButton("paint_brush", 128, 0, buttonSheetTex);
    Button bucketButton("bucket", 256, 0, buttonSheetTex);
    Button pencilButton("pencil", 384, 0, buttonSheetTex);
    Button spray_paintButton("spray_paint", 0, 128, buttonSheetTex);
    Button eraseButton("erase", 0, 256, buttonSheetTex);

    ///////////////////////////////////////////////

    /////////////////fonts and text////////////////

    ///////////////////////////////////////////////

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && 
                event.button.button == SDL_BUTTON_LEFT && !show_menu) {
                drawing = true;
                int x = event.motion.x;
                int y = event.motion.y;
                SDL_SetRenderTarget(renderer, texture);

                DrawBrush(renderer, x, y, CURRENTSIZE, CURRENTCOLOR, BRUSHTYPE);
                prev_x = event.button.x;
                prev_y = event.button.y;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && 
                event.button.button == SDL_BUTTON_LEFT) {
                drawing = false;
                int x = event.motion.x;
                int y = event.motion.y;
                MakeOutline(renderer, outline, x, y, CURRENTSIZE, BRUSHTYPE);
            }

            if (event.type == SDL_EVENT_MOUSE_MOTION && drawing) {
                int x = event.motion.x;
                int y = event.motion.y;

                BresenhalmActivate(renderer, texture, prev_x, prev_y, x, y, CURRENTSIZE, CURRENTCOLOR, BRUSHTYPE);
                MakeOutline(renderer, outline, x, y, CURRENTSIZE, BRUSHTYPE);
                prev_x = x;
                prev_y = y;
            } 
            if (event.type == SDL_EVENT_MOUSE_MOTION && !drawing && !show_menu){
                int x = event.motion.x;
                int y = event.motion.y;
                MakeOutline(renderer, outline, x, y, CURRENTSIZE, BRUSHTYPE);
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT && show_menu) {
                int x = event.motion.x;
                int y = event.motion.y;

                if(resizeButton.mouseOverButton(x,y)) {
                    std::cout<<"resizeButton is pressed :)"<<std::endl;
                }
                if(paint_brushButton.mouseOverButton(x,y)) {
                    std::cout<<"paint_brushButton is pressed :)"<<std::endl;
                }
                if(bucketButton.mouseOverButton(x,y)) {
                    std::cout<<"bucketButton is pressed :)"<<std::endl;
                }
                if(pencilButton.mouseOverButton(x,y)) {
                    std::cout<<"pencilButton is pressed :)"<<std::endl;
                }
                if(spray_paintButton.mouseOverButton(x,y)) {
                    std::cout<<"spray_paintButton is pressed :)"<<std::endl;
                }
                if(eraseButton.mouseOverButton(x,y)) {
                    std::cout<<"eraseButton is pressed :)"<<std::endl;
                }

                }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_TAB) {    // toggle menu
                    show_menu = !show_menu;
                }
                if (event.key.key == SDLK_UP) {     // increase brush size
                    CURRENTSIZE++;

                }
                if (event.key.key == SDLK_DOWN) {   // decrease brush size
                    if(BRUSHSIZE>0){
                        CURRENTSIZE--;
                    }
                }
                if (event.key.key == SDLK_C) {      // set brush to circle
                    BRUSHTYPE = MouseType::CIRCLE;
                    CURRENTCOLOR = BRUSHCOLOR;
                    CURRENTSIZE = BRUSHSIZE;
                }
                if (event.key.key == SDLK_R) {      // set brush to rect
                    BRUSHTYPE = MouseType::RECT;
                    CURRENTCOLOR = BRUSHCOLOR;
                    CURRENTSIZE = BRUSHSIZE;
                }
                if (event.key.key == SDLK_DELETE) { // delete everything
                    clearCanvas(renderer, texture);
                }
                if (event.key.key == SDLK_E) { // delete everything
                    BRUSHSIZE = CURRENTSIZE;
                    CURRENTSIZE = BRUSHSIZE*2;
                    CURRENTCOLOR = GLOBALBACKGROUND;
                }
            }

        }
        

        // Render to window
        SDL_SetRenderTarget(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderTexture(renderer, outline, NULL, NULL);
        
        // Draw menu if active
        if (show_menu) {
            menuScreen(renderer);
            resizeButton.render(renderer);
            paint_brushButton.render(renderer);
            bucketButton.render(renderer);
            pencilButton.render(renderer);
            spray_paintButton.render(renderer);
            eraseButton.render(renderer);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Cap at ~62 FPS
    }
    SDL_DestroyTexture(buttonSheetTex);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(outline);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
