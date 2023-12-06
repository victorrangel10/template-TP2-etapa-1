

#ifndef _TENCA_H_
#define _TENCA_H_

typedef struct tEncaminhamento tEncaminhamento;
#include <stdio.h>
tEncaminhamento * CriaEncaminhamento(char * nomep,char * cpf, char * especialidade, char* motivo, char* nomedico, char* crm,char *data);

void DesalocaEncaminhamento(void * dado);

void ImprimeTelaEncaminhamento (tEncaminhamento * e);

void ImprimeArquivoEncaminhamento(tEncaminhamento* e, void* path);

#endif