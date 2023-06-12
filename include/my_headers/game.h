#ifndef GAME
#include<my_headers/main.h>
#include <my_headers/player_source.h>
typedef struct{
    SDL_Surface *Surface;
    SDL_Texture *Texture;
    SDL_Rect DestRect;
}SDL_need;

SDL_need battle_needs;
SDL_need enemy_needs;
SDL_need player_needs;
SDL_need ball_needs;
void game_init();
int checkBattle(int *ball_number);
#endif