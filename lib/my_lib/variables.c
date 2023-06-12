#include <my_headers/main.h>

static SDL_Window *window; // allocate memory
static SDL_Renderer *renderer;
static SDL_Texture *map_texture; // these texture are used in render copy
static SDL_Texture *player_texture; 
static SDL_Rect playerDestRect;
static TTF_Font *font;
static SDL_Color color;

void fontInit(){
    font = TTF_OpenFont("./font/times.ttf", 50);
    if(font == NULL){
        printf("font not loaded");
    }else{
        printf("font loaded\n");
    }
    SDL_Color color = {255,255,255};
}
TTF_Font *getFont(){
    return font;
}

void defineWindow(){
    window = SDL_CreateWindow("Image Background", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
}
SDL_Window *getWindow(){
    return window;
}

void defineRenderer(){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
}
SDL_Renderer *getRenderer(){
    return renderer;
}


void defineMapTexture(){
    map_texture = IMG_LoadTexture(getRenderer(), "./image/map.jpg");
    if(map_texture == NULL){
        printf("%s", SDL_GetError());
    }
}
SDL_Texture *getMapTexture(){
    return map_texture;
}

void definePlayerTexture(){
    player_texture = IMG_LoadTexture(renderer, "./image/player.png");
    if(player_texture == NULL){
        printf("%s", SDL_GetError());
    }
}
SDL_Texture *getPlayerTexture(){
    return player_texture;
}

void definePlayerDestRect(){
    playerDestRect.x = SCREEN_WIDTH / 2 - 20;
    playerDestRect.y = SCREEN_HEIGHT / 2 + 3;
    playerDestRect.w = 45; // Example width and height for player character
    playerDestRect.h = 35;
}
SDL_Rect *getPlayerDestRect(){
    return &playerDestRect;
}

void initialize(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if(TTF_Init() < 0){
        printf("TTF is WTF");
    }

    fontInit();
    
}

void player_mapInit(){
    defineWindow();
    defineRenderer();
    defineMapTexture();
    definePlayerTexture();
    definePlayerDestRect();

    SDL_RenderClear(getRenderer());
    SDL_RenderCopy(getRenderer(), getMapTexture(), NULL, NULL);
    SDL_RenderCopy(getRenderer(), getPlayerTexture(), NULL, getPlayerDestRect());
    SDL_RenderPresent(getRenderer());
}
void flipScreen(){
    SDL_RenderClear(getRenderer());
    SDL_RenderCopy(getRenderer(), getMapTexture(), NULL, NULL);
    SDL_RenderCopy(getRenderer(), getPlayerTexture(), NULL, getPlayerDestRect());
    SDL_RenderPresent(getRenderer());
}

