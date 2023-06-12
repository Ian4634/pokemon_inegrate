#ifndef VARIABLES
#define VARIABLES
#include <my_headers/main.h>

extern void fontInit();
extern TTF_Font *font;
extern SDL_Color color;
extern TTF_Font *getFont();

extern SDL_Window *window;
void defineWindow();
SDL_Window *getWindow();

extern SDL_Renderer *renderer;
void defineRenderer();
SDL_Renderer *getRenderer();

extern SDL_Texture *player_texture;
void definePlayerTexture();
SDL_Texture *getPlayerTexture();

extern SDL_Texture *map_texture;
void defineMapTexture();
SDL_Texture *getMapTexture();

extern SDL_Rect playerDestRect;
void definePlayerDestRect();
SDL_Rect *getPlayerDestRect();

void initialize();

void player_mapInit();
#define USERNAME_SIZE 50
char username[USERNAME_SIZE]; 
#endif