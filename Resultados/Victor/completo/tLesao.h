#ifndef _TLESAO_H_
#define _TLESAO_H_

typedef struct tLesao tLesao;

#include <stdio.h>

tLesao *criaLesao(char *rotulo, char *diagnostico, char *regiao, int tamanho, int cir, int crio);

void desalocaLesao(void *dado);

void ImprimeLesao(tLesao *l) ;

void ImprimeEmArquivoLesao(tLesao *l,FILE * arq);

int VaiPraCrioterapiaLesao(tLesao * l);

void SalvaLesao(FILE* banco,tLesao* lesao);

tLesao* RecuperaLesao(FILE * banco);

int VaiPraCirurgiaLesao(tLesao * t);

#endif