#include "tLista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tAgente.h"

struct tLista {
    char nomeBuscado[101];
    tAgente** agentes;
    int nAgentes;
};

tLista* criaLista(char* nome, tAgente** agentes, int nAgentes) {
    tLista* l = calloc(1, sizeof(tLista));
    strcpy(l->nomeBuscado, nome);

    l->agentes = malloc(nAgentes * sizeof(tAgente*));
    l->nAgentes = nAgentes;
    for (size_t i = 0; i < nAgentes; i++) {
        l->agentes[i] = ClonaAgente(agentes[i]);
    }

    return l;
}

tLista* desalocaLista(void* dado) {
    tLista* lista = (tLista*)dado;
    if (lista != NULL) {
        for (size_t i = 0; i < lista->nAgentes; i++) {
            LiberaAgente(lista->agentes[i]);
        }
        free(lista->agentes);
    }
    free(lista);
}

void imprimeNaTelaLista(void* dado) {
    tLista* l = (tLista*)dado;
    for (size_t i = 0; i < l->nAgentes; i++) {
        if (strcmp(l->nomeBuscado, ObtemNomeAgente(l->agentes[i])) == 0) {
            printf("%d - %s(%s)\n", i+1, ObtemNomeAgente(l->agentes[i]), ObtemCPFAgente(l->agentes[i]));
        }
    }
}

void imprimeEmArquivoLista(void* dado, char* path) {
    tLista* l = (tLista*)dado;
    char dest[200];
    sprintf(dest, "%s/lista_busca.txt", path);
    FILE* arq = fopen(dest, "w");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo para lista");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < l->nAgentes; i++) {
        if (strcmp(l->nomeBuscado, ObtemNomeAgente(l->agentes[i])) == 0) {
            fprintf(arq, "%d - %s(%s)\n", i, ObtemNomeAgente(l->agentes[i]), ObtemCPFAgente(l->agentes[i]));
        }
    }
    fclose(arq);
}