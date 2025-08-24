class Button{
    public:
    SDL_FRect button;
    SDL_Texture* iconTexture = nullptr;
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

    void render(SDL_Renderer *renderer) const {
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
    
    
    //degining surfaces and textures
    SDL_Surface *iconSurface;
    SDL_Surface *iconSurface1;
    SDL_Texture *iconTexture;
    SDL_Texture *iconTexture1;

    //Creating a button class
    Button eraseButton(0,0,50,50);
    Button drawButton(50,0,50,50);

    SDL_FRect dstRect = eraseButton.getFRect();
    SDL_FRect dstRect1 = drawButton.getFRect();

    //Setting and checking if an icon is found 
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

    //Rendering
    SDL_RenderTexture(renderer,iconTexture, NULL, &dstRect);
    SDL_RenderTexture(renderer,iconTexture1, NULL, &dstRect1);