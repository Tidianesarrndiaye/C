# 01 — Introduction au C

> Équivalent W3Schools : **C Intro**

## Qu'est-ce que le C ?

Le C est un langage de programmation **général**, créé par **Dennis Ritchie** aux Bell Labs entre
1972 et 1973. C'est l'un des langages les plus anciens encore massivement utilisés, et il sert de
base à énormément de choses autour de toi.

- Le noyau **Linux**, Windows et macOS sont écrits en grande partie en C.
- **Python** (l'interpréteur CPython que tu utilises avec Django) est écrit en C.
- Les moteurs JavaScript (V8, celui de Chrome et de Node) sont en C/C++.
- Les bases de données (PostgreSQL, SQLite, MySQL), Git, curl, ffmpeg : du C.

## Pourquoi apprendre le C ?

1. **C'est rapide.** Le code est compilé directement en instructions machine, sans machine
   virtuelle ni interpréteur entre les deux.
2. **Ça t'apprend comment marche l'ordinateur.** Mémoire, pile, tas, adresses, octets : en Python
   tout ça est caché, en C tu le vois.
3. **C'est partout.** Systèmes d'exploitation, drivers, embarqué, jeux vidéo, IoT.
4. **Ça rend les autres langages plus faciles.** C++, C#, Java, Objective-C, PHP, JavaScript, Go,
   Rust : tous ont hérité de la syntaxe du C. Les accolades, le `for (…;…;…)`, le `;` en fin
   d'instruction — tu les connais déjà via JavaScript, ils viennent du C.

## C et C++, quelle différence ?

Le C++ a été créé comme une extension du C : il ajoute la programmation orientée objet (classes,
héritage…). La plus grande partie du code C fonctionne en C++, mais l'inverse est faux. Ici on
fait du **C pur**.

## Ce qui va te changer de Python et de JavaScript

| | Python / JavaScript | C |
|---|---|---|
| Exécution | interprété | **compilé** en binaire |
| Types | dynamiques | **statiques**, déclarés à la main |
| Mémoire | ramasse-miettes automatique | **gérée par toi** (`malloc` / `free`) |
| Chaîne de caractères | type natif | **tableau de caractères** terminé par `\0` |
| Erreur de type | à l'exécution | **à la compilation** (souvent) |
| Dépasser la taille d'un tableau | exception | **comportement indéterminé** (crash… ou pire, silence) |

Cette dernière ligne est la plus importante : en C, le langage ne te protège pas. Il fait
exactement ce que tu as écrit, même quand c'est faux. C'est le prix de la vitesse.

## Prérequis

Rien de particulier, mais ta pratique de JavaScript va beaucoup t'aider pour la syntaxe
(chapitres 03 à 15). Le vrai nouveau territoire commence au chapitre 19 (mémoire).

---
➡️ Chapitre suivant : [02 — Démarrer](02-demarrer.md)
