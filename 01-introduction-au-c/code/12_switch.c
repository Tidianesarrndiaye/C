/*
 * 12_switch.c - aiguillage et mini calculatrice
 */
#include <stdio.h>

int main(void) {
    /* Jour de la semaine */
    int jour = 4;
    switch (jour) {
        case 1:  printf("Lundi\n");    break;
        case 2:  printf("Mardi\n");    break;
        case 3:  printf("Mercredi\n"); break;
        case 4:  printf("Jeudi\n");    break;
        case 5:  printf("Vendredi\n"); break;
        case 6:  printf("Samedi\n");   break;
        case 7:  printf("Dimanche\n"); break;
        default: printf("Jour invalide\n");
    }

    /* Fall-through volontaire : regrouper des cas */
    switch (jour) {
        case 6:
        case 7:
            printf("-> Week-end\n");
            break;
        default:
            printf("-> Jour de semaine\n");
    }

    /* Calculatrice */
    double a = 12.0, b = 4.0;
    char op = '/';

    printf("\n%.2f %c %.2f = ", a, op, b);
    switch (op) {
        case '+': printf("%.2f\n", a + b); break;
        case '-': printf("%.2f\n", a - b); break;
        case '*': printf("%.2f\n", a * b); break;
        case '/':
            if (b == 0.0) {
                printf("division par zero impossible\n");
            } else {
                printf("%.2f\n", a / b);
            }
            break;
        default:
            printf("operateur inconnu\n");
    }

    return 0;
}
