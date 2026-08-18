/*
 * 27_fichiers.c - ecrire, lire et completer un fichier
 */
#include <stdio.h>
#include <string.h>

#define FICHIER "notes.txt"

int main(void) {
    /* --- Ecriture (ecrase le fichier s'il existe) --- */
    FILE *f = fopen(FICHIER, "w");
    if (f == NULL) {
        perror("fopen (ecriture)");
        return 1;
    }
    fprintf(f, "Tidiane;15.5\n");
    fprintf(f, "Awa;17.0\n");
    fputs("Moussa;12.5\n", f);
    fclose(f);
    printf("Fichier %s ecrit.\n\n", FICHIER);

    /* --- Ajout a la fin --- */
    f = fopen(FICHIER, "a");
    if (f == NULL) {
        perror("fopen (ajout)");
        return 1;
    }
    fprintf(f, "Fatou;19.0\n");
    fclose(f);

    /* --- Lecture ligne par ligne --- */
    f = fopen(FICHIER, "r");
    if (f == NULL) {
        perror("fopen (lecture)");
        return 1;
    }

    char ligne[256];
    int  nb = 0;
    float total = 0.0f;

    printf("Contenu :\n");
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        ligne[strcspn(ligne, "\n")] = '\0';

        char  nom[64];
        float note;
        if (sscanf(ligne, "%63[^;];%f", nom, &note) == 2) {
            printf("  %-10s %5.1f\n", nom, note);
            total += note;
            nb++;
        }
    }
    fclose(f);

    if (nb > 0) {
        printf("\nMoyenne de la classe (%d eleves) : %.2f\n", nb, total / (float) nb);
    }

    return 0;
}
