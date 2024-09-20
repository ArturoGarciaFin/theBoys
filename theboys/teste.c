#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "fila.h"
#include "lef.h"
#include "conjunto.h"

int main()
{
	int i;
	int maxBas;
	struct base *vBas[2];

	maxBas = 3;
	printf ("teste 1 = cria base\n");
	for (i = 0; i <= maxBas -1; i++)
	{
		vBas[i] = cria_base (i);
	}
}