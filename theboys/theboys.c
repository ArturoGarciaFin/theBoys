#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "fila.h"
#include "lef.h"
#include "conjunto.h"
#include "eventos.h"


int main()
{
    srand (0);

    struct mundo w;
    struct lef_t *lef;
    struct evento_t *e;
    int tempo, relogio;
    int  misCump, i, total_tent;
    float pctCump, medCump;

    lef = cria_lef();

    /*inicializa o mundo*/
    big_bang (&w, lef);

    tempo = TINICIO;
    relogio = TFIM;
    misCump = 0;
    total_tent = 0;
    
    
    while (tempo < relogio)
    {
        e = retira_lef (lef);

        if (!e)
            break;

        switch (e->tipo)
        {
            case 0:
                chega (e->tempo, w.vHer[e->dado1], w.vBas[e->dado2], &w, lef);
                break;
            
            case 1:
                espera (e->tempo, w.vHer[e->dado1], w.vBas[e->dado2], &w, lef);
                break;

            
            case 2:
                desiste (e->tempo, w.vHer[e->dado1], w.vBas[e->dado2],
                            &w, lef);
                break;
            
            
            
            case 3:
                avisa (e->tempo, w.vBas[e->dado2], &w, lef);
                break;


            
            case 4:
                entra (e->tempo, w.vHer[e->dado1], w.vBas[e->dado2], &w, lef);
                break;

            
            case 5:
                sai (e->tempo, w.vHer[e->dado1], w.vBas[e->dado2], &w, lef);
                break;

            
            case 6:
                viaja (e->tempo, w.vHer[e->dado1], w.vBas[e->dado2],
                        &w, lef);
                break;
            
            
            
            case 7:
                misCump = misCump + missao (e->tempo, w.vMis[e->dado1],
                                            &w, lef);
                break;
            

            
            case 8:
                printf ("%d: FIM\n", tempo);

                for (i = 0; i <= NHEROIS - 1; i++)
                {
                    printf ("HEROI %d PAC %d VEL %d EXP %d HABS ", i,
                            w.vHer[i].paciencia,
                    w.vHer[i].velocidade, w.vHer[i].experiencia);
                    imprime_cjt (w.vHer[i].habilidades);
                }

                for (i = 0; i <= NMISSOES - 1; i++)
                {
                    total_tent = total_tent + w.vMis[i].tentativas;
                }

                medCump = (float)total_tent / NMISSOES;

                pctCump = (float)misCump * 100 / (float)NMISSOES;

                printf ("MISSOES CUMPRIDAS: %d/%d (%.2f%%)\n", misCump,
                        NMISSOES, pctCump);
                printf ("TENTATIVAS/MISSAO: MIN %d MAX %d, MEDIA %2.f", 1, 8, medCump);

                meteoro (&w);
                break;
            

        }

    tempo = e->tempo;
    destroi_evento (e);

    }
    
    destroi_lef (lef);
    
    return 0;
}