#include "tMedico.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tAgente.h"

struct tMedico {
    tAgente* pessoa;
    char CRM[13];
    char usuario[21];
    char senha[21];
};

tMedico* LeMedico() {
    tMedico* medico = calloc(1, sizeof(tMedico));
    if (medico == NULL) {
        perror("Erro ao alocar memória para médico");
        exit(EXIT_FAILURE);
    }

    // Lendo os dados do médico
    printf("#################### CADASTRO MEDICO #######################\n");
    medico->pessoa = LeAgente();  // Usando LeAgente() para ler os dados do agente
    printf("CRM: ");

    scanf("%[^\n]%*c", medico->CRM);

    printf("NOME DE USUARIO: ");
    scanf("%[^\n]", medico->usuario);
    printf("USER EH %s\n", medico->usuario);
    while (getchar() != '\n')
        ;
    printf("SENHA: ");
    scanf("%[^\n]%*c", medico->senha);
    printf("SENHA EH %s\n", medico->senha);

    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    return medico;
}

void SalvaMedico(FILE* banco, tMedico* medico) {
    fwrite(medico, sizeof(tMedico), 1, banco);

    if (medico->pessoa != NULL) {
        RegistraAgenteBancoDados(medico->pessoa, banco);
    }
    fwrite(medico->CRM, sizeof(char), strlen(medico->CRM) + 1, banco);
    fwrite(medico->usuario, sizeof(char), strlen(medico->usuario) + 1, banco);
    fwrite(medico->senha, sizeof(char), strlen(medico->senha) + 1, banco);
}


tMedico* RecuperaMedico(FILE* banco) {
    tMedico* medico = malloc(sizeof(tMedico));
    if (medico == NULL) {
        perror("Erro ao alocar memória para médico");
        exit(EXIT_FAILURE);
    }

    fread(medico, sizeof(tMedico), 1, banco);

    medico->pessoa = RecuperaAgenteBancoDados(banco);
    fread(medico->CRM, sizeof(char), 13, banco);
    fread(medico->usuario, sizeof(char), 21, banco);
    fread(medico->senha, sizeof(char), 21, banco);

    return medico;
}

void LiberaMedico(tMedico* m) {
    if (m->pessoa) {
        LiberaAgente(m->pessoa);
    }
    printf("CHEGOU3\n");
    if (m != NULL) {
        free(m);
    }
    printf("CHEGOU44\n");
}

char* ObtemNomeMedico(tMedico* m) {
    if (m) {
        return ObtemNomeAgente(m->pessoa);
    }
}

char* ObtemCRMMedico(tMedico* m) {
    if (m) {
        return m->CRM;
    }
}

char* ObtemCPFMedico(tMedico* m) {
    if (m) {
        return ObtemCPFAgente(m->pessoa);
    }
}

char* ObtemLoginMedico(tMedico* m) {
    return m->usuario;
}

char* ObtemSenhaMedico(tMedico* m) {
    return m->senha;
}