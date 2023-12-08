#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tBiopsia.h"
#include "tEncaminhamento.h"
#include "tFila.h"
#include "tLesao.h"
#include "tMedico.h"
#include "tReceita.h"

typedef struct tConsulta tConsulta;

tConsulta* criaConsulta(char* crm,char*nomeapl, tAgente* paciente);

void DesalocaConsulta(tConsulta* c);

void RealizaConsulta(tConsulta* consulta, tFila* fila);

void ImprimeMenuConsulta();

void CadastraLesao(tConsulta* consulta);

void CadastraReceita(tConsulta* consulta, tFila* fila);

void GeraBiopsia(tConsulta* consulta, tFila* fila);

void GeraEncaminhamento(tConsulta* consulta, tFila* fila);

void SalvaConsultaBin(FILE* bancoConsulta, FILE* bancoLesoes, tConsulta* c);

void SalvaLesoes(tLesao** lesoes, int num, FILE* bancoLesoes);

void RecuperaLesoesConsulta(FILE* banco, int num, tConsulta* consulta);

tConsulta* RecuperaConsulta(FILE* bancoConsulta, FILE * bancoLesoes);
