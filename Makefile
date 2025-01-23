CC = gcc
CFLAGS = -std=gnu99 -Wall -pedantic

all: saper

saper: plansza.o main.o gra.o gra_z_pliku.o
	$(CC) $(CFLAGS) -o saper main.o plansza.o gra.o gra_z_pliku.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

plansza.o: plansza.c
	$(CC) $(CFLAGS) -c plansza.c

gra.o: gra.c
	$(CC) $(CFLAGS) -c gra.c

gra_z_pliku.o: gra_z_pliku.c
	$(CC) $(CFLAGS) -c gra_z_pliku.c

clean:
	rm -f saper *.o