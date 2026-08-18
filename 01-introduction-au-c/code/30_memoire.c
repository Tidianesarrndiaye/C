/*
 * 30_memoire.c - allocation dynamique
 * A verifier avec :  valgrind --leak-check=full ./30_memoire
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Notre propre version de strdup */
char *copie_chaine(const char *src) {
    char *dest = malloc(strlen(src) + 1);   /* +1 pour le '\0' */
    if (dest == NULL) return NULL;
    strcpy(dest, src);
    return dest;
}

int main(void) {
    int n = 5;

    int *tab = malloc((size_t) n * sizeof(*tab));
    if (tab == NULL) {
        fprintf(stderr, "Echec de malloc\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        tab[i] = (i + 1) * 10;
    }

    printf("Avant realloc (%d elements) : ", n);
    for (int i = 0; i < n; i++) printf("%d ", tab[i]);
    printf("\n");

    /* Agrandissement : jamais tab = realloc(tab, ...) */
    int *tmp = realloc(tab, 8 * sizeof(*tab));
    if (tmp == NULL) {
        free(tab);
        fprintf(stderr, "Echec de realloc\n");
        return 1;
    }
    tab = tmp;
    for (int i = 5; i < 8; i++) tab[i] = (i + 1) * 10;

    printf("Apres realloc (8 elements)  : ");
    for (int i = 0; i < 8; i++) printf("%d ", tab[i]);
    printf("\n\n");

    free(tab);
    tab = NULL;

    /* calloc : tout a zero */
    int *zeros = calloc(4, sizeof(*zeros));
    if (zeros == NULL) return 1;
    printf("calloc initialise a : ");
    for (int i = 0; i < 4; i++) printf("%d ", zeros[i]);
    printf("\n");
    free(zeros);

    /* Chaine allouee dynamiquement */
    char *c = copie_chaine("Bonjour le C");
    if (c != NULL) {
        printf("Copie dynamique     : %s\n", c);
        free(c);
    }

    /* Matrice dynamique 3x4 */
    int lignes = 3, colonnes = 4;
    int **m = malloc((size_t) lignes * sizeof(*m));
    if (m == NULL) return 1;
    for (int i = 0; i < lignes; i++) {
        m[i] = malloc((size_t) colonnes * sizeof(**m));
        if (m[i] == NULL) return 1;
        for (int j = 0; j < colonnes; j++) m[i][j] = i * colonnes + j;
    }

    printf("\nMatrice dynamique 3x4 :\n");
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) printf("%4d", m[i][j]);
        printf("\n");
    }

    for (int i = 0; i < lignes; i++) free(m[i]);
    free(m);

    return 0;
}
