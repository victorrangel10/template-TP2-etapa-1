
#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include "tLesao.h"
#include <stdio.h>


typedef struct tBiopsia tBiopsia;

tBiopsia* criaBiopsia(char* nomePaciente, int qtd, char* cpf, tLesao** lesoes,
                      char* nomemedico, char *crm, char* data);

tBiopsia* desalocaBiopsia(void* dado);

void imprimeNaTelaBiospsia(void* dado);

void imprimeEmArquivoBiopsia(void* dado,char * path);
#endif