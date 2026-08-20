/*
 * 06_variables.c - declarer, afficher et modifier des variables
 * Date: 19-08-2026
 * Auteur: Tidiane
 * Compil.: gcc -Wall -Wextra -std=c17 06_variables.c -o 06_variables
 */
#include <stdio.h>

int main(void) {
    /* Calcul du prix TTC d'un article */
    float prix_ht  = 15000.0f;   /* en FCFA */
    float taux_tva = 0.18f;      /* 18 %    */
    float tva      = prix_ht * taux_tva;
    float prix_ttc = prix_ht + tva;

    printf("Prix HT  : %.2f FCFA\n", prix_ht);
    printf("TVA 18%%  : %.2f FCFA\n", tva);
    printf("Prix TTC : %.2f FCFA\n\n", prix_ttc);

    /* Aire d'un rectangle */
    int longueur = 4;
    int largeur  = 6;
    int aire     = longueur * largeur;
    printf("Aire du rectangle %dx%d : %d\n\n", longueur, largeur, aire);

    /* Plusieurs variables, plusieurs types */
    char  initiale = 'T';
    int   age      = 25;
    float taille   = 1.82f;
    printf("%c a %d ans et mesure %.2f m\n", initiale, age, taille);

    /* Modifier une valeur */
    age = age + 1;
    printf("L'an prochain : %d ans\n", age);

    return 0;
}
