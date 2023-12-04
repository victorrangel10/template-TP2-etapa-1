#include "tDocumento.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tDocumento {
  void *dado;
  func_ptr_imprimeNaTela imprime_tela;
  func_ptr_imprimeEmArquivo imprime_arquivo;
  func_ptr_desaloca func_desaloca;
};

tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                          func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                          func_ptr_desaloca desaloca) {
  tDocumento *d = malloc(sizeof(tDocumento));
  if (d == NULL) {
    exit(1);
  }

  d->dado = dado;
  d->func_desaloca = desaloca;
  d->imprime_arquivo = ImprimeEmArquivo;
  d->imprime_tela=imprimeNaTela;
  d->func_desaloca = desaloca;

  return d;
}

void desalocaDocumento(tDocumento *doc) {
  if (doc != NULL) {
    if (doc->dado) doc->func_desaloca(doc->dado);
  }
  free(doc);
}

void imprimeNaTelaDocumento(tDocumento *doc) { doc->imprime_tela(doc->dado); }

void imprimeEmArquivoDocumento(tDocumento *doc, char *path) {
  doc->imprime_arquivo(doc->dado, path);
}