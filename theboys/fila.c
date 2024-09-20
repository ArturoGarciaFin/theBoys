#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila *fila_cria ()
{
    struct fila *f;

	f = malloc(sizeof(struct fila)); 

	if (f == NULL)
		return NULL;

	f->ini = NULL;
	f->tamanho = 0; 

	return f;
}

void fila_destroi (struct fila **fila)
{
    struct nodo *aux;

	while ((*fila)->ini != NULL)
	{
		aux = (*fila)->ini;
		(*fila)->ini = (*fila)->ini->prox;
		free(aux);
	}

	free(*fila);
	(*fila) = NULL;
}

int enqueue (struct fila *fila, int dado)
{
    struct nodo *novo, *aux;

	novo = malloc(sizeof(struct nodo));

	if (novo == NULL)
		return 0;

	novo->chave = dado;
	novo->prox = NULL;

	if (fila_vazia(fila))
		fila->ini = novo;
	else
	{
		aux = fila->ini;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}

	(fila->tamanho)++;
	
	return 1;
}

int dequeue (struct fila *fila, int *dado)
{
    struct nodo *aux;

	if (fila_vazia(fila))
		return 0;

	*dado = fila->ini->chave;
	aux = fila->ini;
	fila->ini = fila->ini->prox;
	(fila->tamanho)--;

	free(aux);
	aux = NULL;

	return 1;
}

int fila_tamanho (struct fila *fila)
{
    return fila->tamanho;
}

int fila_vazia (struct fila *fila)
{
    if (!fila->tamanho)
		return 1;
	return 0;
}

void fila_imprime (struct fila *fila)
{
    struct nodo *aux;

    aux = fila->ini;

    printf("[ ");
    while (aux != NULL)
    {
        printf("%d ", aux->chave);
        aux = aux->prox;
    }
    printf("]\n");
}