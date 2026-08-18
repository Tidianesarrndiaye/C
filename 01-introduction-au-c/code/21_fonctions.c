/*
 * 21_fonctions.c - definir et appeler des fonctions
 */
#include <stdio.h>

/* Prototypes */
float moyenne(float a, float b, float c);
void  afficher_mention(float note);
int   max2(int a, int b);
int   max3(int a, int b, int c);

int main(void) {
    float m = moyenne(12.0f, 15.5f, 9.0f);
    printf("Moyenne : %.2f -> ", m);
    afficher_mention(m);

    printf("max3(4, 17, 9) = %d\n", max3(4, 17, 9));
    return 0;
}

float moyenne(float a, float b, float c) {
    return (a + b + c) / 3.0f;
}

void afficher_mention(float note) {
    if      (note >= 16.0f) printf("Tres bien\n");
    else if (note >= 14.0f) printf("Bien\n");
    else if (note >= 12.0f) printf("Assez bien\n");
    else if (note >= 10.0f) printf("Passable\n");
    else                    printf("Insuffisant\n");
}

int max2(int a, int b) {
    return (a > b) ? a : b;
}

int max3(int a, int b, int c) {
    return max2(max2(a, b), c);
}
