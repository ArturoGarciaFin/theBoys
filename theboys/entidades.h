#define TINICIO 0
#define TFIM 526500
#define TAMMUNDO 20000
#define NHABILIDADES 10
#define NHEROIS (NHABILIDADES * 5)
#define NBASES (NHEROIS / 6)
#define NMISSOES (TFIM / 100)



struct coordenadas
{
	int x;
	int y;
};

struct base
{
	int id;
	int lotacao;
	struct conjunto *presentes;
	struct fila *espera;
	struct coordenadas local;
};

struct heroi
{
	int id;
	struct conjunto *habilidades;
	int paciencia;
	int velocidade;
	int experiencia;
	int base;
};

struct missao
{
	int id;
	struct conjunto *habilidades;
	struct coordenadas local;
	int tentativas;
};


struct mundo
{
	int nHerois;
	struct heroi vHer[NHEROIS];
	int nBases;
	struct base vBas[NBASES];
	int habilidades;
	int nMissoes;
	struct missao vMis[NMISSOES];
	int tamanhoMundo[4];
	int relogio;
};

/*retorna um numero aleatorio entre min e max*/
int aleat (int min, int max);

struct heroi cria_heroi (int id);

void imprime_heroi (struct heroi h);

struct base cria_base (int id, int x, int y);

void imprime_base (struct base b);

struct missao cria_missao (int id, int x, int y);

void imprime_missao (struct missao m);