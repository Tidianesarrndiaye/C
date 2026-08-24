#include <stdio.h>

int main() {
    const float TVA = 0.18;
    float prix_ht = 4600; // prix en Dirhams marocain
    float prix_ttc = prix_ttc + prix_ht * TVA;
    printf("Le prix hors taxe: %.2f\n",prix_ht);
    printf("Le prix TTC: %.2f\n",prix_ttc);
    return 0;
}