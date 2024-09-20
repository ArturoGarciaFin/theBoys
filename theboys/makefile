# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Werror -Wextra -std=c90 -g  # flags de compilacao
LDFLAGS = -lm
ENTREGA = theboys-entrega

CC = gcc

# arquivos-objeto
	objects = theboys.o lef.o fila.o entidades.o eventos.o
     
all: theboys

theboys: theboys.o conjunto.o lef.o fila.o entidades.o eventos.o
	$(CC) -o theboys theboys.o conjunto.o lef.o fila.o entidades.o eventos.o $(LDFLAGS)

lef.o: lef.c
	$(CC) -c $(CFLAGS) lef.c

fila.o: fila.c
	$(CC) -c $(CFLAGS) fila.c

entidades.o: entidades.c 
	$(CC) -c $(CFLAGS) entidades.c

eventos.o: eventos.c
	$(CC) -c $(CFLAGS) eventos.c

theboys.o: theboys.c
	$(CC) -c $(CFLAGS) theboys.c

# arquivo TGZ para entregar
entrega: clean
	mkdir $(ENTREGA)
	cp *.c *.h makefile $(ENTREGA)
	chmod 600 $(ENTREGA)/*
	tar czvf $(ENTREGA).tgz $(ENTREGA)
	rm -rf $(ENTREGA)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

clean:
	rm -f $(objects) theboys

