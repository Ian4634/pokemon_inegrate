#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <my_headers/variables.h>
#include <my_headers/inventory.h>
#include <my_headers/player_source.h>
// Window dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define DEBUG 0
#define Radom_MAX 8
#define Radom_MIN 1
// create surface, create texture with surface -> create renderer -> render to window

// create surface, create texture with surface -> create renderer -> render to window
// this program is the program to deal with Battle_System()
// go on certain x,y -> battle system
//battle system functions : 1) button to press 2) functions to use skill 3) show out player's pokemon ,enemies pokemon and anmations while using skill.
//                             4) short music when using skill 5) change BGM(specific) 6) count the exp,hp...ect. 

typedef struct{
    SDL_Surface *Surface;
    SDL_Texture *Texture;
    SDL_Rect DestRect;
}SDL_need;

SDL_need battle_needs;
SDL_need enemy_needs;
SDL_need player_needs;
SDL_need ball_needs;

SDL_Rect set_DestRect(SDL_Rect xy, int x, int y, int w, int h);
void initialize_battle(int enemy_num){   
    player_needs.Texture = IMG_LoadTexture(getRenderer(), "./image/master.png");
    player_needs.DestRect = set_DestRect(player_needs.DestRect, 274, 414, 85, 65);

    battle_needs.Texture = IMG_LoadTexture(getRenderer(), "./image/battleBackground.jpg");
    if(battle_needs.Texture == NULL) printf("Battle need Texture is NULLLL");
    

    

    
    ball_needs.Texture = IMG_LoadTexture(getRenderer(), "./image/ball.png");
    ball_needs.DestRect = set_DestRect(ball_needs.DestRect, 274, 414, 85, 65);
    switch(enemy_num){
            case 1:
                enemy_needs.Texture = IMG_LoadTexture(getRenderer(),"./image/gengar.png");
                break;
            case 2:
                enemy_needs.Texture = IMG_LoadTexture(getRenderer(),"./image/magikarp.png");

                break;
            case 3:
                enemy_needs.Texture = IMG_LoadTexture(getRenderer(),"./image/pikachu.png");
                break;
            case 4:
                enemy_needs.Texture = IMG_LoadTexture(getRenderer(),"./image/guyly.png");
                break;
            case 5:
                enemy_needs.Texture = IMG_LoadTexture(getRenderer(),"./image/ducklin.png");
                break;
            case 6:
                enemy_needs.Texture = IMG_LoadTexture(getRenderer(),"./image/mizueve.png");
                break;
            case 7:
                enemy_needs.Texture = IMG_LoadTexture(getRenderer(),"./image/rat.png");
                break;
            case 8:
                enemy_needs.Texture = IMG_LoadTexture(getRenderer(),"./image/mud.png");
                break;
            default:
                break;
        }

    enemy_needs.DestRect = set_DestRect(enemy_needs.DestRect, 485, 22, 320, 240);
    // SDL_need enemy_needs = {enemy_needs.Surface = IMG_Load("./image/ball.png"),enemy_needs.Texture = SDL_CreateTextureFromSurface(getRenderer(), enemy_needs.Surface),enemy_needs.DestRect = set_DestRect(enemy_needs.DestRect, 645, 192, 85, 65)};
    //SDL_need player_needs = {player_needs.Surface = IMG_Load("./image/ball.png"),player_needs.Texture = SDL_CreateTextureFromSurface(getRenderer(), player_needs.Surface),player_needs.DestRect = set_DestRect(player_needs.DestRect, 274, 414, 85, 65)};
    //SDL_need ball_needs = {ball_needs.Surface = IMG_Load("./image/ball.png"),ball_needs.Texture = SDL_CreateTextureFromSurface(getRenderer(), ball_needs.Surface),ball_needs.DestRect = set_DestRect(ball_needs.DestRect, 274, 414, 85, 65)};

    if(battle_needs.Texture){
        printf("not null\n");
    }else{
        printf("battleneed is null\n");
    }
    SDL_RenderCopy(getRenderer(), battle_needs.Texture, NULL, NULL); //要在(645,192) 放上敵人,(274,414)放上自己出戰的
    SDL_RenderCopy(getRenderer(), enemy_needs.Texture, NULL, &enemy_needs.DestRect); //敵人
    SDL_RenderCopy(getRenderer(), player_needs.Texture, NULL, &player_needs.DestRect); //player
}
//-------------------------------------------------------------------------------------------------//


void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int duration) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), surface);

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(getRenderer(), texture, NULL, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    SDL_Delay(duration);
}
//-------------------------------------------------------------------------------------------------//


int rand_enemy(){
    int x = rand() % (Radom_MAX - Radom_MIN + 1) + Radom_MIN;
    return x;
}

SDL_Rect set_DestRect(SDL_Rect xy, int x, int y, int w, int h){ //設定座標的大小
    xy.x = x;
    xy.y = y;
    xy.w = w;
    xy.h = h;
    return xy;
}

void check_ballnumber(int *ball_number, SDL_need ball_needs, SDL_Renderer* renderer, SDL_need battle_needs, SDL_need enemy_needs, SDL_need player_needs, int *catched,int enemy_num){
    
    if(player_lookup(username)->pokemons[9] != NULL){
            return;
        }
    if ((*ball_number) >= 1){
        int frequent_1 = 60, frequent_2 = 20;
        
        while (frequent_1--){
            //initialize_battle(enemy_num);
            SDL_RenderCopy(getRenderer(), battle_needs.Texture, NULL, NULL); //要在(645,192) 放上敵人,(274,414)放上自己出戰的
            SDL_RenderCopy(getRenderer(), enemy_needs.Texture, NULL, &enemy_needs.DestRect); //敵人
            SDL_RenderCopy(getRenderer(), player_needs.Texture, NULL, &player_needs.DestRect); //player
            SDL_RenderCopy(getRenderer(), ball_needs.Texture, NULL, &ball_needs.DestRect);
            SDL_RenderPresent(getRenderer());
            ball_needs.DestRect.x += 6.18; // 定義好球移動軌跡
            ball_needs.DestRect.y -= 3.7;

            printf("loop%s\n", SDL_GetError());

            SDL_Delay(5); // ball hits after flying 
        }
        
        (*ball_number)--;
        printf("ball number: %d\n", ball_number);

        int angle = 30; // 傾斜角度

        while (frequent_2--){
            SDL_RenderClear(getRenderer());
            //initialize_battle(enemy_num);
            SDL_RenderCopy(getRenderer(), battle_needs.Texture, NULL, NULL); //要在(645,192) 放上敵人,(274,414)放上自己出戰的
            SDL_RenderCopy(getRenderer(), enemy_needs.Texture, NULL, &enemy_needs.DestRect); //敵人
            SDL_RenderCopy(getRenderer(), player_needs.Texture, NULL, &player_needs.DestRect); //player
            SDL_RenderCopyEx(getRenderer(), ball_needs.Texture, NULL, &ball_needs.DestRect, angle, NULL, SDL_FLIP_NONE); // 將球傾斜指定角度
            SDL_RenderPresent(getRenderer());
            //SDL_RenderPresent(getRenderer());
            angle = -angle; // 改變傾斜角度方向
            SDL_Delay(20); // ball hits after flying 
            //SDL_RenderClear(getRenderer());
            //initialize_battle(enemy_num);
            //SDL_RenderPresent(getRenderer());
        }

        if(rand_enemy() % 2 == 0){ // 這邊要接到data 1.有抓到 2. 沒抓到
            (*catched) = 1;
        }else{
            (*catched) = 0;
        }

    }
    else{
        printf("no ball\n");
    }
}
void you_die(){
    SDL_need die;
    die.Texture = IMG_LoadTexture(getRenderer(),"./image/die.jpg");
    SDL_RenderCopy(getRenderer(), die.Texture, NULL, NULL);
}
int paper_scissor_stone(char gamer, SDL_need battle_needs, SDL_need enemy_needs, SDL_need player_needs,SDL_Renderer* renderer, int enemy_num){
    //char gamer; // 玩家出拳
    int computer; // 電腦出拳
    int result; // 比賽結果.
    int return_value=0;
    // 初始化 SDL_ttf
    if (TTF_Init() < 0) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
    }

    TTF_Font* font = TTF_OpenFont("./font/regular.ttf", 28);
    if (font == NULL) {
        printf("TTF_OpenFont failed: %s\n", TTF_GetError());
    }
    
    switch (gamer){
        case 65: //A
        case 97: //a
            gamer=4;
            break;
        case 66: //B
        case 98: //b
            gamer=7;
            break;
        case 67: //C
        case 99: //c
            gamer=10;
            break;
        default:
            break;
    }
    
    srand((unsigned)time(NULL)); // 隨機數種子
    computer=rand()%3; // 產生隨機數並取餘，得到電腦出拳
    result=(int)gamer+computer; // gamer 為 char 型別，數學運算時要強制轉換型別
    printf("computer use");
    SDL_Color color = {255, 0, 0, 255};
    renderText(getRenderer(), getFont(), "Computer Use", color, 100, 100, 1000);
    // 刷新渲染器并等待退出事件
    SDL_RenderPresent(getRenderer());
    switch (computer){
        case 0:
            printf(" scissor\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(getRenderer(), getFont(), "Scissor!", color, 100, 150, 1000);
            SDL_RenderPresent(getRenderer());
            break; //4  1
        case 1:
            printf(" stone\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(getRenderer(), getFont(), "Stone!", color, 100, 150, 1000);
            SDL_RenderPresent(getRenderer());
            break; //7 2
        case 2:
            printf(" paper\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(getRenderer(), getFont(), "Paper!", color, 100, 150, 1000);
            SDL_RenderPresent(getRenderer());
            break;  //10 3
    }
    printf("your use");
    //SDL_Color color = {255, 255, 255, 255};
    renderText(getRenderer(), getFont(), "You Use!", color, 100, 200, 1000);
    SDL_RenderPresent(getRenderer());
    switch (gamer){
        case 4:
            printf(" scissor\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(getRenderer(), getFont(), "Scissor!", color, 100, 250, 1000);
            SDL_RenderPresent(getRenderer());
            break;
        case 7:
            printf(" stone\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(getRenderer(), getFont(), "Stone!", color, 100, 250, 1000);
            SDL_RenderPresent(getRenderer());
            break;
        case 10:
            printf(" paper\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(getRenderer(), getFont(), "Paper!", color, 100, 250, 1000);
            SDL_RenderPresent(getRenderer());
            break;
    }
    if(result==6||result==7||result==11){
        //敵人扣血
        printf("you win!\n");
        //SDL_Color color = {255, 255, 255, 255};
        renderText(getRenderer(), getFont(), "You win!", color, 100, 300, 1000);
        SDL_RenderPresent(getRenderer());
        add_minus_coin(player_lookup(username), 50);
        return_value=1;
    }else if(result==5||result==9||result==10){
        //我方扣血
        printf("computer win!\n");
        //SDL_Color color = {255, 255, 255, 255};
        renderText(getRenderer(), getFont(), "Computer Win!", color, 100, 300, 1000);
        add_minus_blood(player_lookup(username), -1);
        
        if(player_lookup(username)->blood <= 0){
            you_die();
            //renderText(getRenderer(), getFont(), "You Die", color, 100, 350, 1000);
        }
        SDL_RenderPresent(getRenderer());
        printf("you now have %d blood\n", player_lookup(username)->blood);
        
        
        return_value=1;
    }else{
        printf("draw\n");
        renderText(getRenderer(), getFont(), "Draw!", color, 100, 300, 1000);
        SDL_RenderPresent(getRenderer());
        return_value=0;
    }
    SDL_Delay(1000);
    SDL_RenderClear(getRenderer());
    initialize_battle(enemy_num);
    SDL_RenderPresent(getRenderer());
    return return_value;
}




int checkBattle(int *ball_number){
    

    int enemy_num=0,running=1,catched=0,return_value=0;
    SDL_Event event;
        //換場景先暫時當作battke system 的地方   
        enemy_num = rand_enemy();
        printf("--------------------%d\n", enemy_num);
        
        //char pokemon[9] = {"==","gengar","magikarp","pikachu","guyly","ducklin","mizueve","rat","mud"};
        //enemy_needs.Texture = SDL_CreateTextureFromSurface(getRenderer(), enemy_needs.Surface);
        //enemy_needs.DestRect = set_DestRect(enemy_needs.DestRect, 645, 192, 85, 65);


        printf("after\n");
        SDL_RenderClear(getRenderer());
        initialize_battle(enemy_num);
        SDL_RenderPresent(getRenderer());
        printf("after present\n");
        #if DEBUG
            printf("enemy_num:%d\n",enemy_num);
            printf("enemyDestRect:%d %d\n", enemy_needs.DestRect.x, enemy_needs.DestRect.y);
        #endif
    
    while(running){

        while (SDL_PollEvent(&event)){

            if(event.type == SDL_QUIT){
                // Handle quit event
                running = 0;
                break;
            }
            if(catched == 1){
                // Handle quit event
                printf("catched == enemy num\n");
                catched = enemy_num;
                running = 0;
                break;
            }else   
                printf("catched == 0");

            if(return_value == 1){                
                printf("WIN/LOSE condition\n");
                running = 0;
                break;  
            }
            //////////////


            if(event.type == SDL_KEYDOWN){
                // Check which key was pressed 
                    switch(event.key.keysym.sym){
                    case SDLK_q:
                        return_value=paper_scissor_stone('A',battle_needs,  enemy_needs,  player_needs, getRenderer(), enemy_num);
                        break;
                    case SDLK_w:
                        return_value=paper_scissor_stone('B',battle_needs,  enemy_needs,  player_needs, getRenderer(), enemy_num);
                        break;
                    case SDLK_e:
                        return_value=paper_scissor_stone('C',battle_needs,  enemy_needs,  player_needs, getRenderer(), enemy_num); //決定勝負
                        break;
                    case SDLK_b: //丟球動畫
                        SDL_Delay(50);
                        check_ballnumber(ball_number, ball_needs, getRenderer(), battle_needs, enemy_needs, player_needs, &catched, enemy_num);
                        SDL_RenderClear(getRenderer());
                        initialize_battle(enemy_num);
                        SDL_RenderPresent(getRenderer());
                        break;   
                    default:
                        break; 
                    }
                    /*if(catched == 1) //haddle win conditions:
                        add_pokemon(player_list, "pikachu");*/
                
            }
        }
        SDL_Delay(50);

    }
    return catched;
}


