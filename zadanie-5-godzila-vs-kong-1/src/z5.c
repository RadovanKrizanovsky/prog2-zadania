#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rng.h"
#include "data.h"


int main(int argc, char *argv[]) {

    int monster1row;
    int monster1col;
    int monster2row;
    int monster2col;


    char* end;
    long int seed = strtol(argv[1], &end, 10);
    srnd(seed);

    FILE * fpointer = fopen(argv[2], "r");

    if (fpointer == NULL)
    {
        return 2;
    }

    int map_width = 5;
    int map_height = 5;
    int num_o_monsters;
    int num_o_enemies;

    int a = fscanf(fpointer,"%d %d %d %d", &map_width, &map_height, &num_o_monsters, &num_o_enemies);

    char velkost[100];
    int **map;

    map = malloc(sizeof(int*) * map_height);

    for (int i = 0; i < map_height; i++)
    {
        map[i] = malloc(sizeof(int) * map_width);
    }

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            map[i][j] = 0;
        }

    }


    int row;
    int col;
    char monster_type_name[100];
    int hp;
    int level;

    Unit* monster_list = (Unit*) malloc(num_o_monsters * sizeof(Unit));

    for (int f = 0; f < num_o_monsters; f++)
    {
        int b = fscanf(fpointer,"%d %d %s %d %d", &row, &col, monster_type_name, &hp, &level);
        monster_list[f].hp = hp;
        monster_list[f].level = level;
        int monster_index = 0;
        if (strcmp(monster_type_name,"Godzilla") == 0)
        {
            monster_index = 0;
        }
        else if (strcmp(monster_type_name,"Kong") == 0)
        {
            monster_index = 1;
        }
        else if (strcmp(monster_type_name,"Mechagodzilla") == 0)
        {
            monster_index = 2;
        }
        monster_list[f].type = &monster_types[monster_index];
        map[row][col] = 10000 + f + 1;

        if (f == 0)
        {
            monster1row = row;
            monster1col = col;
        }
        else if (f == 1)
        {
            monster2row = row;
            monster2col = col;
        }
    }


    Unit* enemy_list = (Unit*) malloc(num_o_enemies * sizeof(Unit));
    int enemy_type_index;

    for (int i = 0; i < num_o_enemies; i++)
    {
        int c = fscanf(fpointer,"%d %d %d %d %d", &row, &col, &enemy_type_index, &hp, &level);
        enemy_list[i].hp = hp;
        enemy_list[i].level = level;

        enemy_list[i].type = &enemy_types[enemy_type_index];
        map[row][col] = i + 1;
    }

    char move[150];
    scanf("%s", move);
    int move_len = strlen(move);


    for (int g = 0; g < move_len; ++g)
    {

        if (move[g] == 'd')
        {
            map[monster1row][monster1col] = 0;
            if (monster1row == map_height-1)
            {
                monster1row = 0;
            }
            else
            {
              monster1row++;
            }

        }
        else if (move[g] == 'u')
        {
            map[monster1row][monster1col] = 0;
            if (monster1row == 0)
            {
                monster1row = map_height - 1;
            }
            else
            {
                monster1row--;
            }

        }
        else if (move[g] == 'l')
        {
            map[monster1row][monster1col] = 0;
            if (monster1col == 0)
            {
                monster1col = map_width - 1;
            }
            else
            {
                monster1col--;
            }

        }
        else if (move[g] == 'r')
        {
            map[monster1row][monster1col] = 0;
            if (monster1col == map_width-1)
            {
                monster1col = 0;
            }
            else
            {
                monster1col++;
            }

        }

        /////////////////////////////////////////

        if (move[g] == 'D')
        {
            map[monster2row][monster2col] = 0;
            if (monster2row == map_height-1)
            {
                monster2row = 0;
            }
            else
            {
                monster2row++;
            }

        }
        else if (move[g] == 'U')
        {
            map[monster2row][monster2col] = 0;
            if (monster2row == 0)
            {
                monster2row = map_height - 1;
            }
            else
            {
                monster2row--;
            }

        }
        else if (move[g] == 'L')
        {
            map[monster2row][monster2col] = 0;
            if (monster2col == 0)
            {
                monster2col = map_width - 1;
            }
            else
            {
                monster2col--;
            }

        }
        else if (move[g] == 'R')
        {
            map[monster2row][monster2col] = 0;
            if (monster2col == map_width-1)
            {
                monster2col = 0;
            }
            else
            {
                monster2col++;
            }

        }

        /////////////////////////////////

        int total_enemy_damage = 0;
        int total_moster_damage = 0;
        int fight = 1;
        int monster_dead = 0;
        int all_enemies_dead = 0;
        int num_o_dead_enemies = 0;
        int damage = 0;
        int base_damage = 0;
        int strength = 0;
        int defense = 0;
        int d1 = 0;
        int d2 = 0;
        int c1 = 0;
        int c2 = 0;
        int i = 0;
        int monster1dead = 0;
        int monster2dead = 0;

        if ((move[g] == 'r' || move[g] == 'l' || move[g] == 'd' || move[g] =='u') && monster1dead == 0)
        {
            //////////////// MONSTER1 VS ENEMY

            i = map[monster1row][monster1col]-1;

            if (map[monster1row][monster1col] > 0 && map[monster1row][monster1col] < 10000){

                while (monster_list[0].hp > 0 && enemy_list[i].hp > 0)
                {


                    base_damage = 30 + enemy_list[i].level - monster_list[0].level;

                    c1 = rnd(1, enemy_list[i].hp);
                    c2 = enemy_list[i].type->att;
                    strength = 100 + c1 + c2;

                    d1 = rnd(1, monster_list[0].hp);
                    d2 = monster_list[0].type->def;
                    defense = 100 + d1 + d2;

                    damage = ((base_damage * strength) / defense);

                    monster_list[0].hp = monster_list[0].hp - damage;


                    if (monster_list[0].hp <= 0)
                    {
                        monster1dead = 1;
                        fight = 0;
                    }

                    if (enemy_list[i].hp <= 0){
                        map[monster1row][monster1col] = 10001;
                        fight = 0;

                    }

                    if(monster1dead == 0){

                        base_damage = 30 + monster_list[0].level - enemy_list[i].level;

                        c1 = rnd(1, monster_list[0].hp);
                        c2 = monster_list[0].type->att;
                        strength = 100 + c1 + c2;

                        d1 = rnd(1, enemy_list[i].hp);
                        d2 = enemy_list[i].type->def;
                        defense = 100 + d1 + d2;

                        damage = ((base_damage * strength) / defense);

                        enemy_list[i].hp = enemy_list[i].hp - damage;



                    }

                    if (enemy_list[i].hp <= 0){
                        map[monster1row][monster1col] = 10001;
                        fight = 0;

                    }
                    if (monster_list[0].hp > 0){
                        if (monster_list[0].level < UNIT_MAX_LEVEL){ //////////////////////////////////dddddddddddddddddddddddddddddddd
                            monster_list[0].level++;
                        }
                    }
                }



            }
            ///////////////////MONSTER 1 VS MONSTER 2
            else if (map[monster1row][monster1col] > 10000){

                while (monster_list[0].hp > 0 && monster_list[1].hp > 0){

                    base_damage = 30 + monster_list[1].level - monster_list[0].level;

                    c1 = rnd(1, monster_list[1].hp);
                    c2 = monster_list[1].type->att;
                    strength = 100 + c1 + c2;

                    d1 = rnd(1, monster_list[0].hp);
                    d2 = monster_list[0].type->def;
                    defense = 100 + d1 + d2;

                    damage = ((base_damage * strength) / defense);

                    monster_list[0].hp = monster_list[0].hp - damage;

                    if (monster_list[0].hp <= 0)
                    {
                        monster1dead = 1;
                    }

                    if(monster1dead == 0){



                        base_damage = 30 + monster_list[0].level - monster_list[1].level;

                        c1 = rnd(1, monster_list[0].hp);
                        c2 = monster_list[0].type->att;
                        strength = 100 + c1 + c2;

                        d1 = rnd(1, monster_list[1].hp);
                        d2 = monster_list[1].type->def;
                        defense = 100 + d1 + d2;

                        damage = ((base_damage * strength) / defense);

                        monster_list[1].hp = monster_list[1].hp - damage;



                    }

                    if (monster_list[1].hp <= 0){
                        monster2dead = 1;
                        map[monster1row][monster1col] = 10001;
                        fight = 0;

                    }
                    if (monster_list[1].hp > 0){
                        if (monster_list[1].level < UNIT_MAX_LEVEL){ //////////////////////////////////sssssssssssssssssssssssssssssssss
                            monster_list[1].level++;
                        }
                    }
                    if (monster_list[0].hp > 0){
                        if (monster_list[0].level < UNIT_MAX_LEVEL){ //////////////////////////////////dddddddddddddddddddddddddddddddd
                            monster_list[0].level++;
                        }
                    }
                }



        }
        else
        {
            if (monster_list[0].hp > 0){
                map[monster1row][monster1col] = 10001;
            }
        }

        }
        else if ((move[g] == 'R' || move[g] == 'L' || move[g] == 'D' || move[g] =='U') && monster2dead == 0){

            //////////////// MONSTER2 VS ENEMY

            i = map[monster2row][monster2col]-1;

            if (map[monster2row][monster2col] > 0 && map[monster2row][monster2col] < 10000){

                while (monster_list[1].hp > 0 && enemy_list[i].hp > 0)
                {


                    base_damage = 30 + enemy_list[i].level - monster_list[1].level;

                    c1 = rnd(1, enemy_list[i].hp);
                    c2 = enemy_list[i].type->att;
                    strength = 100 + c1 + c2;

                    d1 = rnd(1, monster_list[1].hp);
                    d2 = monster_list[1].type->def;
                    defense = 100 + d1 + d2;

                    damage = ((base_damage * strength) / defense);

                    monster_list[1].hp = monster_list[1].hp - damage;


                    if (monster_list[1].hp <= 0)
                    {
                        monster2dead = 1;
                        fight = 0;
                    }

                    if (enemy_list[i].hp <= 0){
                        map[monster2row][monster2col] = 10002;
                        fight = 0;

                    }

                    if(monster2dead == 0){


                        base_damage = 30 + monster_list[1].level - enemy_list[i].level;

                        c1 = rnd(1, monster_list[1].hp);
                        c2 = monster_list[1].type->att;
                        strength = 100 + c1 + c2;

                        d1 = rnd(1, enemy_list[i].hp);
                        d2 = enemy_list[i].type->def;
                        defense = 100 + d1 + d2;

                        damage = ((base_damage * strength) / defense);

                        enemy_list[i].hp = enemy_list[i].hp - damage;



                    }

                    if (enemy_list[i].hp <= 0){
                        map[monster2row][monster2col] = 10002;
                        fight = 0;

                    }

                    if (monster_list[1].hp > 0){
                        if (monster_list[1].level < UNIT_MAX_LEVEL){ //////////////////////////////////sssssssssssssssssssssssssssssssss
                            monster_list[1].level++;
                        }
                    }

                }

            }
                ///////////////////MONSTER 2 VS MONSTER 1
            else if (map[monster2row][monster2col] > 10000){

                while (monster_list[1].hp > 0 && monster_list[0].hp > 0){

                    base_damage = 30 + monster_list[0].level - monster_list[1].level;

                    c1 = rnd(1, monster_list[0].hp);
                    c2 = monster_list[0].type->att;
                    strength = 100 + c1 + c2;

                    d1 = rnd(1, monster_list[1].hp);
                    d2 = monster_list[1].type->def;
                    defense = 100 + d1 + d2;

                    damage = ((base_damage * strength) / defense);

                    monster_list[1].hp = monster_list[1].hp - damage;

                    if (monster_list[1].hp <= 0)
                    {
                        monster2dead = 1;
                    }

                    if(monster2dead == 0){



                        base_damage = 30 + monster_list[1].level - monster_list[0].level;

                        c1 = rnd(1, monster_list[1].hp);
                        c2 = monster_list[1].type->att;
                        strength = 100 + c1 + c2;

                        d1 = rnd(1, monster_list[0].hp);
                        d2 = monster_list[0].type->def;
                        defense = 100 + d1 + d2;

                        damage = ((base_damage * strength) / defense);

                        monster_list[0].hp = monster_list[0].hp - damage;



                        if (monster_list[0].hp <= 0){
                            monster1dead = 1;
                            map[monster2row][monster2col] = 10002;
                            fight = 0;

                        }
                    }

                    if (monster_list[0].hp <= 0){
                        monster1dead = 1;
                        map[monster2row][monster2col] = 10002;
                        fight = 0;

                    }

                    if (monster_list[1].hp > 0){
                        if (monster_list[1].level < UNIT_MAX_LEVEL){ //////////////////////////////////sssssssssssssssssssssssssssssssss
                            monster_list[1].level++;
                        }
                    }
                    if (monster_list[0].hp > 0){
                        if (monster_list[0].level < UNIT_MAX_LEVEL){ //////////////////////////////////dddddddddddddddddddddddddddddddd
                            monster_list[0].level++;
                        }
                    }
                }

            }
            else
            {
                map[monster2row][monster2col] = 10002;
                if (monster_list[1].hp > 0){
                    map[monster2row][monster2col] = 10002;
                }

            }


        }
        fight = 1;

    }

    int final_monsters = 0;
    int final_enemies = 0;

    printf("%d ", map_width);
    printf("%d ", map_height);

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            if (map[i][j] > 0 && map[i][j] <= 10000){
                final_enemies++;
            }
            else if (map[i][j] > 10000){
                final_monsters++;
            }
        }
    }
    printf("%d ", final_monsters);
    printf("%d ", final_enemies);
    printf("\n");

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            if (map[i][j] == 10001){
                printf("%d %d ", i, j);
                printf("%s ", monster_list[0].type->name);
                printf("%d ", monster_list[0].hp);
                printf("%d", monster_list[0].level);
                if (final_enemies > 0 || final_monsters > 1){
                    printf("\n");
                }
            }
        }
    }

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            if (map[i][j] == 10002){
                printf("%d %d ", i, j);
                printf("%s ", monster_list[1].type->name);
                printf("%d ", monster_list[1].hp);
                printf("%d", monster_list[1].level);
                if (final_enemies > 0){
                    printf("\n");
                }
            }
        }
    }

    int index = 0;
    int nums = 0;

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            if (map[i][j] > 0 && map[i][j] <= 10000){
                nums++;
                printf("%d %d ", i, j);
                if (strcmp(enemy_list[map[i][j]-1].type->name, "Infantry") == 0){
                    printf("%d ", 0);
                }
                else if (strcmp(enemy_list[map[i][j]-1].type->name, "Tank") == 0){
                    printf("%d ", 1);
                }
                else if (strcmp(enemy_list[map[i][j]-1].type->name, "Artillery") == 0){
                    printf("%d ", 2);
                }
                else if (strcmp(enemy_list[map[i][j]-1].type->name, "Cruiser") == 0){
                    printf("%d ", 3);
                }
                else if (strcmp(enemy_list[map[i][j]-1].type->name, "Submarine") == 0){
                    printf("%d ", 4);
                }
                else if (strcmp(enemy_list[map[i][j]-1].type->name, "Helicopter") == 0){
                    printf("%d ", 5);
                }
                else if (strcmp(enemy_list[map[i][j]-1].type->name, "Fighter") == 0){
                    printf("%d ", 6);
                }
                else if (strcmp(enemy_list[map[i][j]-1].type->name, "Bomber") == 0){
                    printf("%d ", 7);
                }
                printf("%d ", enemy_list[map[i][j]-1].hp);
                printf("%d", enemy_list[map[i][j]-1].level);
                if (nums < final_enemies){
                    printf("\n");
                }
            }
        }
    }


    free(map);
    return 0;
}