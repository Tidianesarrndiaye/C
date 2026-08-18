/*
 * 04_output.c - afficher du texte
 */
#include <stdio.h>

int main(void) {
    printf("=== Sortie en C ===\n\n");

    printf("Sans retour a la ligne : ");
    printf("suite immediate\n\n");

    printf("Tabulation :\tvaleur alignee\n");
    printf("Guillemets : \"comme ceci\"\n");
    printf("Barre oblique : \\ \n");
    printf("Pourcentage : 100%%\n\n");

    puts("puts ajoute le retour a la ligne tout seul");

    return 0;
}
