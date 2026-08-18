# Exercices — chapitres 11 à 15

## Conditions

1. **Le plus grand.** Deux nombres : affiche le plus grand, ou « égaux ».
2. **Trois nombres.** Le plus grand des trois, sans utiliser de fonction.
3. **État de l'eau.** Selon une température : glace (≤ 0), liquide, vapeur (≥ 100).
4. **Mention.** Une note sur 20 → Très bien / Bien / Assez bien / Passable / Insuffisant, avec
   contrôle de validité (0 à 20).
5. **Catégorie sportive.** Selon l'âge : poussin (< 8), pupille (< 10), minime (< 12),
   cadet (< 14), junior (< 18), senior.
6. **Trouve le bug.**
   ```c
   int code = 0;
   if (code = 1) { printf("acces autorise\n"); }
   ```

## switch

7. **Menu.** `choix` de 1 à 4 → Ajouter / Supprimer / Lister / Quitter, avec `default`.
8. **Calculatrice.** Deux nombres et un opérateur (`+ - * / %`), traités par un `switch`. Gère la
   division par zéro.
9. **Jours du mois.** Un numéro de mois → son nombre de jours (regroupe les cas avec le
   fall-through).
10. **Voyelle ou consonne.** Un caractère → dis lequel des deux (attention aux majuscules).

## Boucles

11. **Compte à rebours** de 10 à 0, puis « Décollage ! ».
12. **Table de multiplication** d'un nombre donné, alignée avec `%3d`.
13. **Somme** des entiers de 1 à 100. Vérifie avec la formule `n(n+1)/2`.
14. **Factorielle** de 10 (attention au type : `int` déborde vite).
15. **Nombres pairs** de 0 à 50, dix par ligne.
16. **Somme des chiffres** d'un nombre (1234 → 10).
17. **Inverser un nombre** (1234 → 4321).
18. **Palindrome numérique** : 12321 en est un, 12345 non.
19. **Nombre premier** : teste si un nombre l'est.
20. **Tous les premiers** inférieurs à 100.
21. **Fibonacci** : affiche les 20 premiers termes.
22. **PGCD** de deux nombres par l'algorithme d'Euclide.
23. **Table de conversion** °C → °F de 0 à 100 par pas de 10.

## Boucles imbriquées

24. **Triangle** de `*` de 5 lignes, puis inversé, puis centré (pyramide).
25. **Table de Pythagore** 9 × 9 avec en-têtes de ligne et de colonne.
26. **Damier** 8 × 8 alternant `#` et `.`.

## break et continue

27. **Premier multiple** de 7 et de 3 entre 1 et 100 : arrête-toi dès que tu le trouves.
28. **FizzBuzz** de 1 à 100.
29. **Somme jusqu'à 0.** L'utilisateur saisit des nombres ; la somme s'affiche quand il tape 0.
30. **Trouve le bug.**
    ```c
    int n = 0;
    while (n < 5) {
        if (n % 2 == 0) continue;
        printf("%d\n", n);
        n++;
    }
    ```
