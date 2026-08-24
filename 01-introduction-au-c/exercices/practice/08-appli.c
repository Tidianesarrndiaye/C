/* 08-appli.c Calcule le perimetre et l'aire
* Date: 20-08-2026
* Auteur: Ahmed Tidiane
* Compile : gcc -Wall -Wextra -std=c17 08-appli.c -o 08.appli.c
*/

#include <stdio.h>
#define PI 3.14
int main() {
    float rayon = 5 ; //en cm
    float perimetre = 2*rayon*PI;
    float aire = rayon*rayon * PI; 
    printf("Le prerimetre du cercle: %.2f\n",perimetre);
    printf("L'aire du cercle: %.2f\n", aire);
    return 0;
}