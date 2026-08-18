# Makefile des exemples du parcours C — Linux/WSL et Windows
#
#   Linux / WSL, shell MSYS2 :   make
#                                make run FILE=04_output
#                                make clean
#
#   Windows PowerShell / cmd :   mingw32-make
#                                mingw32-make run FILE=04_output
#                                mingw32-make clean
#
#   (sous Windows la commande s'appelle mingw32-make ; pour taper "make",
#    ajoute  Set-Alias make mingw32-make  a ton profil PowerShell)

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c17 -g
# -lm : indispensable sous Linux pour <math.h>, sans effet sous Windows.
LDFLAGS = -lm

# --- Detection du systeme ---------------------------------------------------
# 1. Sous Windows, gcc produit des .exe.
ifeq ($(OS),Windows_NT)
  EXE := .exe
else
  EXE :=
endif

# 2. Quel shell make utilise-t-il ? Sous cmd.exe, "echo $OSTYPE" renvoie la
#    chaine litterale "$OSTYPE" ; sous un shell POSIX il renvoie sa valeur.
ifeq ($(shell echo $$OSTYPE),$$OSTYPE)
  MKDIR_BIN = if not exist bin mkdir bin
  RM_BIN    = if exist bin rmdir /s /q bin
  RM_NOTES  = if exist notes.txt del /q notes.txt
  RUN_PROG  = bin\$(FILE)$(EXE)
else
  MKDIR_BIN = mkdir -p bin
  RM_BIN    = rm -rf bin
  RM_NOTES  = rm -f notes.txt
  RUN_PROG  = ./bin/$(FILE)$(EXE)
endif

SRCS = $(wildcard *.c)
BINS = $(patsubst %.c,bin/%$(EXE),$(SRCS))

all: $(BINS)

bin:
	$(MKDIR_BIN)

bin/%$(EXE): %.c | bin
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

run: bin/$(FILE)$(EXE)
	$(RUN_PROG)

clean:
	$(RM_BIN)
	$(RM_NOTES)

.PHONY: all run clean
