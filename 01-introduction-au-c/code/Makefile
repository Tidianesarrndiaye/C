# Makefile des exemples du parcours C
#
#   make                 compile tous les exemples dans bin/
#   make run FILE=04_output   compile et lance un exemple
#   make clean           supprime bin/ et les fichiers generes

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c17 -g
LDFLAGS = -lm

SRCS = $(wildcard *.c)
BINS = $(patsubst %.c,bin/%,$(SRCS))

all: $(BINS)

bin:
	mkdir -p bin

bin/%: %.c | bin
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

run: bin/$(FILE)
	./bin/$(FILE)

clean:
	rm -rf bin notes.txt

.PHONY: all run clean
