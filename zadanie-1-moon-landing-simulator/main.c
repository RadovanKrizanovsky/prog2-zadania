#include <stdio.h>

int main() {

    double m = 0.0;
    double T = 0.0;
    double v0 = 0.0;
    double H = 0.0;
    double g = 0.0;
    double vsoft = 0.0;
    double dt = 0.0;
    double df = 0.0;
    double v = 0.0;
    double h = 0.0;
    double t = 0.0;
    double a = 0.0;
    double total = 0.0;
    int s = 0;

    scanf("%lf", &m);
    scanf("%lf", &T);
    scanf("%lf", &v0);
    scanf("%lf", &H);
    scanf("%lf", &g);
    scanf("%lf", &vsoft);
    scanf("%lf", &dt);

    printf("m=%.3f\n", m);
    printf("T=%.3f\n", T);
    printf("v0=%.3f\n", v0);
    printf("H=%.3f\n", H);
    printf("g=%.3f\n", g);
    printf("vsoft=%.3f\n", vsoft);
    printf("dt=%.3f\n", dt);

    double A = T/m;
    df = ((A-g)*H)/A;
    printf("df=%.3f\n", df);

    h = H;
    a = ((-1.0)*g);
    double vyska_pre_motor = H - df;

    while (h > 0.0){

        if(h > vyska_pre_motor){
            a = ((-1.0)*g);
            s = 0;
        }
        else if (h <= vyska_pre_motor && v < vsoft){
            a = A - g;
            s = 1;
            total = total + dt;
        }
        else if (h <= vyska_pre_motor && v >= vsoft){
            a = ((-1.0)*g);
            s = 0;
        }

        printf("t=%.3f h=%.3f v=%.3f s=%d\n", t, h, v, s);

        h = h + (v * dt) + (a * dt * dt * 0.5);
        v = v + (a * dt);
        t = t + dt;

    }
    if(h <= 0.0){
        printf("t=%.3f h=%.3f v=%.3f\n", t, h, v);
    }
    printf("total=%.3f\n", total);



    return 0;
}
