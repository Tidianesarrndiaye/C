#!/usr/bin/env python3
"""
C -- serveur local commun a tous les modules de cours.

Sert tout le depot comme `python -m http.server`, mais ecoute explicitement sur
0.0.0.0 (IPv4) au lieu de l'adresse IPv6 par defaut (::) : les liens affiches au
demarrage fonctionnent alors tels quels, colles-copies dans le navigateur ou
cliquables dans un terminal qui detecte les liens.

Il y a un seul reader.html, a la racine du depot, partage par tous les modules
(dossiers avec des chapitres numerotes NN-slug.md, ex. 01-introduction-au-c/) :
c'est lui qui choisit le module a afficher (voir sa propre logique de decouverte).
Au demarrage, ce script decouvre les memes modules et affiche un lien direct par
module trouve -- un futur module (02-..., 03-...) est ainsi detecte sans toucher
a ce script.

Usage, depuis la racine du depot :
    uv run python outils/serveur.py
    # ou, avec un autre port :
    uv run python outils/serveur.py --port 8330
"""
import argparse
import datetime
import http.server
import os
import re
import socketserver
import sys

PORT = 8329
REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))

# Sur certains terminaux Windows, la sortie standard n'est pas en UTF-8 (encodage
# cp1252 de la console) : l'emoji utilise plus bas plante alors le demarrage avec
# un UnicodeEncodeError. On force l'UTF-8 quand c'est possible, comme le fait deja
# le serveur d'educmathsplateforme pour la meme raison.
for _stream in (sys.stdout, sys.stderr):
    if hasattr(_stream, "reconfigure"):
        try:
            _stream.reconfigure(encoding="utf-8", errors="replace", line_buffering=True)
        except Exception:
            pass


def log(message):
    timestamp = datetime.datetime.now().strftime("%H:%M:%S")
    print(f"[{timestamp}] {message}", flush=True)


class Handler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=REPO_ROOT, **kwargs)

    def log_message(self, fmt, *args):
        log(f"{self.address_string()} - {fmt % args}")


class ThreadingHTTPServer(socketserver.ThreadingMixIn, http.server.HTTPServer):
    daemon_threads = True
    allow_reuse_address = True


_CHAPTER_RE = re.compile(r"^\d+-.+\.md$", re.IGNORECASE)


def find_modules():
    """Modules de cours : dossiers a la racine du depot contenant au moins un
    chapitre numerote (NN-slug.md), la meme regle que reader.html utilise pour
    se decouvrir tout seul un module."""
    modules = []
    for name in sorted(os.listdir(REPO_ROOT)):
        if name.startswith("."):
            continue
        full = os.path.join(REPO_ROOT, name)
        if not os.path.isdir(full):
            continue
        if any(_CHAPTER_RE.match(f) for f in os.listdir(full)):
            modules.append(name)
    return modules


def main():
    parser = argparse.ArgumentParser(description="C -- serveur local commun aux lecteurs interactifs.")
    parser.add_argument("--port", "-p", type=int, default=PORT, help=f"Port d'ecoute HTTP (defaut : {PORT})")
    args = parser.parse_args()

    server = ThreadingHTTPServer(("0.0.0.0", args.port), Handler)
    log(f"C -- serveur demarre sur http://localhost:{args.port}/ (ecoute 0.0.0.0:{args.port})")

    modules = find_modules()
    print(flush=True)
    if not modules:
        print(f"\U0001F449 Ouvre http://localhost:{args.port}/ dans ton navigateur", flush=True)
    elif len(modules) == 1:
        print(f"\U0001F449 Ouvre http://localhost:{args.port}/reader.html dans ton navigateur", flush=True)
    else:
        for name in modules:
            print(f"\U0001F449 Ouvre http://localhost:{args.port}/reader.html?m={name} dans ton navigateur", flush=True)
    print("   (Ctrl+C pour arreter)\n", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        log("Arret du serveur.")
        server.shutdown()
    return 0


if __name__ == "__main__":
    sys.exit(main())
