#include "tAgente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tLesao.h"

struct tAgente {
    char nome[101];
    char cpf[15];             // 000.000.00-00
    char dataNascimento[11];  // dd/mm/aaaa
    char telefone[15];        //(00)00000-0000
    char genero[15];          // masc fem outros
    tLesao** lesoes;
    int nLesoes;
    int possuiDiabetes;
    int ehFumante;
    int possuiHistoricoCancer;
    int tipoPele;
    int jaFoiAtendido;
};

tAgente* LeAgente() {
    tAgente* agente = calloc(1, sizeof(tAgente));

    if (agente == NULL) {
        perror("Erro ao alocar memória para agente");
        exit(EXIT_FAILURE);
    }

    printf("NOME COMPLETO: ");
    scanf("%[^\n]%*c", agente->nome);
    printf(" nome eh %s\n", agente->nome);

    printf("CPF: ");
    scanf("%[^\n]%*c", agente->cpf);
    printf("cpf eh %s\n", agente->cpf);

    printf("DATA DE NASCIMENTO: ");
    scanf("%[^\n]%*c", agente->dataNascimento);
    printf("data eh %s\n", agente->dataNascimento);

    printf("TELEFONE: ");
    scanf("%[^\n]%*c", agente->telefone);
    printf("tel eh %s\n", agente->telefone);

    printf("GENERO: ");
    scanf("%[^\n]%*c", agente->genero);
    printf("genero eh %s\n", agente->genero);

    agente->possuiDiabetes = 199;

    return agente;
}

void RegistraAgenteBancoDados(tAgente* agente, FILE* banco) {
    if (agente) {
        fwrite(agente, sizeof(tAgente), 1, banco);
        /*  fwrite(agente->cpf, sizeof(char), strlen(agente->cpf) + 1, banco);
          fwrite(agente->dataNascimento, sizeof(char), strlen(agente->dataNascimento) + 1, banco);
          fwrite(agente->genero, sizeof(char), strlen(agente->genero) + 1, banco);
          fwrite(agente->nome, sizeof(char), strlen(agente->nome) + 1, banco);
          fwrite(agente->telefone, sizeof(char), strlen(agente->telefone) + 1, banco);*/
    }
}

void AtendePaciente(tAgente* a) {
    a->jaFoiAtendido = 1;
}

int JaFoiAtendidoPaciente(tAgente* a) {
    return a->jaFoiAtendido;
}

tAgente* RecuperaAgenteBancoDados(FILE* banco) {
    tAgente* agente = malloc(sizeof(tAgente));

    if (agente == NULL) {
        perror("Erro ao alocar memória para abrir agente");
        exit(EXIT_FAILURE);
    }

    fread(agente, sizeof(tAgente), 1, banco);

    /* fread(agente->cpf, sizeof(char), 15, banco);
     fread(agente->dataNascimento, sizeof(char), 11, banco);
     fread(agente->genero, sizeof(char), 15, banco);
     fread(agente->nome, sizeof(char), 101, banco);
     fread(agente->telefone, sizeof(char), 15, banco);*/

    return agente;
}

void LiberaAgente(tAgente* a) {
    if (a) {
        if (a->lesoes) {
            for (size_t i = 0; i < a->nLesoes; i++) {
                desalocaLesao(a->lesoes[i]);
            }
        }
        if (a->lesoes) {
            free(a->lesoes);
        }
        free(a);
    }
}

char* ObtemNomeAgente(tAgente* a) {
    if (a) {
        return a->nome;
    }
}

char* ObtemDataNascimentoAgente(tAgente* a) {
    if (a) {
        return a->dataNascimento;
    }
}

char* ObtemCPFAgente(tAgente* a) {
    if (a) {
        return a->cpf;
    }
}

char* ObtemGeneroAgente(tAgente* a) {
    if (a) return a->genero;
}

void AtendeuPaciente(tAgente* a) {
    if (a) {
        a->jaFoiAtendido = 1;
    }
}

tAgente* ClonaAgente(tAgente* a) {
    tAgente* novo = calloc(1, sizeof(tAgente));

    strcpy(novo->cpf, a->cpf);
    strcpy(novo->nome, a->nome);
    strcpy(novo->dataNascimento, a->dataNascimento);
    strcpy(novo->genero, a->genero);
    strcpy(novo->telefone, a->telefone);
    novo->nLesoes = a->nLesoes;
    novo->possuiDiabetes = a->possuiDiabetes;
    novo->possuiHistoricoCancer = a->possuiHistoricoCancer;
    novo->tipoPele = a->tipoPele;
    novo->jaFoiAtendido = a->jaFoiAtendido;
    novo->ehFumante = a->ehFumante;
    for (size_t i = 0; i < novo->nLesoes; i++) {
        novo->lesoes[i] = ClonaLesao(a->lesoes[i]);
    }
    return novo;
}
