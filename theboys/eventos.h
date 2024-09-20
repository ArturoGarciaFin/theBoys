struct time
{
	int id_bas;
	int dis;
};

void big_bang (struct mundo *w, struct lef_t *lef);

void chega (int tempo, struct heroi h, struct base b, struct mundo *w,
			struct lef_t *lef);

void desiste (int tempo, struct heroi h, struct base b, struct mundo *w,
				struct lef_t *lef);

void espera (int tempo, struct heroi h, struct base b, struct mundo *w,
				struct lef_t *lef);

void avisa (int tempo, struct base b, struct mundo *w,
			struct lef_t *lef);

void entra (int tempo, struct heroi h, struct base b, struct mundo *w,
			struct lef_t *lef);

void sai (int tempo, struct heroi h, struct base b, struct mundo *w,
			struct lef_t *lef);

void viaja (int tempo, struct heroi h, struct base b, struct mundo *w,
			struct lef_t *lef);

int missao (int tempo, struct missao m, struct mundo *w,
			struct lef_t *lef);

void meteoro (struct mundo *w);