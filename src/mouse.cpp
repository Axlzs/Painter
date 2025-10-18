#define _USE_MATH_DEFINES

#include <cmath>
#include "mouse.hpp"
#include <iostream>

/////////////////////BUTTONS/////////////////////

SDL_Color GLOBALBACKGROUND = {255, 255, 255, 255};
/////////////////////BUTTONS/////////////////////

int extern WINDOWWIDTH;
int extern WINDOWHEIGHT;

void Mouse::enableEraser(bool value) {
    erasing = value;
    if (erasing){
        drawing = false;
        moving = false;

        brushsize = currentSize;
        currentSize = eraserSize;
        currentColor = GLOBALBACKGROUND;
    } else {
        currentColor = brushColor;
        currentSize = brushsize;
    }
}

void Mouse::enableDrawing(bool value) {
    drawing = value;
    if (drawing){
        erasing = false;
        moving = false;
    }
}

void Mouse::moveWindow(SDL_FRect& canvas) {
    erasing = false;
    drawing = false;
    //realx2 = x2 + canvas.x;
    //realy2 = y2 + canvas.y;

    if(realx1 != -1 && realy1 != 0){
        canvas.x += realx2 - realx1; // x2-x1 = deltaX
        canvas.y += realy2 - realy1; // y2-y1 = deltaY
    }
}

void Mouse::changeBrushSize(int amount) {
    currentSize+=amount;
    if(currentSize<=0){currentSize=1;}
}

void Mouse::changeBrushType(MouseType type){
    brushType = type;
}

struct Stroke {
    std::vector<SDL_Point> points;
    SDL_Color color;
    int brushSize;
    MouseType brushType;
};

std::vector<Stroke> AllStrokes;
std::vector<Stroke> UndoStrokes;

Stroke newStroke;

void createStroke(int x, int y, SDL_Color currentcolor, int currentsize, MouseType brushtype, int strokesToRedo){
    newStroke = Stroke{};
    newStroke.color = currentcolor;
    newStroke.brushSize = currentsize;
    newStroke.brushType = brushtype;
    newStroke.points.push_back({x, y});
    AllStrokes.push_back(newStroke);
    strokesToRedo=0;    
}

void addStroke(int x, int y){
    newStroke.points.push_back({x, y});
    AllStrokes.back().points.push_back({x, y});
    
}

void DrawBrush(SDL_Renderer *renderer, int x, int y, MouseType type, SDL_Color color, int brushsize) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (type == MouseType::RECT) {
        SDL_FRect rect = { (float)(x - brushsize/2), (float)(y - brushsize/2), (float)brushsize, (float)brushsize };
        SDL_RenderFillRect(renderer, &rect);
    } else if (type == MouseType::CIRCLE) {
        for (int dy = -brushsize/2; dy <= brushsize/2; dy++) {
            for (int dx = -brushsize/2; dx <= brushsize/2; dx++) {
                if (dx*dx + dy*dy <= (brushsize/2)*(brushsize/2)) {
                    SDL_RenderPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }
}
void BresenhalmActivate(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, MouseType type, SDL_Color color, int brushsize) {
    
    // Distance between points
    int dx = x2 - x1;
    int dy = y2 - y1;
    float dist = sqrt(dx*dx + dy*dy);

    // step for brush: smaller = smoother line
    float step = 1.0f; 

    for (float i = 0; i < dist; i += step) {
        float t = i / dist;  // normalized [0,1]
        int x = (int)std::lerp((float)x1, (float)x2, t);
        int y = (int)std::lerp((float)y1, (float)y2, t);
        DrawBrush(renderer, x, y, type, color, brushsize);
    }

    // ensure last point is drawn
    DrawBrush(renderer, x2, y2, type, color, brushsize);
}

void drawStroke(SDL_Renderer* renderer, SDL_Texture* texture){
    if (AllStrokes.size()>0){
        SDL_SetRenderTarget(renderer, texture);
        auto last_stroke = AllStrokes.back();
        SDL_Point prev = last_stroke.points[0];
        if(last_stroke.points.size()>1){
            for (auto i = 1; i < last_stroke.points.size(); i++){
                BresenhalmActivate(renderer, prev.x, prev.y, last_stroke.points[i].x, last_stroke.points[i].y, last_stroke.brushType, last_stroke.color, last_stroke.brushSize);
                prev = last_stroke.points[i];
            }
        } else {
                DrawBrush(renderer, prev.x, prev.y, last_stroke.brushType, last_stroke.color, last_stroke.brushSize);
        }
        SDL_SetRenderTarget(renderer, NULL);
    }
}

void reDrawStrokes(SDL_Renderer* renderer, SDL_Texture* texture){
    for (auto i: AllStrokes) {
        SDL_Point prev = i.points[0];
        if(i.points.size()>1){
            for (auto j = 1; j < i.points.size(); j++){
                BresenhalmActivate(renderer, prev.x, prev.y, i.points[j].x, i.points[j].y, i.brushType, i.color, i.brushSize);
                prev = i.points[j];
            }
        } else {
            DrawBrush(renderer, prev.x, prev.y, i.brushType, i.color, i.brushSize);
        }
    }
}

void undoStroke(int& strokestoredo){
    if (AllStrokes.size()>0){
        UndoStrokes.push_back(AllStrokes.back());
        AllStrokes.pop_back();
        strokestoredo = AllStrokes.size();
    }
}
void redoStroke(int& strokestoredo){
    if (UndoStrokes.size()>0){
        if(AllStrokes.size() == strokestoredo){
            AllStrokes.push_back(UndoStrokes.back());
            UndoStrokes.pop_back();
            strokestoredo = AllStrokes.size();
        } else {
            UndoStrokes.clear();
        }
    }
}

void MakeOutline(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, int currentsize, MouseType brushtype){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    SDL_SetRenderTarget(renderer, texture); // selects the layer, the coursor is on
    SDL_SetRenderDrawColor(renderer, 0,0,0,0); // sets the color to invisible
    SDL_RenderClear(renderer); // immediately overlays the invisible color
    SDL_SetRenderDrawColor(renderer, 0,0,0,180);
    if (brushtype == MouseType::RECT) {
        SDL_FRect rect = { (x - currentsize/2), (y - currentsize/2), (float)currentsize, (float)currentsize };
        SDL_RenderRect(renderer, &rect); // draws the textrue
    } else if (brushtype == MouseType::CIRCLE) {
        for (int dy = -currentsize/2; dy <= currentsize/2; dy++) {
            for (int dx = -currentsize/2; dx <= currentsize/2; dx++) {
                if (dx*dx + dy*dy <= (currentsize/2)*(currentsize/2)&& dx*dx + dy*dy >=(currentsize/2-1)*(currentsize/2-1)) {
                    SDL_RenderPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }
    SDL_SetRenderTarget(renderer, NULL); // deselects this layer 
    
}