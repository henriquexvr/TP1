CC = gcc
CFLAGS = -O3 -march=native -msse -Wall -Wextra

SRC = src/main.c src/csvReader.c src/normalizeBaseline.c src/normalizeQuake.c src/normalizeSse.c

all:
	$(CC) $(CFLAGS) -o normalize $(SRC) -lm

clean:
	rm -f normalize