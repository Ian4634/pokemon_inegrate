#include <my_headers/main.h>
#include <my_headers/variables.h>
#include <my_headers/events.h>
#include <my_headers/login.h>
#include <my_headers/player_source.h>
#include <my_headers/game.h>
void text_stuff(){
    
}

int main(int argc, char *argv[]){
    /* initialize sdl */
    
    system("cls");
    //printf("Program started\n");
    initialize();
    player_source_init();

    printf("Finished initializing\n");
    int ball_number = 10;
    

    //checkBattle(getRenderer(), battle_needs, enemy_needs, player_needs, ball_needs, &ball_number);
    login_main();
    player_mapInit();
    while(handleEvents()){
       SDL_Delay(10);
    }
    rewrite();
    return 0;
    
}