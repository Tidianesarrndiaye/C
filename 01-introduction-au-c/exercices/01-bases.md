# Exercices — chapitres 01 à 10

## Sortie et variables

1. **Carte de visite.** Affiche ton nom, ta ville et ton langage préféré, chacun sur sa ligne,
   alignés avec des tabulations.
2. **Échappements.** Affiche exactement :
   ```
   Il a dit : "Bonjour"
   Chemin : C:\Users\tidia
   Reduction : 50%
   ```
3. **Rectangle.** Déclare une longueur et une largeur, affiche l'aire et le périmètre.
4. **TVA.** Prix HT en `float`, taux de TVA en constante, affiche le prix TTC avec 2 décimales.
5. **Échange.** Deux variables `a = 5` et `b = 10` : échange leurs valeurs (sans pointeurs, avec
   une variable temporaire), puis affiche-les.
6. **Sans variable temporaire.** Refais l'échange avec uniquement des additions/soustractions.

## Types et conversions

7. **Tailles.** Affiche la taille en octets de tous les types de base avec `sizeof`.
8. **ASCII.** Affiche le code ASCII des lettres `A`, `a` et `0`. Déduis-en l'écart entre
   majuscules et minuscules.
9. **Le piège.** Pourquoi `float r = 5 / 2;` affiche-t-il `2.000000` ? Corrige-le de deux façons
   différentes.
10. **Température.** Convertis 37 °C en Fahrenheit (`F = C × 9/5 + 32`). Attention au `9/5`.
11. **Débordement.** Affiche `INT_MAX`, puis `INT_MAX + 1`. Explique le résultat.

## Constantes et opérateurs

12. **Cercle.** `const double PI`, un rayon, affiche l'aire et le périmètre.
13. **Secondes.** L'utilisateur donne un nombre de secondes ; affiche-le en heures, minutes,
    secondes (indice : `/` et `%`).
14. **Pair ou impair.** Sans `if` : affiche `n % 2` puis `n & 1` et compare.
15. **Chiffres.** Pour un nombre à 3 chiffres, affiche séparément les centaines, dizaines et
    unités.

## Booléens

16. **Bissextile.** Une année est bissextile si elle est divisible par 4, sauf si divisible par
    100, sauf si divisible par 400. Stocke le résultat dans un `bool`.
17. **Triangle valide.** Trois longueurs forment un triangle si chaque côté est plus petit que la
    somme des deux autres. Renvoie un `bool`.
18. **Connexion.** Trois `bool` : `est_inscrit`, `a_paye`, `est_banni`. Affiche si l'accès est
    autorisé.

## Pour aller plus loin

19. **Aire d'un trapèze**, avec des constantes nommées et aucun nombre magique.
20. **Facture.** Prix unitaire, quantité, remise en pourcentage, TVA : affiche un récapitulatif
    aligné en colonnes avec `%-15s` et `%8.2f`.
