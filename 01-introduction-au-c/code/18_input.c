/*
 * 18_input.c - saisie utilisateur robuste
 *
 * Test sans taper :  printf "Tidiane\n25\n" | ./18_input
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    char nom[50];
    char ligne[64];
    int  age;

    printf("Ton nom : ");
    if (fgets(nom, sizeof(nom), stdin) == NULL) {
        fprintf(stderr, "Lecture interrompue.\n");
        return 1;
    }
    nom[strcspn(nom, "\n")] = '\0';   /* enleve le retour a la ligne */

    printf("Ton age : ");
    if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
        fprintf(stderr, "Lecture interrompue.\n");
        return 1;
    }
    if (sscanf(ligne, "%d", &age) != 1) {
        fprintf(stderr, "Age invalide.\n");
        return 1;
    }

    printf("\nBonjour %s, tu auras %d ans l'an prochain.\n", nom, age + 1);
    return 0;
}
