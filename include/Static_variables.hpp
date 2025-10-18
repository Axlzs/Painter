#ifndef STATIC_VARIABLES_HPP
#define STATIC_VARIABLES_HPP

float WINDOWWIDTH = 900;
float WINDOWHEIGHT = 700;

float CANVASWWIDTH = 3000;
float CANVASHEIGHT = 3000;
const float SCALE = 1.0f;

bool drawing = false;
bool running = true;
bool UPDATEZOOM = false;
bool moving = false;

bool show_menu = false; // menu toggle state
SDL_Color BLACK = {0, 0, 0, 255};
inline const char *BUTTON_LOCATION = "icons/buttons.png";
inline const char *COLOR_WHEEL_LOCATION = "icons/colorWheel.png";

//////////////////////FONTS//////////////////////
int TOTALTEXTS = 3;
float FONTSIZE = 20.0f;
inline const char *FONT_LOCATION = "fonts/Roboto/Roboto-VariableFont_wdth,wght.ttf";
int w[3] = {0, 0, 0};
int h[3] = {0, 0, 0};

#endif