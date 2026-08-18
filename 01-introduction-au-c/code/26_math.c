/*
 * 26_math.c - fonctions mathematiques
 * ATTENTION : compiler avec -lm
 *   gcc -Wall -Wextra -std=c17 26_math.c -o 26_math -lm
 */
#include <stdio.h>
#include <math.h>

/* M_PI n'est pas dans la norme stricte : avec -std=c17 il faut le definir soi-meme.
   (Avec -std=gnu17, math.h le fournit deja.) */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void) {
    printf("sqrt(64)     = %.2f\n", sqrt(64.0));
    printf("pow(4, 3)    = %.2f\n", pow(4.0, 3.0));
    printf("ceil(1.4)    = %.2f\n", ceil(1.4));
    printf("floor(1.4)   = %.2f\n", floor(1.4));
    printf("round(1.5)   = %.2f\n", round(1.5));
    printf("fabs(-7.25)  = %.2f\n\n", fabs(-7.25));

    /* Distance entre deux points */
    double x1 = 0.0, y1 = 0.0, x2 = 3.0, y2 = 4.0;
    double d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    printf("Distance (0,0)-(3,4) : %.2f\n", d);
    printf("Avec hypot           : %.2f\n\n", hypot(3.0, 4.0));

    /* Cercle */
    double r = 5.0;
    printf("Cercle de rayon %.1f :\n", r);
    printf("  aire      = %.4f\n", M_PI * r * r);
    printf("  perimetre = %.4f\n\n", 2.0 * M_PI * r);

    /* Interets composes : 100000 FCFA a 5 pourcent pendant 10 ans */
    double capital = 100000.0, taux = 0.05;
    printf("Capital final apres 10 ans : %.2f FCFA\n\n", capital * pow(1.0 + taux, 10.0));

    /* Le piege des decimaux */
    printf("0.1 + 0.2 == 0.3 ? %s\n", (0.1 + 0.2 == 0.3) ? "oui" : "non");
    printf("0.1 + 0.2 = %.20f\n", 0.1 + 0.2);
    printf("Comparaison correcte : %s\n",
           (fabs((0.1 + 0.2) - 0.3) < 1e-9) ? "egaux" : "differents");

    return 0;
}
