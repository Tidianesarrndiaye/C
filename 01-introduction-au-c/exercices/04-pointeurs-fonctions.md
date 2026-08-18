# Exercices — chapitres 19 à 26

## Adresses et pointeurs

1. **Observation.** Affiche la valeur, l'adresse et la taille de trois variables de types
   différents.
2. **Contiguïté.** Affiche l'adresse de chaque case d'un `int[5]` puis d'un `char[5]`. Explique
   l'écart entre deux adresses successives.
3. **Aller-retour.** Déclare une variable, un pointeur vers elle ; modifie la variable par le
   pointeur, puis le pointeur par la variable.
4. **Échange.** `void echanger(int *a, int *b)`.
5. **Parcours.** Parcours un tableau uniquement avec un pointeur, sans jamais utiliser `[]`.
6. **`strlen` maison** en n'utilisant qu'un `char *`.
7. **Pointeur NULL.** Écris un programme qui plante en déréférençant `NULL`, puis corrige-le avec
   un test.

## Fonctions

8. **Carré.** `int carre(int n)` — affiche les carrés de 1 à 10.
9. **Max.** `int max2(int, int)` puis `int max3(int, int, int)` qui réutilise le premier.
10. **Ligne.** `void afficher_ligne(char c, int n)` qui affiche `n` fois le caractère `c`.
11. **Premier.** `bool est_premier(int n)`.
12. **Conversion.** `float celsius_vers_fahrenheit(float c)` et la réciproque.
13. **Statistiques.** `void statistiques(const int tab[], int n, float *moyenne, int *min, int *max)`.
14. **Tri.** `void trier(int tab[], int n)` — le tableau est modifié sur place.
15. **Découpage.** Reprends un de tes anciens programmes et découpe-le en `module.h`,
    `module.c`, `main.c`. Écris le `Makefile`.

## Portée

16. **Compteur.** Une fonction avec une variable `static` qui compte ses propres appels.
17. **Globale vs paramètre.** Écris un programme avec une globale partagée, puis le même sans
    globale. Compare la lisibilité.
18. **Non initialisé.** Que vaut une variable locale non initialisée ? Une globale ? Vérifie.

## Récursivité

19. **Factorielle** en récursif et en itératif.
20. **Fibonacci** récursif ; mesure `fibonacci(35)` avec `time`, compare à la version itérative.
21. **PGCD** récursif (Euclide).
22. **Compter les chiffres** d'un nombre, récursivement.
23. **Puissance** `x^n` récursive.
24. **Somme d'un tableau** récursive.
25. **Tours de Hanoï** pour 3 puis 5 disques ; compte les déplacements.

## Mathématiques

26. **Second degré.** Résous `ax² + bx + c = 0`, en traitant le discriminant négatif.
27. **Distance** entre deux points, avec `sqrt` et avec `hypot`.
28. **Intérêts composés** sur 10 ans.
29. **Nombre mystère.** Le programme tire un nombre entre 1 et 100, l'utilisateur devine, le
    programme répond « plus grand » / « plus petit » et compte les essais.
30. **Précision.** Affiche `0.1 + 0.2` avec `%.20f` et explique pourquoi `== 0.3` est faux.
