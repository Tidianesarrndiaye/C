/*
 * 29_enums.c - enum, typedef, switch exhaustif, drapeaux binaires
 */
#include <stdio.h>

typedef enum { EN_ATTENTE, VALIDE, REFUSE } Statut;

typedef enum {
    LECTURE  = 1,   // 0001
    ECRITURE = 2,   // 0010
    EXEC     = 4    // 0100
} Permission;

const char *nom_statut(Statut s) {
    switch (s) {
        case EN_ATTENTE: return "En attente";
        case VALIDE:     return "Valide";
        case REFUSE:     return "Refuse";
        default:         return "Inconnu";
    }
}

int main(void) {
    /* Valeurs par defaut : 0, 1, 2... */
    Statut s = VALIDE;
    printf("Statut brut : %d -> %s\n", s, nom_statut(s));

    /* Enum et switch exhaustif */
    for (Statut i = EN_ATTENTE; i <= REFUSE; i++) {
        printf("  %d : %s\n", i, nom_statut(i));
    }

    /* Drapeaux binaires : combiner plusieurs valeurs dans un seul entier */
    int droits = LECTURE | ECRITURE;
    printf("\nDroits = %d\n", droits);
    printf("  Lecture  : %s\n", (droits & LECTURE)  ? "oui" : "non");
    printf("  Ecriture : %s\n", (droits & ECRITURE) ? "oui" : "non");
    printf("  Exec     : %s\n", (droits & EXEC)     ? "oui" : "non");

    droits &= ~ECRITURE;   /* retire un drapeau */
    printf("Apres retrait de ECRITURE, droits = %d\n", droits);

    return 0;
}
