/*
 * 28_structures.c - structures, tableaux de structures, pointeurs de structures
 */
#include <stdio.h>
#include <string.h>

typedef struct {
    char  nom[50];
    int   age;
    float moyenne;
} Etudiant;

void afficher(const Etudiant *e) {
    printf("  %-10s %3d ans   %5.2f\n", e->nom, e->age, e->moyenne);
}

void anniversaire(Etudiant *e) {
    e->age++;
}

Etudiant creer(const char *nom, int age, float moyenne) {
    Etudiant e;
    snprintf(e.nom, sizeof(e.nom), "%s", nom);
    e.age = age;
    e.moyenne = moyenne;
    return e;
}

int main(void) {
    Etudiant classe[3] = {
        {"Tidiane", 25, 15.5f},
        {.nom = "Awa",    .age = 22, .moyenne = 17.0f},
        {.nom = "Moussa", .age = 24, .moyenne = 12.5f}
    };

    int n = 3;

    printf("Classe :\n");
    for (int i = 0; i < n; i++) {
        afficher(&classe[i]);
    }

    /* Modification par pointeur */
    anniversaire(&classe[0]);
    printf("\nApres l'anniversaire de %s :\n", classe[0].nom);
    afficher(&classe[0]);

    /* Recherche du meilleur */
    int meilleur = 0;
    for (int i = 1; i < n; i++) {
        if (classe[i].moyenne > classe[meilleur].moyenne) {
            meilleur = i;
        }
    }
    printf("\nMeilleure moyenne : %s (%.2f)\n", classe[meilleur].nom, classe[meilleur].moyenne);

    /* Creation par fonction */
    Etudiant nouveau = creer("Fatou", 21, 19.0f);
    printf("\nNouvel etudiant :\n");
    afficher(&nouveau);

    printf("\nsizeof(Etudiant) = %zu octets\n", sizeof(Etudiant));
    return 0;
}
