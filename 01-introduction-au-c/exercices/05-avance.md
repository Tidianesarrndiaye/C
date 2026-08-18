# Exercices — chapitres 27 à 32

## Fichiers

1. **Écriture.** Crée `journal.txt` et écris-y 5 lignes.
2. **Lecture numérotée.** Relis le fichier et affiche chaque ligne précédée de son numéro.
3. **Mini `wc`.** Compte les lignes, les mots et les caractères d'un fichier passé en argument.
4. **Copie.** Copie un fichier vers un autre, caractère par caractère, puis par blocs (`fread`).
5. **CSV.** Lis un fichier `nom;note` et affiche la moyenne de la classe.
6. **Ajout.** Ajoute une ligne horodatée à un fichier de log à chaque exécution.
7. **Recherche.** Affiche toutes les lignes d'un fichier contenant un mot donné (un mini `grep`).
8. **Robustesse.** Que fait ton programme si le fichier n'existe pas ? Affiche un message clair
   avec `perror`.

## Structures

9. **Livre.** Structure `Livre` (titre, auteur, année, prix) ; affiche une bibliothèque de 3 livres.
10. **Augmentation.** `void augmenter_prix(Livre *l, float pourcentage)`.
11. **Point.** `Point {x, y}` et `double distance(const Point *a, const Point *b)`.
12. **Tri de structures.** Trie un tableau d'`Etudiant` par moyenne décroissante.
13. **Imbrication.** `Personne` contenant une `Date` de naissance ; affiche `JJ/MM/AAAA`.
14. **Rectangle.** `Rectangle` composé de deux `Point` ; calcule son aire et son périmètre.

## Enums

15. **Saison.** Un enum `Saison` et une fonction qui donne la saison d'un mois.
16. **Statut.** `Statut { EN_ATTENTE, VALIDE, REFUSE }` et un message par cas via `switch`.
17. **Tâche.** Combine une structure `Tache` (titre, `Statut`) et affiche une liste de tâches.
18. **Permissions.** Un enum de drapeaux binaires (lecture/écriture/exécution) ; ajoute, retire et
    teste des droits.

## Mémoire dynamique

19. **Tableau dynamique.** L'utilisateur choisit la taille ; remplis, affiche, libère. Vérifie
    avec Valgrind qu'il n'y a **aucune fuite**.
20. **`strdup` maison.**
21. **Croissance.** Un tableau qui double de capacité quand il est plein (`realloc`).
22. **Matrice dynamique** `n × m`, remplie, affichée, entièrement libérée.
23. **Fuite volontaire.** Introduis une fuite, retrouve-la avec Valgrind, corrige-la.
24. **Liste chaînée.** Insertion en tête et en queue, suppression, recherche, affichage,
    libération complète. Zéro fuite sous Valgrind.

## Erreurs et débogage

25. **Cinq erreurs.** Écris un programme avec 5 erreurs de syntaxe, corrige-les une par une en
    lisant gcc.
26. **Segfault.** Provoque un `Segmentation fault`, retrouve la ligne avec `gdb` et `backtrace`.
27. **Division sûre.** `int diviser(int a, int b, int *resultat)` qui renvoie un code d'erreur.
28. **Sanitizer.** Fais tourner un de tes programmes avec `-fsanitize=address,undefined`.
29. **Assertions.** Ajoute des `assert` sur les préconditions d'une de tes fonctions.

## Date et heure

30. **Date du jour** au format `Mardi 18 août 2026, 09h15`.
31. **Jours restants** jusqu'à une date future.
32. **Âge en jours** à partir de ta date de naissance.
33. **Chronomètre.** Mesure la durée d'une boucle qui compte jusqu'à un milliard, avec `clock()`
    puis avec la commande `time`.
