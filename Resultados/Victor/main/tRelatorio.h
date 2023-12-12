#ifndef _TRELATORIO_H_
#define _TRELATORIO_H_

#include <stdio.h>

#include "tLesao.h"

typedef struct tRelatorio tRelatorio;

tRelatorio* criaRelatorio(int sumIdades, int nIdades, int masc, int fem, int outros, int nLesoes, int sumTamLesoes, int cir, int criots, int natendidos,int t);

tRelatorio* desalocaRelatorio(void* dado);

void imprimeNaTelaRelatorio(void* dado);

void imprimeEmArquivoRelatorio(void* dado, char* path);

#endif
