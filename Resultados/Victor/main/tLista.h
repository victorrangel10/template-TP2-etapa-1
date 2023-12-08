#ifndef _TLISTA_H_
#define _TLISTA_H_

#include "tLesao.h"
#include <stdio.h>
#include "tAgente.h"
typedef struct tLista tLista;

tLista* criaLista(char* nome, tAgente** agentes,int numAgentes);

tLista* desalocaLista(void* dado);

void imprimeNaTelaLista(void* dado);

void imprimeEmArquivoLista(void* dado, char* path);

#endif
