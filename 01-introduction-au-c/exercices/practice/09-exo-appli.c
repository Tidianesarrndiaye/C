/*
 * File: 09-exo-appli.c
 * Date: 25-08-2026 // day/month/year
 * Auteur: Ahmed Tidiane
 * Consigne: Écris un programme qui, pour un entier n donné, affiche : 
 * s'il est pair ou impair, son carré, sa moitié en division entière, 
 * sa moitié en décimal, et le résultat de n & 1. Compare n % 2 et n & 1. 
*/
#include <stdio.h>
int main() {
    int n = 24;
    char *parite = (n % 2 == 0) ? "pair" : "impair";
    int carre = n * n;
    int moitie_entier = n / 2;
    float moitie_decimal = (float) n / 2.0; //
    int resultat_bitwise = n & 1;
    printf("L'entier %d est %s.\n", n, parite);
    printf("Son carré est %d.\n", carre);
    printf("Sa moitié en division entière est %d.\n", moitie_entier);
    printf("Sa moitié en décimal est %.2f.\n", moitie_decimal);
    printf("Le résultat de n & 1 est %d.\n", resultat_bitwise);
    printf("\nComparaison entre n %% 2 et n & 1 :\n");
    printf("Apparement n %% 2 et n & 1 donnent le même résultat pour chercher la parité.\n");
}