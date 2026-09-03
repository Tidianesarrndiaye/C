/*
 * 09-appli3.c Test des operateur ternaires
 * Date: 25-08-2026
 * Auteur: Ahmed Tidiane
 */

#include <stdio.h>

int main() {
    int age = 20;
    char *statut = (age >= 18) ? "majeur" : "mineur";
    printf("%s\n", statut);
    return 0;
 }