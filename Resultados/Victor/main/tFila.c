#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tFila.h"

struct tFila {
    tDocumento **documentos;
    int numdocs;
};

tFila *criaFila() {
    tFila *f = calloc(1, sizeof(tFila));
    if (f == NULL) {
        exit(1);
    }
    return f;
}

void desalocaFila(tFila *f) {
    if (f != NULL) {
        for (size_t i = 0; i < f->numdocs; i++) {
            if (f->documentos[i]) desalocaDocumento(f->documentos[i]);
        }
        if (f->documentos) free(f->documentos);
        if (f) free(f);
    }
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela, func_ptr_imprimeEmArquivo ImprimeEmArquivo, func_ptr_desaloca desaloca) {
    tDocumento *doc = criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);
    f->documentos = realloc(f->documentos, (f->numdocs + 1) * sizeof(tDocumento *));
    f->documentos[f->numdocs] = doc;
    f->numdocs++;
}


int quantidadeDocumentosNaFila(tFila *f){
    return f->numdocs;
}

void imprimeFila(tFila *f, char *path){

    for (size_t i = 0; i < f->numdocs; i++)
    {
        imprimeNaTelaDocumento(f->documentos[i]);
        imprimeEmArquivoDocumento(f->documentos[i],path);
    }
    
}