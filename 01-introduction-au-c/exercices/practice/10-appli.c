/*
*File: 10-appli.c
*Created on: 26-08-2026
*Auteur: Ahmed Tidiane
*Consigne: Écris un programme qui détermine si une année est bissextile,
en stockant le résultat dans un bool. Règle : divisible par 4, sauf les années 
divisibles par 100 qui ne le sont pas, sauf celles divisibles par 400 qui le sont.
*/

#include <stdio.h>
#include <stdbool.h>

int main() {
    int annee = 2026;
    bool is_bissextile = (annee%4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
    printf("L'année %d est %s\n", annee, is_bissextile ? "bissextile" : "non bissextile");
    return 0;
}