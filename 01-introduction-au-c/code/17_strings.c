/*
 * 17_strings.c - chaines de caracteres
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char mot[] = "Hello";

    printf("Chaine        : %s\n", mot);
    printf("strlen        : %zu caracteres\n", strlen(mot));
    printf("sizeof        : %zu octets (le '\\0' compte)\n", sizeof(mot));
    printf("Premier char  : %c\n", mot[0]);
    printf("Dernier char  : %c\n\n", mot[strlen(mot) - 1]);

    /* Parcours caractere par caractere */
    printf("Lettre par lettre : ");
    for (int i = 0; mot[i] != '\0'; i++) {
        printf("%c ", mot[i]);
    }
    printf("\n\n");

    /* Copie et concatenation */
    char nom_complet[64];
    snprintf(nom_complet, sizeof(nom_complet), "%s", "Tidiane");
    strncat(nom_complet, " Ndiaye", sizeof(nom_complet) - strlen(nom_complet) - 1);
    printf("Nom complet   : %s\n", nom_complet);

    /* Comparaison : jamais avec == */
    char a[] = "Hello";
    char b[] = "Hello";
    const char *pa = a, *pb = b;
    printf("pa == pb      : %d  (compare des adresses, sans interet)\n", pa == pb);
    printf("strcmp(a, b)  : %d  (0 = contenu identique)\n\n", strcmp(a, b));

    /* Transformation */
    char copie[64];
    snprintf(copie, sizeof(copie), "%s", nom_complet);
    for (int i = 0; copie[i] != '\0'; i++) {
        copie[i] = (char) toupper((unsigned char) copie[i]);
    }
    printf("En majuscules : %s\n", copie);

    /* Compter les voyelles */
    int voyelles = 0;
    for (int i = 0; nom_complet[i] != '\0'; i++) {
        char c = (char) tolower((unsigned char) nom_complet[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
            voyelles++;
        }
    }
    printf("Voyelles      : %d\n", voyelles);

    return 0;
}
