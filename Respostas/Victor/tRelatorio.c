#include "tRelatorio.h"

#include <stdio.h>
#include <stdlib.h>

struct tRelatorio {
    int sumIdades, nIdades, masc, fem, outros, nLesoes;
    int sumTamLesoes, cirugias, crioterapias, nAtendidos;
};

tRelatorio* criaRelatorio(int sumIdades, int nIdades, int masc, int fem, int outros, int nLesoes, int sumTamLesoes, int cir, int criots, int natendidos) {
    tRelatorio* r = malloc(sizeof(tRelatorio));
    if (r == NULL) {
        perror("erro ao alocar memoria do relatorio\n");
        exit(EXIT_FAILURE);
    }

    r->sumIdades = sumIdades,
    r->nIdades = nIdades;
    r->masc = masc;
    r->fem = fem;
    r->outros = outros;
    r->nLesoes = nLesoes;
    r->sumTamLesoes = sumTamLesoes;
    r->cirugias = cir;
    r->crioterapias = criots;
    r->nAtendidos = natendidos;
    return r;
}

tRelatorio* desalocaRelatorio(void* dado) {
    if (dado) {
        free(dado);
    }
}

void imprimeNaTelaRelatorio(void* dado) {
    tRelatorio* r = (tRelatorio*)dado;
    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->nAtendidos);

    int mediaIdade = r->sumIdades / r->nAtendidos;

    printf("IDADE MEDIA: %d\n", mediaIdade);

    printf("DISTRIBUICAO POR GENERO:\n");

    printf("- FEMININO: %d\n", r->fem);

    printf("- MASCULINO: %d\n", r->masc);

    printf("- OUTROS: %d\n", r->outros);

    int tammediolesoes = r->sumTamLesoes / r->nLesoes;

    printf("TAMANHO MEDIO DAS LESOES: %d\n", tammediolesoes);

    printf("NUMERO TOTAL DE LESOES: %d\n", r->nLesoes);

    printf("NUMERO TOTAL DE CIRURGIAS: %d\n", r->cirugias);

    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n", r->crioterapias);
}

void imprimeEmArquivoRelatorio(void* dado, char* path) {
    tRelatorio* r = (tRelatorio*)dado;
    char dest[200];
    sprintf(dest, "%s/relatorio_geral.txt", path);
    FILE* arq = fopen(dest, "w");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo para lista");
        exit(EXIT_FAILURE);
    }

    fprintf(arq, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->nAtendidos);

    int mediaIdade = r->sumIdades / r->nAtendidos;

    fprintf(arq, "IDADE MEDIA: %d\n", mediaIdade);

    fprintf(arq, "DISTRIBUICAO POR GENERO:\n");

    fprintf(arq, "- FEMININO: %d\n", r->fem);

    fprintf(arq, "- MASCULINO: %d\n", r->masc);

    fprintf(arq, "- OUTROS: %d", r->outros);

    int tammediolesoes = r->sumTamLesoes / r->nLesoes;

    fprintf(arq, "TAMANHO MEDIO DAS LESOES: %d", tammediolesoes);

    fprintf(arq, "NUMERO TOTAL DE LESOES: %d\n", r->nLesoes);

    fprintf(arq, "NUMERO TOTAL DE CIRURGIAS: %d\n", r->cirugias);

    fprintf(arq, "NUMERO TOTAL DE CRIOTERAPIA: %d\n", r->crioterapias);

    fclose(arq);
}