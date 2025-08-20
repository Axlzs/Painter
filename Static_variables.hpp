#ifndef STATIC_VARIABLES_HPP
#define STATIC_VARIABLES_HPP

int prev_x = -1, prev_y = -1;
bool drawing = false;
bool running = true;
bool show_menu = false;  // menu toggle state
// Drawing part
bool circle = true;
bool square = false;

int windowW;
int windowH;

int brushSize = 10;
SDL_Color red = {255, 0, 0, 255};


#endif