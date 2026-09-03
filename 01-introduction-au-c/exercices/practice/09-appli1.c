/* 09-appli1.c Teste les pre et pos incrementation
Auteur Cheikh Tidiane
Date: 20-08-2026
*/


#include <stdio.h>

int main() {
    int x = 5;
    printf("%d\n", x++);   // affiche 5, PUIS x devient 6   (post)
    printf("%d\n", x);     // 6

    int y = 5;
    printf("%d\n", ++y);   // y devient 6, PUIS affiche 6   (pre)

}
