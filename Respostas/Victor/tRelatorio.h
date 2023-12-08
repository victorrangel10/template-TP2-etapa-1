#ifndef _TRELATORIO_H_
#define _TRELATORIO_H_

#include "tLesao.h"
#include <stdio.h>

typedef struct tRelatorio tRelatorio;

tRelatorio* criaRelatorio(char* nomePaciente, int qtd, char* cpf, tLesao** lesoes,
                           char* nomemedico, char* crm, char* data);

tRelatorio* desalocaRelatorio(void* dado);

void imprimeNaTelaRelatorio(void* dado);

void imprimeEmArquivoRelatorio(void* dado, char* path);

#endif
