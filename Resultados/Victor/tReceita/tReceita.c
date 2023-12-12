#include "tReceita.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tReceita {
  char nomePaciente[101];
  eTipoUso tipoUso;
  char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
  char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
  int quantidade;
  char instrucoes[MAX_TAM_INSTRUCOES];
  char nomeMedico[101];
  char CRM[13];
  char data[11];
  int dia, mes, ano;
};

void PrintaIntDataStrR(char *data) {
  int dia, mes, ano;
  sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
  printf("%d/%d/%d\n\n", dia, mes, ano);
}

void PrintaEmArqIntDataStrEmR(char *data, FILE *arq) {
  int dia, mes, ano;
  sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
  fprintf(arq, "%d/%d/%d\n\n", dia, mes, ano);
}

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso,
                      char *nomeMedicamento, char *tipoMedicamento,
                      char *instrucoes, int qntd, char *nomeMedico, char *CRM,
                      char *dataStr) {
  tReceita *r = calloc(1, sizeof(tReceita));
  if (r == NULL) {
    exit(1);
  }

  r->quantidade = qntd;
  r->tipoUso = tipoUso;
  strcpy(r->nomePaciente, nomePaciente);
  strcpy(r->nomeMedicamento, nomeMedicamento);
  strcpy(r->tipoMedicamento, tipoMedicamento);
  strcpy(r->instrucoes, instrucoes);
  strcpy(r->nomeMedico, nomeMedico);
  if (CRM) strcpy(r->CRM, CRM);
  strcpy(r->data, dataStr);
  int dia, mes, ano;
  sscanf(dataStr, "%d/%d/%d", &dia, &mes, &ano);
  r->dia = dia;
  r->mes = mes;
  r->ano = ano;
  return r;
}

void desalocaReceita(void *dado) {
  if (dado == NULL) {
    return;
  }
  free(dado);
}

void ImprimeUso(eTipoUso tipo) {
  if (tipo == ORAL) {
    printf("USO ORAL\n\n");
  } else if (tipo == TOPICO) {
    printf("USO TOPICO\n\n");
  } else {
    printf("ERRO NO TIPO USO\n");
  }
}

void imprimeNaTelaReceita(void *dado) {
  tReceita *r = (tReceita *)dado;
  printf("RECEITUARIO\n");
  printf("NOME: %s\n\n", r->nomePaciente);
  ImprimeUso(r->tipoUso);
  printf("%s\n%d %s\n\n", r->nomeMedicamento, r->quantidade,
         r->tipoMedicamento);
  printf("%s\n\n", r->instrucoes);
  printf("%s (%s)\n", r->nomeMedico, r->CRM);
  PrintaIntDataStrR(r->data);
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma receita) e
 * imprime os dados no arquivo específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou
 * editado. Ex: /home/usuario/Documentos O nome do arquivo e a maneira de
 * escrita é definido dentro da função
 */
void imprimeEmArquivoReceita(void *dado, char *path) {
  char dest[250];
  sprintf(dest, "%s/receita.txt", path);
  FILE *arq = fopen(dest, "a");
  if (arq == NULL) {
    perror("Erro ao abrir o arquivo para abrir");
    exit(EXIT_FAILURE);
  }

  tReceita *r = (tReceita *)dado;

  fprintf(arq, "RECEITUARIO\n");
  fprintf(arq, "NOME: %s\n\n", r->nomePaciente);
  if (r->tipoUso == ORAL) {
    fprintf(arq, "USO ORAL\n\n");
  } else if (r->tipoUso == TOPICO) {
    fprintf(arq, "USO TOPICO\n\n");
  }

  fprintf(arq, "%s\n%d %s\n\n", r->nomeMedicamento, r->quantidade,
          r->tipoMedicamento);
  fprintf(arq, "%s\n\n", r->instrucoes);
  fprintf(arq, "%s (%s)\n", r->nomeMedico, r->CRM);
  fprintf(arq, "%d/%d/%d\n\n", r->dia, r->mes, r->ano);

  fclose(arq);
}