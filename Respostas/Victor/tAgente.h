#ifndef _atores
#define _atores

#include <stdio.h>

typedef struct tAgente tAgente;

void RegistraAgenteBancoDados(tAgente* agente, FILE* banco);

tAgente* LeAgente();

void LiberaAgente(tAgente* a);

tAgente* RecuperaAgenteBancoDados(FILE* banco);

void LiberaAgente(tAgente* a);

#endif