#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "conjunto.h"
#include "fila.h"
#include "lef.h"
#include "entidades.h"
#include "eventos.h"

/*
ID EVENTOS:
CHEGA = 0
ESPERA = 1
DESISTE = 2
AVISA = 3
ENTRA = 4
SAI = 5
VIAJA = 6
MISSAO = 7
FIM = 8
*/

double dis_euclidiana (struct coordenadas c1, struct coordenadas c2)
{
	int dx, dy;

	dx = c2.x - c1.x;
	dy = c2.y - c1.y;

	return sqrt(dx * dx + dy * dy);
}

void big_bang (struct mundo *w, struct lef_t *lef)
{
	int base, tempo;
    struct evento_t *e;
    int i, x, y;

    w->nHerois = NHEROIS;
    w->nBases = NBASES;
    w->habilidades = NHABILIDADES;
    w->nMissoes = NMISSOES;
    w->tamanhoMundo[0] = 0;
    w->tamanhoMundo[1] = TAMMUNDO;
    w->tamanhoMundo[2] = 0;
    w->tamanhoMundo[3] = TAMMUNDO;
    w->relogio = TFIM;

    for (i = 0; i <= NMISSOES - 1; i++)
    {
    	tempo = aleat (0, TFIM);
    	x = aleat (1, TAMMUNDO);
    	y = aleat (1, TAMMUNDO);
    	w->vMis[i] = cria_missao (i, x, y);
    	e = cria_evento (tempo, 7, i, -1);
    	insere_lef (lef, e);
    }

    for (i = 0; i <= NBASES -1; i++)
    {
        x = aleat (1, TAMMUNDO);
        y = aleat (1, TAMMUNDO);
        w->vBas[i] = cria_base (i, x, y);
    }

    for (i = 0; i <= NHEROIS - 1; i++)
    {
        tempo = aleat (1, 4320);
        base = aleat (0, NBASES - 1);
        w->vHer[i] = cria_heroi (i);
        e = cria_evento (tempo, 0, w->vHer[i].id, w->vBas[base].id);
        insere_lef (lef, e);
    }

    e = cria_evento (TFIM, 8, -1, -1);
    insere_lef (lef, e);
}

void chega (int tempo, struct heroi h, struct base b, struct mundo *w,
			struct lef_t *lef)
{
	w->vHer[h.id].base = b.id;

	int espera;
	int presentes = cardinalidade_cjt (b.presentes);

	if (presentes < b.lotacao && fila_vazia (b.espera))
	{
		espera = 1;
	}
	else
	{
		espera = (h.paciencia) > (10 * fila_tamanho (b.espera));
	}

	if (espera)
	{
		printf ("%d: CHEGA HEROI %d BASE %d (%d/%d) ESPERA\n",
			tempo, h.id, b.id, presentes, b.lotacao);

		struct evento_t *e;
		e = cria_evento (tempo, 1, h.id, b.id);
		insere_lef (lef, e);

		return;
	}
	else
	{
		printf ("%d: CHEGA HEROI %d BASE %d (%d/%d) DESISTE\n",
			tempo, h.id, b.id, presentes, b.lotacao);

		struct evento_t *e;
		e = cria_evento (tempo, 2, h.id, b.id);
		insere_lef (lef, e);

		return;
	}
}


void espera (int tempo, struct heroi h, struct base b, struct mundo *w,
				struct lef_t *lef)
{
	printf ("%d: ESPERA HEROI %d BASE %d (%d)\n",
			tempo, w->vHer[h.id].id, b.id, fila_tamanho(b.espera));

	struct evento_t *e;

	insere_cjt (b.presentes, h.id);

	enqueue (b.espera, h.id);
	
	e = cria_evento (tempo, 3, -1, b.id);
	insere_lef (lef, e);

	return;
}

void desiste (int tempo, struct heroi h, struct base b, struct mundo *w,
				struct lef_t *lef)
{
	printf ("%d: DESISTE HEROI %d BASE %d\n", tempo, w->vHer[h.id].id, b.id);

	struct evento_t *e;
	int bdes = aleat (0, NBASES - 1);

	e = cria_evento (tempo, 6, h.id, bdes);
	insere_lef (lef, e);

	return;
}

void avisa (int tempo, struct base b, struct mundo *w, struct lef_t *lef)
{
	printf ("%d: AVISA PORTEIRO BASE %d (%d/%d) FILA ",
		tempo, w->vBas[b.id].id, cardinalidade_cjt (b.presentes), b.lotacao);
	fila_imprime (b.espera);

	int presentes = cardinalidade_cjt(b.presentes);
	int id;

	while (presentes <= b.lotacao && (b.espera->tamanho != 0))
	{
		dequeue (b.espera, &id);
		printf ("%d: AVISA PORTEIRO BASE %d ADMITE %d\n", tempo, b.id, id);
		insere_cjt (b.presentes, id);
		struct evento_t *e;
		e = cria_evento (tempo, 4, id, b.id);
		insere_lef (lef, e);
	}

	return;
}


void entra (int tempo, struct heroi h, struct base b, struct mundo *w,
			struct lef_t *lef)
{
	int tpb = 15 + w->vHer[h.id].paciencia * aleat (1, 20);

	struct evento_t *e;
	e = cria_evento (tempo + tpb, 5, h.id, b.id);
	insere_lef (lef, e);

	printf ("%d: ENTRA HEROI %d BASE %d (%d/%d) SAI %d\n",
		tempo, h.id, b.id, cardinalidade_cjt(b.presentes), b.lotacao, tpb);

	return;
}


void sai (int tempo, struct heroi h, struct base b, struct mundo *w,
			struct lef_t *lef)
{
	int bdes;
	retira_cjt (b.presentes, h.id);
	bdes = aleat (1, NBASES - 1);
	struct evento_t *e1, *e2;
	e1 = cria_evento (tempo, 6, h.id, bdes);
	insere_lef (lef, e1);
	e2 = cria_evento (tempo, 3, -1, b.id);
	insere_lef (lef, e2);

	printf ("%d: SAI HEROI %d BASE %d (%d/%d)\n", tempo, h.id, b.id,
					cardinalidade_cjt(b.presentes), w->vBas[b.id].lotacao);

	return;
}

void viaja (int tempo, struct heroi h, struct base b, struct mundo *w,
			struct lef_t *lef)
{
	struct base b_at;
	double distancia;
	int duracao, distancia_int;
	struct evento_t *e;

	b_at = w->vBas[h.base];

	distancia = dis_euclidiana (b_at.local, b.local);

	distancia_int = (int)distancia;

	duracao = distancia_int / h.velocidade;

	e = cria_evento (tempo + duracao, 0, h.id, b.id);
	insere_lef (lef, e);

	printf ("%d: VIAJA HEROI %d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
	tempo, h.id, b_at.id, b.id, distancia_int, h.velocidade,tempo + duracao);

	return;
}


int missao (int tempo, struct missao m, struct mundo *w, struct lef_t *lef)
{
	int i, j, menor, valido, heroi, id_hab;
	double dis_double;
	struct time aux, vTime[NBASES];
	struct conjunto *hab, *hab_heroi;
	struct base b_aux;
	struct evento_t *e;

	for (i = 0; i <= NBASES - 1; i++)
	{
		vTime[i].id_bas = i;

		dis_double = dis_euclidiana (m.local, w->vBas[i].local);

		vTime[i].dis = (int)dis_double;
	}

	for (i = 0; i < NBASES; i++)
	{
		menor = i;

		for (j = i + 1; j <= NBASES - 1; j++)
		{
			if (vTime[j].dis < vTime[menor].dis)
				menor = j;
		}

		aux = vTime[i];
		vTime[i] = vTime[menor];
		vTime[menor] = aux;
	}

	hab = cria_cjt (NHABILIDADES);

	i = 0;
	valido = 0;

	while (i <= NBASES - 1 && !valido)
	{
		printf ("%d: MISSAO %d TENT %d HAB REQ: ", tempo, m.id, i + 1);
		w->vMis[i].tentativas = 1;
		w->vMis[i].tentativas++;
		imprime_cjt (m.habilidades);

		while (!vazio_cjt (hab))
			retira_um_elemento_cjt (hab);

		b_aux = w->vBas[vTime[i].id_bas];

		printf ("%d: MISSAO %d BASE %d DIST %d HEROIS: ", tempo,
										m.id, i, vTime[i].dis);
		imprime_cjt (b_aux.presentes);

		inicia_iterador_cjt (b_aux.presentes);
		j = 0;

		while (j < cardinalidade_cjt (b_aux.presentes))
		{
			incrementa_iterador_cjt (b_aux.presentes, &heroi);
			hab_heroi = w->vHer[heroi].habilidades;
			inicia_iterador_cjt (hab_heroi);

			printf ("%d: MISSAO %d HAB HEROI %d: ", tempo, m.id, heroi);
			imprime_cjt (hab_heroi);

			while (incrementa_iterador_cjt (hab_heroi, &id_hab))
			{
				insere_cjt (hab, id_hab);
			}

			j++;
		}

		printf ("%d: MISSAO %d UNIAO HAB BASE %d: ", tempo, m.id, i);
		imprime_cjt (hab);

		if (contido_cjt (m.habilidades, hab))
		{
			valido = 1;
			break;
		}

		i++;
	}

	destroi_cjt (hab);

	if (!valido)
	{
		e = cria_evento (tempo + 24 * 60, 7, m.id, -1);
		insere_lef (lef, e);
		printf ("%d: MISSAO %d IMPOSSIVEL\n", tempo, m.id);

		return 0;
	}

	inicia_iterador_cjt (w->vBas[i].presentes);

	while (incrementa_iterador_cjt (w->vBas[i].presentes, &heroi))
	{
		(w->vHer[heroi].experiencia)++;
	}

	printf ("%d: MISSAO %d CUMPRIDA BASE %d\n", tempo, m.id, i);

	return 1;
}

void meteoro (struct mundo *w)
{
	int i;

	for (i = 0; i <= NBASES - 1; i++)
	{
		destroi_cjt (w->vBas[i].presentes);
		fila_destroi (&(w->vBas[i].espera));
	}

	for (i = 0; i <= NHEROIS - 1; i++)
	{
		destroi_cjt (w->vHer[i].habilidades);
	}

	for (i = 0; i <= NMISSOES - 1; i++)
	{
		destroi_cjt (w->vMis[i].habilidades);
	}
}