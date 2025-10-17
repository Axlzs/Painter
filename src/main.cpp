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

struct camera{
    SDL_FPoint offset = {0,0};
    float zoom = 1;
}camera;

SDL_FRect WINDOW = {
    camera.offset.x,
    camera.offset.y,
    WINDOWWIDTH,
    WINDOWHEIGHT
};

SDL_FRect CANVAS = {
    camera.offset.x,
    camera.offset.y,
    CANVASWWIDTH,
    CANVASHEIGHT
};
void updateZoom(){

    WINDOW.x*=camera.zoom;
    WINDOW.y*=camera.zoom;
    WINDOW.w*=camera.zoom;
    WINDOW.h*=camera.zoom;

    CANVAS.x*=camera.zoom;
    CANVAS.y*=camera.zoom;
    CANVAS.w*=camera.zoom;
    CANVAS.h*=camera.zoom;

}
void moveWindow(float x1, float y1, float x2, float y2){
    dx = x2 - x1;
    dy = y2 - y1;
    CANVAS.x += dx;
    CANVAS.y += dy;
}

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Texture *outline;
    SDL_Texture *uiElements;
    SDL_Surface *colorWheel;
    SDL_Event event;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("Painter", WINDOW.w, WINDOW.h, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CANVASWWIDTH, CANVASHEIGHT);
    outline = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CANVASWWIDTH, CANVASHEIGHT);
    
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);

    ///////////////button definitions//////////////
    
    // Loading sprite sheet
    SDL_Surface* surface = IMG_Load(BUTTON_LOCATION);
    if (!surface) {
        std::cerr << "Failed to load image: " << SDL_GetError() << "\n";
        return 1;
    }
    SDL_Texture* buttonSheetTex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Creating button instances
    Button resizeButton("resize", 0, 0, buttonSheetTex);
    Button paint_brushButton("paint_brush", 74, 0, buttonSheetTex);
    Button bucketButton("bucket", 148, 0, buttonSheetTex);
    Button pencilButton("pencil", 222, 0, buttonSheetTex);
    Button spray_paintButton("spray_paint", 296, 0, buttonSheetTex);
    Button eraseButton("erase", 370, 0, buttonSheetTex);

    ///////////////////////////////////////////////

    /////////////////fonts and text////////////////
    static TTF_Font *font = NULL;
    SDL_Surface *text[TOTALTEXTS];
    SDL_Texture *textTexture[TOTALTEXTS];

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialise SDL_ttf: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* Open the font */
    font = TTF_OpenFont(FONT_LOCATION, FONTSIZE);
    if (!font) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    
    
    /* Assign text to surface*/
    text[0] = TTF_RenderText_Blended(font, "Settings", 0, BLACK);
    text[1] = TTF_RenderText_Blended(font, "Hello World!", 0, BLACK);
    text[2] = TTF_RenderText_Blended(font, "Quit", 0, BLACK);

    SDL_FRect dst[TOTALTEXTS];    

    for(int i=0; i<TOTALTEXTS; i++){
        if(text[i]){
            textTexture[i] = SDL_CreateTextureFromSurface(renderer, text[i]);
            SDL_DestroySurface(text[i]);
        }

        if (!textTexture[i]) {
            SDL_Log("Couldn't create text: %s\n", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        SDL_GetRenderOutputSize(renderer, &w[i], &h[i]);
        SDL_SetRenderScale(renderer, SCALE, SCALE);
        // Getting width and height for text
        SDL_GetTextureSize(textTexture[i], &dst[i].w, &dst[i].h);
        dst[i].x = 30;
        dst[i].y = ((h[i] / SCALE) - dst[i].h) / 2 + dst[i].h*2*i;

    }

    ///////////////////////////////////////////////

    Mouse Mouse; // creating an instance of mouse class
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if(SDL_EVENT_WINDOW_RESIZED){
                int newW, newH;
                SDL_GetWindowSize(window, &newW, &newH);
                WINDOW.w = newW; 
                WINDOW.h = newH;
            }
            
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                int x = event.motion.x;
                int y = event.motion.y;

                if (event.button.button == SDL_BUTTON_LEFT && !show_menu){
                    drawing = true;
                    SDL_SetRenderTarget(renderer, texture);
                    createStroke(x, y, Mouse.currentColor, Mouse.currentSize, Mouse.brushType, Mouse.strokesToRedo);
                }

                if (event.button.button == SDL_BUTTON_MIDDLE && !show_menu){
                    moving = true;
                    prev_x = x;
                    prev_y = y;
                }

                if (event.button.button == SDL_BUTTON_LEFT && show_menu){
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

                    for(int i = 0; i < TOTALTEXTS; i++){
                        if(checkClick(x,y,dst[i])){
                            if(i==0){std::cout<<"settings accessed"<<std::endl;}
                            if(i==1){std::cout<<"hello world accessed"<<std::endl;}
                            if(i==2){running = false;}
                        }
                    }
                }

            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && 
                event.button.button == SDL_BUTTON_LEFT) {
                drawing = false;
                int x = event.motion.x;
                int y = event.motion.y;
                MakeOutline(renderer, outline, x, y, Mouse.currentSize, Mouse.brushType);
            }

            if (event.type == SDL_EVENT_MOUSE_MOTION){
                int x = event.motion.x;
                int y = event.motion.y;

                if (drawing) {
                    addStroke(x, y);
                    MakeOutline(renderer, outline, x, y, Mouse.currentSize, Mouse.brushType); 
                }

                if (!drawing && !show_menu){
                    MakeOutline(renderer, outline, x, y, Mouse.currentSize, Mouse.brushType);
                }
            }

    if(event.type == SDL_EVENT_MOUSE_WHEEL){
        if(event.wheel.y > 0) { // scroll up
            camera.zoom+=ZOOMINTERVAL;
        }
        else if(event.wheel.y < 0) { // scroll down
            if(camera.zoom>ZOOMINTERVAL+0.01){
                camera.zoom-=ZOOMINTERVAL;
            }
        }
        UPDATEZOOM = true;
    }


            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_TAB) {    // toggle menu
                    show_menu = !show_menu;
                }
                if (event.key.key == SDLK_UP && !drawing) {     // increase brush size
                    Mouse.changeBrushSize(1);
                }
                if (event.key.key == SDLK_DOWN && !drawing) {   // decrease brush size
                    Mouse.changeBrushSize(-1);
                }
                if (event.key.key == SDLK_C && !drawing) {      // set brush to circle
                    Mouse.enableEraser(false);
                    Mouse.changeBrushType(MouseType::CIRCLE);
                }
                if (event.key.key == SDLK_R && !drawing) {      // set brush to rect
                    Mouse.enableEraser(false);
                    Mouse.changeBrushType(MouseType::RECT);
                }
                if (event.key.key == SDLK_E) { // eraser
                    Mouse.enableEraser(true);
                }
                if ((event.key.key == SDLK_Z) && (event.key.mod == SDL_KMOD_LCTRL)){
                    SDL_SetRenderTarget(renderer, texture);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
                    undoStroke(Mouse.strokesToRedo);
                    reDrawStrokes(renderer,texture);
                    SDL_SetRenderTarget(renderer, NULL);
                }
                if ((event.key.key == SDLK_Y) && (event.key.mod == SDL_KMOD_LCTRL)){
                    SDL_SetRenderTarget(renderer, texture);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
                    redoStroke(Mouse.strokesToRedo);
                    reDrawStrokes(renderer,texture);
                    SDL_SetRenderTarget(renderer, NULL);
                }
            }

        }
        
        if (UPDATEZOOM){
            UPDATEZOOM = false;
            updateZoom();
        }

        // Render to window
        SDL_SetRenderTarget(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 119, 76, 111, 255); // White background
        SDL_RenderClear(renderer);
        drawStroke(renderer,texture); // continuously renders only the last stroke

        SDL_RenderTexture(renderer, texture, NULL, &CANVAS);
        SDL_RenderTexture(renderer, outline, NULL, &CANVAS);
        
        // Draw menu if active
        if (show_menu) {
            menuScreen(renderer, WINDOW);
            resizeButton.render(renderer);
            paint_brushButton.render(renderer);
            bucketButton.render(renderer);
            pencilButton.render(renderer);
            spray_paintButton.render(renderer);
            eraseButton.render(renderer);
            for(int i = 0; i<=TOTALTEXTS; i++){
                SDL_RenderTexture(renderer, textTexture[i], NULL, &dst[i]);
            }
        }


        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Cap at ~62 FPS
    }
    SDL_DestroyTexture(buttonSheetTex);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(outline);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
