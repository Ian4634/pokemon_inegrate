#include <my_headers/main.h>
#include<my_headers/events.h>
#include<my_headers/inventory.h>
#include<my_headers/player_source.h>
#include <my_headers/variables.h>

static int POKEMON_X = SCREEN_WIDTH / 2;
static int POKEMON_Y = SCREEN_HEIGHT / 2;
static int WORD_X = 420;
static int WORD_Y = 510;
static int COIN_X = 420;
static int COIN_Y = 540;
static void show_potions(char *name){
    char *potion_base = "Potions: ";
    char *coin_base = "Coins: ";
    char num_of_potions[10];
    char coins[10];
    char temp[2];

    SDL_Color textColor = {0,0,0};
    for(;*potion_base != '\0';potion_base++){
        SDL_Surface *wordSurface = TTF_RenderGlyph_Solid(getFont(), *potion_base, textColor);
        SDL_Texture *wordTexture = SDL_CreateTextureFromSurface(getRenderer(), wordSurface);
        SDL_Rect wordRect;
        wordRect.w = 10;
        wordRect.h = 26;
        wordRect.x = WORD_X;
        wordRect.y = WORD_Y;
        WORD_X += 10;
        SDL_RenderCopy(getRenderer(), wordTexture, NULL, &wordRect);
    }

    // show potion
    sprintf(num_of_potions, "%d", player_lookup(name)->potion); // converts to int string
    for(char *temp = num_of_potions;*temp != '\0'; temp++){
        SDL_Surface *wordSurface = TTF_RenderGlyph_Solid(getFont(), *temp, textColor);
        SDL_Texture *wordTexture = SDL_CreateTextureFromSurface(getRenderer(), wordSurface);
        SDL_Rect wordRect;
        wordRect.w = 10;
        wordRect.h = 26;
        wordRect.x = WORD_X;
        wordRect.y = WORD_Y;
        WORD_X += 10;
        SDL_RenderCopy(getRenderer(), wordTexture, NULL, &wordRect);
    }

    // show coin
    for(;*coin_base != '\0';coin_base++){
        SDL_Surface *wordSurface = TTF_RenderGlyph_Solid(getFont(), *coin_base, textColor);
        SDL_Texture *wordTexture = SDL_CreateTextureFromSurface(getRenderer(), wordSurface);
        SDL_Rect wordRect;
        wordRect.w = 10;
        wordRect.h = 26;
        wordRect.x = COIN_X;
        wordRect.y = COIN_Y;
        COIN_X += 10;
        SDL_RenderCopy(getRenderer(), wordTexture, NULL, &wordRect);
    }

    sprintf(coins, "%d", player_lookup(name)->coin);
    for(char *temp = coins;*temp != '\0'; temp++){
        SDL_Surface *wordSurface = TTF_RenderGlyph_Solid(getFont(), *temp, textColor);
        SDL_Texture *wordTexture = SDL_CreateTextureFromSurface(getRenderer(), wordSurface);
        SDL_Rect wordRect;
        wordRect.w = 10;
        wordRect.h = 26;
        wordRect.x = COIN_X;
        wordRect.y = COIN_Y;
        COIN_X += 10;
        SDL_RenderCopy(getRenderer(), wordTexture, NULL, &wordRect);
    }

}

static void show_pokemon(char *name){

    char dir[100] = "./image/";
    strcat(dir, name);
    strcat(dir, ".jpg");

    SDL_Rect PokemonDestRect;
    PokemonDestRect.x = POKEMON_X;
    PokemonDestRect.y = POKEMON_Y;
    PokemonDestRect.w = 100;
    PokemonDestRect.h = 100;
    
    // set location to render for next pokemon
    if(POKEMON_X >= 700){ // change to next line
        POKEMON_Y += 100;
        POKEMON_X = SCREEN_WIDTH / 2;
    }else{
        POKEMON_X += 100;
    }
    

    SDL_Texture *pokemonTexture = IMG_LoadTexture(getRenderer(),dir);
    SDL_RenderCopy(getRenderer(), pokemonTexture, NULL, &PokemonDestRect);
    SDL_RenderPresent(getRenderer());
}

static void show_button(){
    // 740 570 w = 60 h = 20
    SDL_Rect buttonRect;
    buttonRect.w = 100;
    buttonRect.h = 33;
    buttonRect.x = 700;
    buttonRect.y = 570;

    SDL_Texture *buttonTexture = IMG_LoadTexture(getRenderer(), "./image/button.jpg");
    SDL_RenderCopy(getRenderer(), buttonTexture, NULL, &buttonRect);
}

// show *name's inventory
// this function copies everything to the renderer and present em together
void show_inventory(char *name){
    // reset these values otherwise they continues to grow
    POKEMON_X = SCREEN_WIDTH / 2;
    POKEMON_Y = SCREEN_HEIGHT / 2;
    WORD_Y = 510;
    COIN_X = 420;
    COIN_Y = 540;
    WORD_X = 420;
    // get the desired player struct
    Player *user = player_lookup(name);
    printf("he has %d %d\n", user->coin, user->potion);

    // create and show the base of inventory
    SDL_Rect InventoryDestRect;
    InventoryDestRect.x = SCREEN_WIDTH / 2;
    InventoryDestRect.y = SCREEN_HEIGHT / 2;
    InventoryDestRect.w = SCREEN_WIDTH / 2;
    InventoryDestRect.h = SCREEN_HEIGHT / 2;

    SDL_Texture *inventory_texture = IMG_LoadTexture(getRenderer(), "./image/inventory.jpg");
    SDL_RenderCopy(getRenderer(), inventory_texture, NULL, &InventoryDestRect);
    SDL_RenderPresent(getRenderer());

    // check if user found
    if(user == NULL) return ;

    //show player's pokemons
    for(int i=0; i<10 && user->pokemons[i] != NULL;i++){
        show_pokemon(user->pokemons[i]);
    }
    show_potions(name);
    show_button();
    SDL_RenderPresent(getRenderer());
}