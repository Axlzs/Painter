#ifndef STATIC_VARIABLES_HPP
#define STATIC_VARIABLES_HPP

int WINDOWWIDTH = 1024;
int WINDOWHEIGHT = 768;
const float SCALE = 1.0f;

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

/////////////////////BUTTONS/////////////////////
inline const char* BUTTON_LOCATION = "icons/buttons.png";

//////////////////////FONTS//////////////////////
int TOTALTEXTS = 3;
float FONTSIZE = 20.0f;
inline const char* FONT_LOCATION = "fonts/Roboto/Roboto-VariableFont_wdth,wght.ttf";
int w[3] = {0,0,0};
int h[3] = {0,0,0};
#endif