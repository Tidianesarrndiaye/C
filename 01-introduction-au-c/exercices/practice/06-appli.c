#include <stdio.h>

int main() {
    char nom_etudiant = 'A'; // Example character for student name
    float note1 = 85.5; // Example float for student grade
    float note2 = 90.0; // Example float for student grade
    float note3 = 78.0; // Example float for student grade
    float moyenne = (note1 + note2 + note3) / 3; // Calculate average grade
    printf("Moyenne de %c : %.2f\n", nom_etudiant, moyenne);
    return 0;
}