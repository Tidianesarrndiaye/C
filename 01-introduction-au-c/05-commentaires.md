# 05 — Les commentaires

> Équivalent W3Schools : **C Comments**

Les commentaires servent à expliquer le code et à désactiver temporairement des lignes. Le
compilateur les ignore complètement.

## Commentaire sur une ligne — `//`

Tout ce qui suit `//` jusqu'à la fin de la ligne est ignoré :

```c
// Ceci est un commentaire
printf("Hello World!\n");

printf("Hello World!\n");  // celui-ci est en fin de ligne
```

## Commentaire sur plusieurs lignes — `/* */`

Tout ce qui se trouve entre `/*` et `*/` est ignoré, y compris sur plusieurs lignes :

```c
/* Ce programme calcule la moyenne
   des notes saisies par l'utilisateur
   et l'affiche avec deux décimales. */
printf("Hello World!\n");
```

On l'utilise aussi au milieu d'une ligne, même si c'est rare :

```c
int x = 5 /* la largeur */ * 3 /* la hauteur */;
```

## Désactiver du code

C'est l'usage le plus fréquent pendant le débogage :

```c
printf("Version A\n");
// printf("Version B\n");   ← désactivée
```

Dans VS Code : `Ctrl + :` (ou `Ctrl + /` selon le clavier) commente/décommente la sélection.

## Pièges

Les commentaires `/* */` **ne s'imbriquent pas** :

```c
/* début
   /* imbriqué */   ← le commentaire se termine ICI
   cette ligne provoque une erreur
*/
```

Pour désactiver un gros bloc qui contient déjà des `/* */`, utilise plutôt le préprocesseur :

```c
#if 0
    tout ce bloc est ignoré,
    même s'il contient /* des commentaires */
#endif
```

## Bien commenter

Le bon commentaire explique **pourquoi**, pas **quoi**. Le code dit déjà quoi.

```c
i++;                              // ❌ incrémente i — inutile, on le voit

// On saute l'en-tete CSV avant de parser les donnees
i++;                              // ✅ explique l'intention
```

## Convention : l'en-tête de fichier

Beaucoup de projets C commencent chaque fichier par un bloc de ce genre :

```c
/*
 * moyenne.c — calcule la moyenne d'une serie de notes
 *
 * Auteur : Tidiane
 * Date   : 2026-08-18
 * Compil.: gcc -Wall -Wextra -std=c17 moyenne.c -o moyenne
 */
```

## Accents dans les commentaires et les chaînes

Les accents fonctionnent en UTF-8 avec un terminal moderne, mais peuvent s'afficher bizarrement
sous Windows (`cmd.exe`) ou dans certains environnements. Beaucoup de codeurs C écrivent donc
leurs commentaires et leurs `printf` **sans accents** par sécurité. C'est ce qui est fait dans les
fichiers `code/` de ce parcours.

## Exercice

Reprends ton programme du chapitre 04, ajoute un en-tête de fichier commenté, puis commente une
des lignes `printf` et vérifie qu'elle disparaît de la sortie après recompilation.

---
⬅️ [04 — Afficher du texte](04-sortie-output.md) | ➡️ [06 — Variables](06-variables.md)
