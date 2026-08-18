/*
 * 20_pointeurs.c - adresses, pointeurs, passage par adresse
 */
#include <stdio.h>

void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_max(const int tab[], int n, int *min, int *max) {
    *min = *max = tab[0];
    for (int i = 1; i < n; i++) {
        if (tab[i] < *min) *min = tab[i];
        if (tab[i] > *max) *max = tab[i];
    }
}

int main(void) {
    int age = 25;
    int *ptr = &age;

    printf("age    : %d\n", age);
    printf("&age   : %p\n", (void *) &age);
    printf("ptr    : %p\n", (void *) ptr);
    printf("*ptr   : %d\n\n", *ptr);

    *ptr = 30;
    printf("Apres *ptr = 30, age vaut %d\n\n", age);

    /* Echange par adresse */
    int x = 5, y = 10;
    printf("Avant  : x=%d y=%d\n", x, y);
    echanger(&x, &y);
    printf("Apres  : x=%d y=%d\n\n", x, y);

    /* Arithmetique de pointeurs sur un tableau */
    int notes[] = {12, 15, 8, 19};
    printf("Parcours avec un pointeur : ");
    for (int *p = notes; p < notes + 4; p++) {
        printf("%d ", *p);
    }
    printf("\n");

    /* Deux resultats renvoyes par pointeurs */
    int mn, mx;
    min_max(notes, 4, &mn, &mx);
    printf("min=%d  max=%d\n", mn, mx);

    return 0;
}
