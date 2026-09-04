# C — instructions pour Claude

## Ce que c'est

Dossier d'apprentissage personnel du langage C (Tidiane), parcours calqué sur le tutoriel C de
W3Schools mais réécrit chapitre par chapitre. Voir `README.md` à la racine pour l'organisation
complète (compilation Linux/WSL vs Windows/MSYS2, cycle `gcc` → exécution) et
`01-introduction-au-c/README.md` pour le sommaire des 33 chapitres.

## Structure

```
C/
├── README.md
├── CLAUDE.md                    ← ce fichier
└── 01-introduction-au-c/
    ├── README.md                ← sommaire des chapitres
    ├── 01-....md … 33-....md    ← un fichier par chapitre, même forme partout
    ├── reader.html               ← lecteur local interactif (voir plus bas)
    ├── code/                    ← exemples .c compilables de chaque chapitre
    ├── exercices/
    └── reference/                ← fiches mots-clés, stdio.h, string.h, math.h...
```

## Convention des chapitres

Chaque `NN-slug.md` suit toujours la même forme, dont dépend le lecteur (`reader.html`) :
- Titre `# NN — Titre du chapitre` en première ligne.
- Corps en Markdown normal (titres `##`/`###`, tableaux, blocs de code C).
- Un bloc de navigation en toute fin de fichier, séparé du corps par une ligne `---` :
  `⬅️ Précédent : [...] · ➡️ Suivant : [...]`.

Si on ajoute un nouveau chapitre : respecter ce format, le numéroter en continuité, mettre à jour
les liens précédent/suivant des chapitres voisins, et ajouter l'exemple `.c` correspondant dans
`code/` si le chapitre en introduit un. Le lecteur, lui, n'a besoin d'aucune mise à jour : il
découvre les fichiers automatiquement.

## Le lecteur interactif (`reader.html`)

Page HTML/CSS/JS autonome (pas de build, pas de dépendance à installer) qui affiche les chapitres
un par un avec navigation Précédent/Suivant, sommaire cliquable et progression de lecture. Elle
détecte les chapitres tout seule en lisant le listing de dossier fourni par un serveur HTTP local
— rien à régénérer quand un chapitre est ajouté ou modifié.

Lancer depuis `01-introduction-au-c/` :

```powershell
python -m http.server 8329
```

puis ouvrir `http://localhost:8329/reader.html`. La progression (chapitres lus, position
courante) est sauvegardée dans le `localStorage` du navigateur, propre à ce chemin de dossier —
pas de fichier de progression à maintenir à la main.

**Port 8329** : volontairement non standard (ni `8000`/`8080`, déjà pris par d'autres projets sur
cette machine). Chaque projet avec un lecteur/serveur local doit avoir son propre port dédié, pour
pouvoir tous tourner en même temps sans conflit — voir `educmathsplateforme` (`8743`) et `reseaux`
(`8461`).

## Idées pour plus tard (pas encore demandées, à proposer)

- **Palette du lecteur** (`reader.html`, partagé avec `lpl/reseaux`) : la version actuelle (papier
  quadrillé, accent rouge, onglets) plaît, mais Tidiane trouve que la toute première version —
  publiée comme Artifact Claude sous
  `https://claude.ai/code/artifact/10c8453a-c2d5-4c54-a1fa-b34c71f6523b` (fond sombre, accent bleu
  cyan `#3fd6ce`, police IBM Plex) — était visuellement plus belle. Objectif pour une prochaine
  session : proposer une piste qui reprend cette identité bleu/sombre plus soignée sans revenir aux
  tics génériques repérés dans le premier jet (labels en petites capitales trackées, barre de
  progression en %).
- **Sidebar repliable sur mobile** : ajouter un bouton hamburger qui cache/affiche le sommaire
  (actuellement les onglets à droite), pour que la lecture soit confortable sur téléphone.
- Ne pas faire ces changements sans que Tidiane le redemande explicitement — il ne veut pas
  superviser cette itération maintenant.

## Ce qu'il ne faut pas faire

- Ne pas renommer les fichiers de chapitre sans mettre à jour les liens `[...]​(NN-....md)` qui les
  référencent depuis les autres chapitres.
- Ne pas casser la première ligne `# NN — Titre` ni le séparateur `---` de fin de fichier : c'est
  ce que `reader.html` parse pour extraire titre et corps.
- Ne pas committer de binaires compilés (`.o`, `.exe`, exécutables sans extension) : déjà couvert
  par `.gitignore`, mais vérifier avant un `git add` si un nouveau nom de binaire apparaît.
