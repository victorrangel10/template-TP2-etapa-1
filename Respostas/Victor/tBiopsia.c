#include "tBiopsia.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tLesao.h"

struct tBiopsia {
  char nomePaciente[101];
  int quantidade;
  char cpfPaciente[15];
  tLesao** lesoes;
  char nomeMedico[101];
  char crm[13];
  char data[11];
  int nlesoes;
};

tBiopsia* criaBiopsia(char* nomePaciente, int qtd, char* cpf, tLesao** lesoes,
                      char* nomemedico, char* crm, char* data) {
                        
  tBiopsia* b = calloc(1, sizeof(tBiopsia));


  strcpy(b->nomePaciente, nomePaciente);
  b->quantidade = qtd;
  strcpy(b->cpfPaciente, cpf);
  b->lesoes = lesoes;
  strcpy(b->nomeMedico, nomemedico);
  strcpy(b->crm, crm);
  strcpy(b->data, data);
  return b;
}

tBiopsia* desalocaBiopsia(void* dado) {
  tBiopsia* b = (tBiopsia*)dado;
  if (b != NULL) {
    for (size_t i = 0; i < b->nlesoes; i++) {
      desalocaLesao(b->lesoes[i]);
    }
    if (b->lesoes) free(b->lesoes);
  }
  free(b);
}

void imprimeNaTelaBiospsia(void* dado) {
  tBiopsia* b = (tBiopsia*)dado;
  printf("PACIENTE:%s\n", b->nomePaciente);
  printf("CPF:%s\n", b->cpfPaciente);
  printf("\n");
  printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

  for (size_t i = 0; i < b->nlesoes; i++) {
    ImprimeLesao(b->lesoes[i]);
  }

  printf("\n");

  printf("%s (%s)\n", b->nomeMedico, b->crm);
  printf("%s\n", b->data);
}

void imprimeEmArquivoBiopsia(void* dado,char * path) {
  tBiopsia* b = (tBiopsia*)dado;
  char dest[200];
  sprintf(dest,"%s/biopsia.txt",path);
  FILE* arq = fopen(dest, "w");
  if (arq == NULL) {
    perror("Erro ao abrir o arquivo para biopsia");
    exit(EXIT_FAILURE);
  }

  fprintf(arq,"PACIENTE:%s\n", b->nomePaciente);
  fprintf(arq,"CPF:%s\n", b->cpfPaciente);
  fprintf(arq,"\n");
  fprintf(arq,"SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

  for (size_t i = 0; i < b->nlesoes; i++) {
    ImprimeEmArquivoLesao(b->lesoes[i],arq);
  }

  fprintf(arq,"\n");

  fprintf(arq,"%s (%s)\n", b->nomeMedico, b->crm);
  fprintf(arq,"%s\n", b->data);
  fclose(arq);
}
