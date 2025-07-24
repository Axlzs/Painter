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