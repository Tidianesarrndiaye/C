#include <stdio.h>

int main() {
    float largeur = 5.5;
    float longueur = 7.25;
    float perimetre = 2 * (longueur + largeur);
    float aire = longueur * largeur;
    printf("Perimetre: %.2f\n", perimetre);
    printf("Aire: %.2f\n", aire);
    return 0;
}