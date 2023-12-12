#include "tEncaminhamento.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tEncaminhamento {
    char nomePaciente[101];
    char cpf[15];
    char especialidade[51];
    char motivo[301];
    char nomeMedico[101];
    char crm[13];
    char dataStr[11];
};

void PrintaIntDataStr(char* data) {
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    printf("%d/%d/%d\n\n", dia, mes, ano);
}

void PrintaEmArqIntDataStrEm(char* data, FILE* arq) {
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    fprintf(arq, "%d/%d/%d\n\n", dia, mes, ano);
}

tEncaminhamento* CriaEncaminhamento(char* nomep, char* cpf, char* especialidade, char* motivo, char* nomedico, char* crm, char* data) {
    tEncaminhamento* t = calloc(1, sizeof(tEncaminhamento));
    if (t == NULL) {
        exit(1);
    }

    strcpy(t->nomePaciente, nomep);
    strcpy(t->cpf, cpf);
    strcpy(t->especialidade, especialidade);
    strcpy(t->motivo, motivo);
    strcpy(t->nomeMedico, nomedico);
    strcpy(t->crm, crm);
    strcpy(t->dataStr, data);

    return t;
}

void DesalocaEncaminhamento(void* dado) {
    if (dado != NULL) {
        free(dado);
    }
}

void ImprimeTelaEncaminhamento(tEncaminhamento* e) {
    if (e == NULL) return;

    printf("PACIENTE: %s\n", e->nomePaciente);
    printf("CPF: %s\n", e->cpf);
    printf("\n");
    printf("ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    printf("MOTIVO:%s\n", e->motivo);
    printf("\n");
    printf("%s (%s)\n", e->nomeMedico, e->crm);
    PrintaIntDataStr(e->dataStr);
}

void ImprimeArquivoEncaminhamento(tEncaminhamento* e, void* path) {
    char dest[101];
    char* caminho = (char*)path;
    sprintf(dest, "%s/encaminhamento.txt", caminho);
    FILE* arq = fopen(dest, "a+");

    fprintf(arq, "PACIENTE: %s\n", e->nomePaciente);
    fprintf(arq, "CPF: %s\n", e->cpf);
    fprintf(arq, "\n");
    fprintf(arq, "ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    fprintf(arq, "MOTIVO: %s\n", e->motivo);
    fprintf(arq, "\n");
    fprintf(arq, "%s (%s)\n", e->nomeMedico, e->crm);
    PrintaEmArqIntDataStrEm(e->dataStr, arq);

    fclose(arq);
}
