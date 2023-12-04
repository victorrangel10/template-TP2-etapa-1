#include "tLesao.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tLesao {
  char rotulo[6];
  char diagnostico[100];
  char regiao[30];
  int tamanho;
  int vaiPraCirurgia;
  int vaiPraCrioterapia;
};

tLesao *criaLesao(char *rotulo, char *diagnostico, char *regiao, int tamanho,
                  int cir, int crio) {
  tLesao *l = calloc(1, sizeof(tLesao));

   strcpy(l->rotulo, rotulo);
 
  strcpy(l->diagnostico, diagnostico);

  strcpy(l->regiao, regiao);

  l->tamanho = tamanho;

  l->vaiPraCirurgia = cir;

  l->vaiPraCrioterapia = crio;

  return l;
}

void desalocaLesao(void *dado) {
  if (dado) {
    tLesao *t = (tLesao *)dado;
    free(t);
  }
}

void ImprimeLesao(tLesao *l) {
  printf("%s - %s - %s - %dMM\n", l->rotulo, l->diagnostico, l->regiao,
         l->tamanho);
}

void ImprimeEmArquivoLesao(tLesao *l,FILE * arq) {
  fprintf(arq,"%s - %s - %s - %dMM\n", l->rotulo, l->diagnostico, l->regiao,
         l->tamanho);
}


int VaiPraCrioterapiaLesao(tLesao * l){
  return l->vaiPraCrioterapia;
}



void SalvaLesao(FILE* banco,tLesao* lesao){

  fwrite(lesao,sizeof(tLesao),1,banco);
 

}

tLesao* RecuperaLesao(FILE * banco){
  tLesao * l = calloc(1,sizeof(tLesao));
  if (l==NULL)
  {
    printf("erro ao alocar memomoria para lesao\n");
    exit(EXIT_FAILURE);
  }
  fread(l,sizeof(tLesao),1,banco);
  return l;
  
}