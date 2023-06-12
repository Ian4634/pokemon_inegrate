#include<my_headers/player_source.h>

static int read_word(char *word, FILE *f) {
    char ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == ' ') {
            *word = '\0';
            return 1;
        } else if (ch == '\n') {
            *word = '\0';
            return 0;
        } else {
            *word++ = ch;
        }
    }
    
    // Add the null terminator if the end of the file is reached
    *word = '\0';
    return EOF;
}
static unsigned int hash(char *name){
    int hash_value = 0;
    int index = 0;
    for(;*name != '\0';name++){
        hash_value += *name * index++;
    }
    hash_value %= PLAYER_TABLE_SIZE;
    return hash_value;    //which location is store
}

static void initialize_player_table(){
    for(int i=0;i<PLAYER_TABLE_SIZE;i++){
        player_table[i] = NULL;
    }
}

bool add_player(Player *p){
    //printf("adding %s\n", p->name);
    Player **location = &player_table[hash(p->name)];
    if(*location == NULL){
        *location = p;
        p->next = NULL;
    }else{
        Player *cur = *location;
        Player *pre = NULL;
        for(;cur != NULL; pre = cur, cur = cur->next);
        pre->next = p;
        p->next = NULL;
    }
    return true;
}
void traverse(){
    for(int i=0;i<PLAYER_TABLE_SIZE;i++){
        printf("slot %d\n", i);
        for(Player *cur = player_table[i];cur != NULL;cur = cur->next){
            printf("--%s %s %d %d %d", cur->name, cur->password, cur->blood, cur->coin, cur->potion);
            for(int a=0;a<MAX_POKEMONS && cur->pokemons[a] != NULL; a++){
                printf(" >>%s", cur->pokemons[a]);
            }
            printf("\n");
        }
    }
}
//find a person in the location by their name
Player *player_lookup(char *name){
    traverse();
    Player *location = player_table[hash(name)];
    
    if(location == NULL){
        printf("location is null\n");
        return NULL;
    }else{
        Player *cur = location;
        for(;cur != NULL && strcmp(name, cur->name) != 0;cur = cur->next);
        if(cur){
            return cur;
        }else{
            return NULL;
        }
    }
}

Player *player_delete(char *name);
// eason 0000 100 0 0 flower ibu flower
static Player *create(FILE *f){

    Player *new_player = malloc(sizeof(Player));
    char *token;
    
    /* store working line to lineBuffer */
    
    fgets(lineBuffer, 1024, f);

    if(strcmp(lineBuffer, "end-of-file") == 0){
            return NULL;
    }

    // operations
    token = strtok(lineBuffer, " ");
    strcpy(new_player->name, token);

    token = strtok(NULL, " ");
    strcpy(new_player->password, token);

    token = strtok(NULL, " ");
    new_player->blood = atoi(token);

    token = strtok(NULL, " ");
    new_player->coin = atoi(token);

    token = strtok(NULL, " ");
    new_player->potion = atoi(token);

    int i = 0; // keep track of amount of pokemons read
    while(1){
        token = strtok(NULL, " ");
        if(token){
            // remove \n
            char *temp = token;
            for(;*temp != '\0'; temp++);
            temp--; // points to last char of lineBuffer
            if(*temp == '\n') *temp = '\0';

            
            // initialize new-user->pokemons to NULL
            for(int a = 0;a<MAX_POKEMONS;a++){
                new_player->pokemons[a] == NULL;
            }
            // add pokemon to user->pokemons
            new_player->pokemons[i] = malloc(128);
            strcpy(new_player->pokemons[i++],token);
        }else{
            break;
        }
    }

    add_player(new_player);
    return new_player;
}

void add_minus_blood(Player *p, int x){
    p->blood += x;
}

void add_minus_potion(Player *p, int x){
    p->potion += x;
}

void add_minus_coin(Player *p, int x){
    p->coin += x;
}
void add_pokemon(Player *p, char *pokemon_name){
    int index = 0;
    if(p == NULL){
        printf("p is null\n");
        return;
    }
    
    for(;p->pokemons[index]!=NULL;index++);
    printf("after\n");
    p->pokemons[index] = malloc(100);
    strcpy(p->pokemons[index], pokemon_name);
}
void rewrite(){
    FILE *out = fopen("login_data.txt", "w");
    for(int i=0;i<PLAYER_TABLE_SIZE;i++){
        // per slot
        for(Player *cur = player_table[i];cur != NULL;cur = cur->next){
            fprintf(out,"%s %s %d %d %d", cur->name, cur->password, cur->blood, cur->coin, cur->potion);
            for(int a=0;a<MAX_POKEMONS && cur->pokemons[a] != NULL; a++){
                fprintf(out," %s", cur->pokemons[a]);
            }
            fprintf(out, "\n");
        }
    }
    fprintf(out, "end-of-file");
    fclose(out);
}

void player_source_init(){
    initialize_player_table();
    FILE *f = fopen("login_data.txt", "r");
    while(create(f) != NULL);
    fclose(f);
}


