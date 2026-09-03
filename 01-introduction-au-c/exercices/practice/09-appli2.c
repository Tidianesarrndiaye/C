/* 09-appli2.c Test d'utilisation des operations sur les bits
Auteur Cheikh Tidiane
Date: 20-08-2026
*/

#define LECTURE  1   // 0001
#define ECRITURE 2   // 0010
#define EXEC     4   // 0100

#include <stdio.h>

int main() {
    int droits = LECTURE | ECRITURE;        // 0011
    if (droits & ECRITURE) printf("Ecriture autorisee\n");

}
