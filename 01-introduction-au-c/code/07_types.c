/*
 * 07_types.c - types, tailles et conversions
 */
#include <stdio.h>
#include <limits.h>

int main(void) {
    printf("--- Tailles sur cette machine ---\n");
    printf("char        : %zu octet(s)\n", sizeof(char));
    printf("short       : %zu octet(s)\n", sizeof(short));
    printf("int         : %zu octet(s)\n", sizeof(int));
    printf("long        : %zu octet(s)\n", sizeof(long));
    printf("long long   : %zu octet(s)\n", sizeof(long long));
    printf("float       : %zu octet(s)\n", sizeof(float));
    printf("double      : %zu octet(s)\n", sizeof(double));
    printf("long double : %zu octet(s)\n\n", sizeof(long double));

    printf("--- Limites ---\n");
    printf("INT_MIN  : %d\n", INT_MIN);
    printf("INT_MAX  : %d\n\n", INT_MAX);

    printf("--- char est un entier ---\n");
    char lettre = 'A';
    printf("'%c' vaut %d en ASCII\n", lettre, lettre);
    printf("'A' + 1 donne '%c'\n\n", (char)(lettre + 1));

    printf("--- Division entiere, le piege ---\n");
    int a = 5, b = 2;
    printf("5 / 2 en int          : %d\n", a / b);
    printf("5 / 2 sans cast       : %f\n", (float)(a / b));
    printf("5 / 2 avec cast       : %.2f\n\n", (float) a / b);

    printf("--- Troncature ---\n");
    float x = 9.99f;
    int   y = (int) x;
    printf("(int) 9.99 = %d  (tronque, pas arrondi)\n\n", y);

    printf("--- Debordement ---\n");
    int grand = INT_MAX;
    printf("INT_MAX + 1 = %d\n", grand + 1);

    return 0;
}
