/*
 * 16_tableaux.c - tableaux simples et 2D
 */
#include <stdio.h>

int main(void) {
    int notes[] = {12, 15, 8, 19, 14};
    size_t n = sizeof(notes) / sizeof(notes[0]);

    printf("Le tableau contient %zu elements\n", n);

    int somme = 0;
    int min = notes[0], max = notes[0];

    for (size_t i = 0; i < n; i++) {
        printf("notes[%zu] = %d\n", i, notes[i]);
        somme += notes[i];
        if (notes[i] < min) min = notes[i];
        if (notes[i] > max) max = notes[i];
    }

    printf("\nSomme   : %d\n", somme);
    printf("Min     : %d\n", min);
    printf("Max     : %d\n", max);
    printf("Moyenne : %.2f\n\n", (float) somme / (float) n);

    /* Tableau a deux dimensions */
    int matrice[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("Matrice 2x3 :\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%4d", matrice[i][j]);
        }
        printf("\n");
    }

    return 0;
}
