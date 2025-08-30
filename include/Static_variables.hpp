#ifndef STATIC_VARIABLES_HPP
#define STATIC_VARIABLES_HPP

int WINDOWWIDTH = 1024;
int WINDOWHEIGHT = 768;

int prev_x = -1, prev_y = -1;
bool drawing = false;
bool running = true;
bool show_menu = false;  // menu toggle state

int BRUSHSIZE = 10;
int CURRENTSIZE = 10;
SDL_Color BRUSHCOLOR = {255, 0, 0, 255};
SDL_Color CURRENTCOLOR = {255, 0, 0, 255};
SDL_Color RED = {255, 0, 0, 255};
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color GLOBALBACKGROUND = {255, 255, 255, 255};
SDL_Color FONTCOLOR  = {0, 0, 0, 255};

//////////////////////FONTS//////////////////////
float FONTSIZE = 50.0f;

#endif