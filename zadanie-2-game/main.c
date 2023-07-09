#include<stdio.h>

//////////////////     NEMENIT !!!      ///////////////////////

//    Vo vasom rieseni musite pouzit tieto funkcie na
//    generovanie pseudo-nahodnych cisiel.
//
//    Funkcia srnd(seed):
//       * Zavolajte 1-krat na zaciatku programu na
//       inicializaciu generovanej postupnosti cisiel.
//
//    Funkcia rnd(from, to):
//       * Sluzi na vygenerovanie dalsieho nahodneho
//       cisla z intervalu <from,to>.

#define R_MAX 2147483647 // vsetky generovane cisla su mensie ako R_MAX
static long long unsigned int SEED = 0x1; // seed generatora

void srnd(int seed) {
    SEED = seed;
}

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}

/////////////////////////////////////////////////////////////

int max(int num1, int num2){

    if(num1 > num2){
        return num1;
    }

    else if(num2 > num1){
        return  num2;
    }

    else{
        return num1;
    }

}


int main() {

    int n = 0;
    int m2 = 0;
    int seed = 0;
    int m1 = 0;
    const int Nmin = 10;
    const int Nmax = 100;

    scanf("%d", &seed);
    scanf("%d", &n);
    scanf("%d", &m1);
    scanf("%d", &m2);

    srnd(seed);

    if (seed <= 0 || ((m1 + m2)>(n/2)) || n < Nmin || n > Nmax){

        return 1;

    }
    int x;
    int draha[n];
    int y;
    int pozicie[n];

    for (x = 0; x < n; x++){

        draha[x] = 0;

    }

    for (y = 0; y < n; y++){

        pozicie[y] = 0;

    }

    int pocet_block = 0;
    int pocet_boost = 0;
    int rand_pos = 0;

    // |0-volne|  |1-blocker|  |2-booster|

    while (pocet_block < m1){

        rand_pos = rnd(1,(n-1));

        if(draha[rand_pos] == 0){
            draha[rand_pos] = 1;
            pocet_block++;
        }

    }

    while (pocet_boost < m2){

        rand_pos = rnd(1,(n-1));

        if(draha[rand_pos] == 0){
            draha[rand_pos] = 2;
            pocet_boost++;
        }

    }


    int pos_block[m1];
    int k = 0;
    int k_pos = 0;

    for(k = 0; k < n; k++){
        if (draha[k] == 1){
            pos_block[k_pos] = k;
            k_pos++;

        }

    }


    int pos_boost[m2];
    k = 0;
    k_pos = 0;

    for(k = 0; k < n; k++){
        if (draha[k] == 2){
            pos_boost[k_pos] = k;
            k_pos++;

        }

    }

    printf("BLOCK:");

    k = 0;

    for(k = 0; k < m1; k++){

        printf("%d ", pos_block[k]);

    }

    printf("\nBOOST:");

    k = 0;

    for(k = 0; k < m2; k++){

        printf("%d ", pos_boost[k]);

    }

    int h = 1;
    int t = 1;
    int r1 = 0;
    int r2 = 0;
    int hra = 1;
    int vitaz = 0;

    int p1p = -1;
    int p1np = -1;
    int p1b = 0;
    int p1nb = 0;

    int p2p = -1;
    int p2np = -1;
    int p2b = 0;
    int p2nb = 0;


    while (hra == 1){

        r1 = rnd(1, 6);
        r2 = rnd(1, 6);

        if (h == 1){

            if (p1np == -1){
                if ((r1+r2)>7){
                    p1p = p1np;
                    p1np = 0;
                    p1np = p1np + ((r1+r2)-7) + p1nb;
                    pozicie[p1np]++;
                }
                p1p = -1;

            }
            else if (r1 == r2 && r1 == 6 && p1np < p2np && p2np > -1){
                p2p = p2np;
                p1p = p1np;
                p1np = p2p;
                p2np = p1p;
                pozicie[p1np]++;
                pozicie[p2np]++;

            }
            else if (r1 == r2 && r1 == 1 && p1np > p2np && p2np > -1){
                p2p = p2np;
                p1p = p1np;
                p1np = p2p;
                p2np = p1p;
                pozicie[p1np]++;
                pozicie[p2np]++;

            }
            else if (p1np > -1){
                p1p = p1np;
                p1np = p1p + max(r1,r2) + p1nb;
                pozicie[p1np]++;
            }

            if (draha[p1np] == 2){
                draha[p1np] = 0;
                p1nb++;

            }
            else if (draha[p1np] == 1){
                draha[p1np] = 0;
                if (p1nb > 0){
                    p1nb = 0;
                }
                else if(p1nb == 0){
                    p1np = -1;
                }

            }
            else if (p1np == p2np){
                p2p = p2np;
                p2np = -1;
            }

            printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]",t , h, p1p, p1b, r1, r2, p1np, p1nb);
            p1b = p1nb;
            h = 2;
        }

        else if (h == 2){

            if (p2np == -1){
                if ((r1+r2)>7){
                    p2p = p2np;
                    p2np = 0;
                    p2np = p2np + ((r1+r2)-7) + p2nb;
                    pozicie[p2np]++;
                }
                p2p = -1;

            }
            else if (r1 == r2 && r1 == 6 && p2np < p1np && p1np > -1){
                p2p = p2np;
                p1p = p1np;
                p1np = p2p;
                p2np = p1p;
                pozicie[p1np]++;
                pozicie[p2np]++;

            }
            else if (r1 == r2 && r1 == 1 && p2np > p1np && p1np > -1){
                p2p = p2np;
                p1p = p1np;
                p1np = p2p;
                p2np = p1p;
                pozicie[p1np]++;
                pozicie[p2np]++;

            }
            else if (p2np > -1){
                p2p = p2np;
                p2np = p2p + max(r1,r2) + p2nb;
                pozicie[p2np]++;
            }

            if (draha[p2np] == 2){
                draha[p2np] = 0;
                p2nb++;

            }
            else if (draha[p2np] == 1){
                draha[p2np] = 0;
                if (p2nb > 0){
                    p2nb = 0;
                }
                else if(p2nb == 0){
                    p2np = -1;
                }
            }
            else if (p2np == p1np){
                p1p = p1np;
                p1np = -1;
            }

            printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]",t , h, p2p, p2b, r1, r2, p2np, p2nb);
            p2b = p2nb;
            h = 1;

        }

        if(p1np >= n){
            vitaz = 1;
            hra = 0;
        }
        else if(p2np >= n){
            vitaz = 2;
            hra = 0;
        }


    t++;

    }

    pozicie[0] = 0;

    int z = 0;
    int Hotspot = 0;

    for(z = 0; z < n; z++){
        if (Hotspot < pozicie[z]){
            Hotspot = pozicie[z];
        }
    }

    printf("\nWINNER:%d", vitaz);
    printf("\nHOTSPOT:%d", Hotspot);



    return 0;
    }




