#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>

/////////////////////     NEMENIT !!!      ////////////////////////

// Funkcia na nacitanie jedneho riadku textu zo standardneho vstupu.

// VSTUP:
//        Ziadny.
// VYSTUP:
//        Smernik na alokovany blok pamate
//        obsahujuci C retazec reprezentujuci
//        nacitany riadok ukonceny znakom '\n'.
//        Funkcia vrati NULL ak:
//          * dojde k chybe pri alokacii pamate
//          * dojde chybe citania
//          * narazi sa na EOF (End-of-file)

// Dokumentacia k funkcii 'fgets':
// https://www.cplusplus.com/reference/cstdio/fgets/?kw=fgets

// Dokumentacia k funkcii 'realloc':
// https://www.cplusplus.com/reference/cstdlib/realloc/?kw=realloc

char *readline() {
    const size_t BSIZE = 100;
    char *line = NULL;
    size_t capacity = 0;

    do {
        // Priprav dostatok pamate.
        capacity += BSIZE;

        // Alokuj miesto na capacity + '\0'.
        line = (char *) realloc(line, (capacity + 1) * sizeof(char));
        if (line == NULL)
            return line;

        // Nacitaj zo vstupu riadok (resp. jeho zvysok).
        if (fgets(line + capacity - BSIZE, BSIZE + 1, stdin) == NULL) {
            free(line);
            return NULL; // doslo k chybe citania alebo sme narazili na EOF
        }
        // Opakuj, pokym sa nenacita cely riadok.
        // Indikacia, ze zostal zvysok riadku:
        //   1. je naplnena cela BSIZE
        //   2. na konci nie je '\n'
    } while (strlen(line + capacity - BSIZE) >= BSIZE
             && line[capacity - 1] != '\n');
    // nacitany riadok obsahuje na konci znak '\n'
    return line;
}

////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]){

    // Poznamky ku 'getopt':

    // 'optstring' specifikuje platne prepinace programu

    // ak funkcia 'getopt' narazi na neplatny prepinac, vrati znak '?'
    // ak 'optstring' zacina znakom ':', vtedy 'getopt' vrati znak ':'
    // v pripade chybajuceho povinneho parametra prepinaca

    // ak je v 'optstringu' za pismenom prepinaca znak ':', znamena to,
    // ze dany prepinac vyzaduje parameter

    // povinny parameter aktualneho prepinaca vieme ziskat cez globalny
    // smernik 'optarg'

    // ked su rozpoznane vsetky prepinace, funkcia 'getopt' vrati -1
    // ak zostali nejake non-option argumenty, tak prvy non-option argument
    // ma index dany globalnou premennou 'optind'

    int opt;
    char* optstring = ":aculr:";
    int p_a = 0;
    int p_c = 0;
    int p_u = 0;
    int p_l = 0;
    int p_r = 0;


    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'a':
                p_a = 1;
                break;
            case 'c':
                p_c = 1;
                break;
            case 'u':
                if (p_l > 0 && p_u > 0){
                    return 3;
                }
                p_u = 1;
                break;
            case 'l':
                p_l = 1;
                if (p_l > 0 && p_u > 0){
                    return 3;
                }
                break;
            case 'r':
                p_r = 1;
                break;
            case '?':
                return 1;
                break;
            case ':':
                return 2;
                break;
                ///////////////////////////////////////////////////////////// treba deafult?
        }
    }
    /*
    if(optind < argc){
        for(int i=optind;i<argc;i++){
            printf("Non-option CMD argument: %s\n",argv[i]);
        }
    }
    */
    char *premenna = optarg;
    char *line = NULL;
    int x = 0;

    while ((line = readline()) != NULL) {

        if (p_a == 1) {

            while (line[x] != NULL) {

                if (((int) line[x]) < 65 || (((int) line[x]) > 90 && (((int) line[x]) < 97)) || ((int) line[x]) > 122) {
                    line[x] = (char) 32;
                }
                x++;
            }
            line[x] = NULL;

        }

        x = 0;
        int y = 0;
        char newLine[200];
        if (p_c == 1) {

            while (line[x] != NULL) {

                if ((((int) line[x]) >= 65 && ((int) line[x]) <= 90) ||
                    (((int) line[x]) >= 97 && ((int) line[x]) <= 122)) {
                    line[y] = line[x];
                    y++;

                }
                x++;
            }
            line[y] = NULL;
        }
        x = 0;
        if (p_u == 1) {

            while (line[x] != NULL) {
                if ((((int) line[x]) >= 97 && ((int) line[x]) <= 122)) {
                    line[x] = toupper((char)line[x]);
                }
                x++;
            }
            line[x-1] = NULL;
        }

        x = 0;
        if (p_l == 1) {

            while (line[x] != NULL) {
                if ((((int) line[x]) >= 65 && ((int) line[x]) <= 90)) {
                    line[x] = tolower(line[x]);
                }
                x++;
            }
            line[x-1] = NULL;
        }

        if (optind < argc) {
            for (int i = optind; i < argc; i++) {

                y = 0;
                x = 0;
                /*
                if (p_r == 1) {
                    char por[100];
                    int dlzka = strlen(argv[i]);
                    while (line[x] != NULL) {

                        for (int j = 0; j < dlzka; j++) {
                            por[j] = line[j + y];
                            //por[j + 1] = NULL;

                        }
                        if (strcmp(por, argv[i]) == 0) {
                            printf("here");
                            for (int j = 0; j < strlen(argv[i]); j++) {

                                line[y+j] = premenna[j];
                            }
                        }

                        x++;
                        y++;
                    }
                }
                */
                if (p_r == 0) {
                    char por[100];
                    int dlzka = strlen(argv[i]);
                    while (line[x] != NULL) {

                        for (int j = 0; j < dlzka; j++) {
                            por[j] = line[j + y];
                            //por[j + 1] = NULL;
                        }
                        if (strcmp(por, argv[i]) == 0) {
                            for (int j = 0; j < strlen(argv[i]); j++) {
                                line[y+j] = (char)42;
                            }
                        }

                        x++;
                        y++;
                    }
                    line[x-1] = NULL;
                }

            }

            if (line == NULL) {
                return 0;
            }


        }

        if (p_r == 0) {
            printf("%s\n", line);
        }

        free(line);
    }
    return 0;
}