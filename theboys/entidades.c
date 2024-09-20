#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "fila.h"
#include "lef.h"
#include "conjunto.h"


int aleat (int min, int max)
{
    return (rand() % ((max + 1) - min) + min);
}


struct base cria_base (int id, int x, int y)
{
	struct base b;

	b.id = id;
	b.lotacao = aleat (3, 10);
	b.presentes = cria_cjt (b.lotacao);
	b.espera = fila_cria ();
	b.local.x = x;
	b.local.y = y;

	return b;
}


struct conjunto *cria_hab (int numHab)
{
	struct conjunto *hab;
	int elemento, i;

	hab = cria_cjt (numHab);

	for (i = 0; i <= numHab - 1; i++)
	{
		elemento = aleat (1, NHABILIDADES);
		insere_cjt (hab, elemento);
	}

	return hab;
}


struct heroi cria_heroi (int id)
{
	struct heroi h;

	int numHab = aleat (1, 3);

	h.id = id;
	h.habilidades = cria_hab (numHab);
	h.paciencia = aleat (1, 100);
	h.velocidade = aleat (50, 5000);
	h.experiencia = 0;
	h.base = -1;

	return h;
}

struct missao cria_missao (int id, int x, int y)
{
	struct missao m;

	int elemento;
	int numHab = aleat (6, 10);

	m.id = id;
	m.local.x = x;
	m.local.y = y;
	m.habilidades = cria_cjt (numHab);

	while (cardinalidade_cjt (m.habilidades) < numHab)
	{
		elemento = aleat (1, NHABILIDADES);
		insere_cjt (m.habilidades, elemento);
	}

	return m;
}

void imprime_heroi (struct heroi h)
{
	printf ("id do heroi: %d\n", h.id);
	printf ("paciencia do heroi: %d\n", h.paciencia);
	printf ("velocidade do heroi: %d\n", h.velocidade);
	printf ("experiencia do heroi: %d\n", h.experiencia);
	printf ("base do heroi: %d\n", h.base);
	printf ("habilidades do heroi: ");
	imprime_cjt (h.habilidades);
}

void imprime_base (struct base b)
{
	printf ("id da base: %d\n", b.id);
	printf ("lotacao da base: %d\n", b.lotacao);
	printf ("x da base: %d\n", b.local.x);
	printf ("y da base: %d\n", b.local.y);
	printf ("presentes na base: ");
	imprime_cjt (b.presentes);
}

void imprime_missao (struct missao m)
{
	printf ("id da missao: %d\n", m.id);
	printf ("x da missao: %d\n", m.local.x);
	printf ("y da missao: %d\n", m.local.y);
	printf ("habilidades da missao: ");
	imprime_cjt (m.habilidades);
}