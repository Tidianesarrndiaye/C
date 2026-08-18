/*
 * 11_if_else.c - conditions
 */
#include <stdio.h>

int main(void) {
    float note = 14.5f;

    printf("Note : %.1f/20 -> ", note);

    if (note < 0.0f || note > 20.0f) {
        printf("Note invalide\n");
    } else if (note >= 16.0f) {
        printf("Tres bien\n");
    } else if (note >= 14.0f) {
        printf("Bien\n");
    } else if (note >= 12.0f) {
        printf("Assez bien\n");
    } else if (note >= 10.0f) {
        printf("Passable\n");
    } else {
        printf("Insuffisant\n");
    }

    /* Forme abregee : l'operateur ternaire */
    int age = 20;
    printf("A %d ans : %s\n", age, (age >= 18) ? "majeur" : "mineur");

    /* Conditions combinees */
    int a_permis = 1;
    if (age >= 18 && a_permis) {
        printf("Peut conduire\n");
    } else {
        printf("Ne peut pas conduire\n");
    }

    return 0;
}
