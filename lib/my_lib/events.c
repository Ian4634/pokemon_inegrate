#include<my_headers/main.h>
#include<my_headers/events.h>
#include<my_headers/inventory.h>
#include<my_headers/variables.h>
#include <my_headers/player_source.h>
#include <my_headers/game.h>
static void handlePlayerMovement(SDL_Event events){
    SDL_Rect *player = getPlayerDestRect();

    switch(events.key.keysym.sym){
        case SDLK_UP:
            if(player->y - 37 >= 0 && player->y - 37  <= 600)  player->y -= 37;
            break;
        case SDLK_DOWN:
            if(player->y + 37 >= 0 && player->y + 37  <= 590)  player->y += 37;
            break;
        case SDLK_LEFT:
            if(player->x - 53 >= 0 && player->x - 53 <= 800)  player->x -= 53;
            break;
        case SDLK_RIGHT:
            if(player->x + 53 >= 0 && player->x + 53 <= 800)  player->x += 53;
            break;
        
        default:
            printf("sth went wrong in playerMovement()\n");
    }
    SDL_RenderClear(getRenderer());
    SDL_RenderCopy(getRenderer(), getMapTexture(), NULL, NULL);
    SDL_RenderCopy(getRenderer(), getPlayerTexture(), NULL, getPlayerDestRect());
    SDL_RenderPresent(getRenderer());
}
static void handleMouseMovement(SDL_Event event){
    if(event.button.button == SDL_BUTTON_LEFT){
        printf("clicked at %d %d\n", event.button.x, event.button.y);
        if(event.button.x >= 5 && event.button.x <= 55 && event.button.y >= 560 && event.button.y <= 590){
            int *ball_number,catch_num=0;
            *ball_number = 10;

            char* pokemon[] = {"=_=", "gengar", "magikarp", "pikachu", "guyly", "ducklin", "mizueve", "rat", "mud"};
            
            catch_num = checkBattle(ball_number);
            if(catch_num != 0) {
                add_pokemon(player_lookup(username), pokemon[catch_num]);
                add_minus_coin(player_lookup(username), 50);
                }
            // catch pokemon
            show_inventory(username);
            

        }else if(event.button.x >= 700 && event.button.y >= 570){
            printf("buy a potion\n");
            Player *user_obj = player_lookup(username);
            if(user_obj->coin >= 100){
                user_obj->coin -= 100;
                user_obj->potion++;
                show_inventory(username); // have to refresh
            }
        }
    }
}
int handleEvents(){
    SDL_Event event;
    
    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            return 0;
            break;
        case SDL_KEYDOWN:
            handlePlayerMovement(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            handleMouseMovement(event);
            break;
        default:
            printf("Unhandled event %d\n", event.type);
            break;
        }
    }

    return 1;
}

