#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rng.h"
#include "data.h"

int main(int argc, char *argv[]) {


    int find = 0;
    int index_monster = 0;
    char* end;
    long int seed = strtol(argv[3], &end, 10);
    srnd(seed);
    Unit monster;
    Unit enemy;
    int num_o_enemies;

    Unit * end2;
    num_o_enemies = strtol(argv[2], &end2, 10);
    Unit* list_o_enemies = (Unit*) malloc(num_o_enemies * sizeof(Unit));


    if(argc == 4){


        for (int i = 0; i < MONSTER_TYPE_COUNT; i++) {

            if (strcmp(monster_types[i].name, argv[1]) == 0){
                find = 1;
                index_monster = i;
                i = MONSTER_TYPE_COUNT;

            }
        }
        if (find == 0){
            return 1;
        }

        monster.type = &monster_types[index_monster];
        monster.hp = MONSTER_INITIAL_HP;
        monster.level = 0;

        for (int i = 0; i < num_o_enemies; i++) {


            int random = rnd(0, ENEMY_TYPE_COUNT-1);
            enemy.type = &enemy_types[random];

            random = rnd(ENEMY_MIN_INIT_HP, ENEMY_MAX_INIT_HP);
            enemy.hp = random;

            random = rnd(0, UNIT_MAX_LEVEL);
            enemy.level = random;

            list_o_enemies[i] = enemy;

        }

    }
    else if(argc == 6){


        for (int i = 0; i < MONSTER_TYPE_COUNT; i++) {

            if (strcmp(monster_types[i].name, argv[1]) == 0){
                find = 1;
                index_monster = i;
                i = MONSTER_TYPE_COUNT;
            }
        }
        if (find == 0){
            return 1;
        }

        monster.type = &monster_types[index_monster];
        monster.hp = MONSTER_INITIAL_HP;
        monster.level = 0;


        FILE * fpointer = fopen(argv[5], "r");

        char one[UNIT_TYPE_NAME_LEN];
        int two[100];
        int three[100];
        int pocet_cyklov = 0;

        if (fpointer == NULL){
            return 2;
        } else{
            int a = fscanf(fpointer,"%s %d %d", one, &two, &three);
            while (a == 3) {

                strcpy(enemy_types[pocet_cyklov].name, one);
                enemy_types[pocet_cyklov].att = *two;
                enemy_types[pocet_cyklov].def = *three;

                a = fscanf(fpointer,"%s %d %d", one, &two, &three);
                pocet_cyklov++;
            }

            if(pocet_cyklov != 8){
                return 3;
            }

        }

        for (int i = 0; i < num_o_enemies; i++) {

            int random = rnd(0, ENEMY_TYPE_COUNT-1);
            enemy.type = &enemy_types[random];

            random = rnd(ENEMY_MIN_INIT_HP, ENEMY_MAX_INIT_HP);
            enemy.hp = random;

            random = rnd(0, UNIT_MAX_LEVEL);
            enemy.level = random;

            list_o_enemies[i] = enemy;

        }

        fclose(fpointer);
    }

    printf("%s, ", monster.type->name);
    printf("ATT:%d, ", monster.type->att);
    printf("DEF:%d, ", monster.type->def);
    printf("HP:%d, ", monster.hp);
    printf("LVL:%d\n", monster.level);

    for (int i = 0; i < num_o_enemies; i++) {

        printf("[%d] ", i);
        printf("%s, ", list_o_enemies[i].type->name);
        printf("ATT:%d, ", list_o_enemies[i].type->att);
        printf("DEF:%d, ", list_o_enemies[i].type->def);
        printf("HP:%d, ", list_o_enemies[i].hp);
        printf("LVL:%d\n", list_o_enemies[i].level);

    }

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

    while (fight == 1){

        int unit_to_attack = 0;

        for (int i = 1; i < num_o_enemies; i++) {
            if (list_o_enemies[unit_to_attack].hp <= 0){
                unit_to_attack = i;
            }
            else if(list_o_enemies[unit_to_attack].hp > list_o_enemies[i].hp && list_o_enemies[i].hp > 0){
                unit_to_attack = i;
            }
        }

        if (all_enemies_dead == 0 && monster.hp > 0){

            //////////////////////////////// MONSTER ATTACK ////////////////////////////////
            base_damage = 30 + monster.level - list_o_enemies[unit_to_attack].level;

            c1 = rnd(1, monster.hp);
            c2 = monster.type->att;
            strength = 100 + c1 + c2;

            d1 = rnd(1, list_o_enemies[unit_to_attack].hp);
            d2 =list_o_enemies[unit_to_attack].type->def;
            defense = 100 + d1 + d2;

            damage = ((base_damage * strength) / defense);
            total_moster_damage = total_moster_damage + damage;

            list_o_enemies[unit_to_attack].hp = list_o_enemies[unit_to_attack].hp - damage;
            ////////////////////////////////////////////////////////////////////////////////
            printf("\n%s => %d => [%d] %s", monster.type->name, damage, unit_to_attack, list_o_enemies[unit_to_attack].type->name);
            printf("\n");
            ////////////////////////////////////////////////////////////////////////////////

        }

        for (int i = 0; i < num_o_enemies; i++) {
            if (list_o_enemies[i].hp > 0 && monster.hp > 0 && all_enemies_dead == 0){
                //////////////////////////////// ENEMIES ATTACK ////////////////////////////////
                base_damage = 30 + list_o_enemies[i].level - monster.level;

                c1 = rnd(1, list_o_enemies[i].hp);
                c2 = list_o_enemies[i].type->att;
                strength = 100 + c1 + c2;

                d1 = rnd(1, monster.hp);
                d2 = monster.type->def;
                defense = 100 + d1 + d2;

                damage = ((base_damage * strength) / defense);
                total_enemy_damage = total_enemy_damage + damage;

                monster.hp = monster.hp - damage;
                ////////////////////////////////////////////////////////////////////////////////
                printf("[%d] %s => %d => %s\n", i, list_o_enemies[i].type->name, damage, monster.type->name);
                ////////////////////////////////////////////////////////////////////////////////
            }else{
                num_o_dead_enemies = num_o_dead_enemies + 1;
                if (num_o_dead_enemies == num_o_enemies){
                    all_enemies_dead = 1;
                }

            }

            if (monster.hp <= 0){
                monster_dead = 1;
                i = num_o_enemies;
            }
            if (all_enemies_dead == 1 || monster_dead == 1){
                fight = 0;
            }

        }
        num_o_dead_enemies = 0;

        if (monster_dead == 0 && monster.level < UNIT_MAX_LEVEL){
            monster.level = monster.level + 1;
        }

        printf("\n%s, ", monster.type->name);
        printf("ATT:%d, ", monster.type->att);
        printf("DEF:%d, ", monster.type->def);
        printf("HP:%d, ", monster.hp);
        printf("LVL:%d\n", monster.level);

        for (int i = 0; i < num_o_enemies; i++) {

            printf("[%d] ", i);
            printf("%s, ", list_o_enemies[i].type->name);
            printf("ATT:%d, ", list_o_enemies[i].type->att);
            printf("DEF:%d, ", list_o_enemies[i].type->def);
            printf("HP:%d, ", list_o_enemies[i].hp);
            printf("LVL:%d\n", list_o_enemies[i].level);

        }

    }

    if (all_enemies_dead == 1){
        printf("\nWinner: %s", monster.type->name);
    } else if (monster_dead == 1){
        printf("\nWinner: Enemy");
    }
    printf("\nTotal monster DMG: %d", total_moster_damage);
    printf("\nTotal enemies DMG: %d", total_enemy_damage);

    return 0;
}