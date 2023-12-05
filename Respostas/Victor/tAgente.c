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
};

tAgente* LeAgente() {
    tAgente* agente = calloc(1, sizeof(tAgente));

    if (agente == NULL) {
        perror("Erro ao alocar memória p    ara agente");
        exit(EXIT_FAILURE);
    }

    printf("NOME COMPLETO: ");
    scanf("%[^\n]%*c", agente->nome);
    printf(" nome eh %s", agente->nome);

    printf("CPF: ");
    scanf("%[^\n]%*c", agente->cpf);
    printf("cpf eh %s", agente->cpf);

    printf("DATA DE NASCIMENTO: ");
    scanf("%[^\n]%*c", agente->dataNascimento);
    printf("data eh %s", agente->dataNascimento);

    printf("TELEFONE: ");
    scanf("%[^\n]%*c", agente->telefone);
    printf("tel eh %s", agente->telefone);

    printf("GENERO: ");
    scanf("%[^\n]%*c", agente->genero);
    printf("genero eh %s", agente->genero);

    return agente;
}

void RegistraAgenteBancoDados(tAgente* agente, FILE* banco) {
    fwrite(agente, sizeof(tAgente), 1, banco);

    if (agente->nLesoes) {
        for (size_t i = 0; i < agente->nLesoes; i++) {
            SalvaLesao(banco, agente->lesoes[i]);
        }
    }
    fwrite(agente->cpf, sizeof(char), strlen(agente->cpf) + 1, banco);
    fwrite(agente->dataNascimento, sizeof(char), strlen(agente->dataNascimento) + 1, banco);
    fwrite(agente->genero, sizeof(char), strlen(agente->genero) + 1, banco);
    fwrite(agente->nome, sizeof(char), strlen(agente->nome) + 1, banco);
    fwrite(agente->telefone, sizeof(char), strlen(agente->telefone) + 1, banco);
}

tAgente* RecuperaAgenteBancoDados(FILE* banco) {
    tAgente* agente = malloc(sizeof(tAgente));
    if (agente == NULL) {
        perror("Erro ao alocar memória para abrir agente");
        exit(EXIT_FAILURE);
    }
    fread(agente, sizeof(tAgente), 1, banco);

    agente->lesoes = malloc(agente->nLesoes * sizeof(tLesao*));

    if (agente->nLesoes) {
        for (size_t i = 0; i < agente->nLesoes; i++) {
            agente->lesoes[i] = RecuperaLesao(banco);
        }
    }

    fread(agente->cpf, sizeof(char), 15, banco);
    fread(agente->dataNascimento, sizeof(char), 11, banco);
    fread(agente->genero, sizeof(char), 15, banco);
    fread(agente->nome, sizeof(char), 101, banco);
    fread(agente->telefone, sizeof(char), 15, banco);
    
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


char * ObtemNomeAgente(tAgente * a){
    if (a)
    {
        return a->nome;
    }
    
}

char * ObtemDataNascimentoAgente(tAgente * a){
    if (a)
    {
        return a->dataNascimento;
    }
    
}

char * ObtemCPFAgente(tAgente * a){
    if (a)
    {
        return a->cpf;
    }
    
}