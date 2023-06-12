#ifndef POKEMON_STATS_H
#define POKEMON_STATS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10  //to define how much table
#define PLAYER_TABLE_SIZE 10
#define MAX_POKEMONS 10
#define DEBUG 0
//pokemon's data
struct pokemon{
    char name[100];
    char attributes1[100];
    char attributes2[100];
    int blood;
    int attack;
    int defense;
    int special_attack;
    int special_defense;
    int speed;
    struct pokemon *next;
};

typedef struct pokemon Pokemon;

Pokemon flower;
Pokemon dragan;
Pokemon turtle;
Pokemon pikachu;
Pokemon nine_tails;
Pokemon fat;
Pokemon strange;
Pokemon stupid;
Pokemon ibu;

void pokemon_stats_init();

//make sure every table is empty
void initialize_hash_table();

bool hash_table_add(Pokemon *p);

//find a person in the table by their name
Pokemon *hash_table_lookup(char *name);

void hash_table_delete(char *name);

 // STATS


/* player data */

/***********************************************************
*   use the player_source_init(); when starting the game,  *
*   do the things you want, and use rewrite() to update    *
*   changes into database before closing the game          *
***********************************************************/
#define BAG_SIZE 10

struct player{
    char name[100];
    char password[100];
    int blood;
    int coin;
    int potion;
    char *pokemons[MAX_POKEMONS];
    struct player *next;
};

typedef struct player Player;
Player *player_table[PLAYER_TABLE_SIZE];
char lineBuffer[1024];
//make sure every location is empty

void player_source_init();
bool add_player(Player *p);

//find a person in the location by their name
Player *player_lookup(char *name);

Player *player_delete(char *name);

void add_minus_blood(Player *p, int x);
void add_minus_potion(Player *p, int x);
void add_minus_coin(Player *p, int x);
void add_pokemon(Player *p, char *pokemon_name);

void rewrite();
void traverse();
#endif