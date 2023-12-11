#include "tSecretario.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tAgente.h"

struct tSecretario {
    tAgente* pessoa;
    char usuario[21];
    char senha[21];
    char acesso[10];
};

typedef enum {
    USER,
    ADMIN
} Acesso;

void SalvaSecretario(FILE* banco, tSecretario* secretario) {
    fwrite(secretario, sizeof(tSecretario), 1, banco);

    if (secretario->pessoa) {
        RegistraAgenteBancoDados(secretario->pessoa, banco);  // Chamada à função para salvar a estrutura tAgente
    }

    /*fwrite(secretario->usuario, sizeof(char), strlen(secretario->usuario) + 1, banco);
    fwrite(secretario->senha, sizeof(char), strlen(secretario->senha) + 1, banco);
    fwrite(secretario->acesso, sizeof(char), strlen(secretario->acesso) + 1, banco);*/
}

tSecretario* RecuperaSecretario(FILE* banco) {
    tSecretario* secretario = malloc(sizeof(tSecretario));
    if (secretario == NULL) {
        perror("Erro ao alocar memória para secretário");
        exit(EXIT_FAILURE);
    }

    fread(secretario, sizeof(tSecretario), 1, banco);

    secretario->pessoa = RecuperaAgenteBancoDados(banco);

    /*fread(secretario->usuario, sizeof(char), 21, banco);
    fread(secretario->senha, sizeof(char), 21, banco);
    fread(secretario->acesso, sizeof(char), 10, banco);*/

    return secretario;
}

char* ObtemNomeSecretario(tSecretario* s) {
    return ObtemNomeAgente(s->pessoa);
}
tSecretario* LeSecretario() {
    tSecretario* secretario = calloc(1, sizeof(tSecretario));
    if (secretario == NULL) {
        perror("Erro ao alocar memória para secretário");
        exit(EXIT_FAILURE);
    }

    // Lendo os dados do secretário
    printf("#################### CADASTRO SECRETARIO #######################\n");
    secretario->pessoa = LeAgente();  // Usando LeAgente() para ler os dados do agente
    printf("NOME DE USUARIO: ");
    scanf("%[^\n]", secretario->usuario);

    while (getchar() != '\n')
        ;
    printf("LOGIN EH %s\n", secretario->usuario);
    printf("SENHA: ");
    scanf("%[^\n]", secretario->senha);
    while (getchar() != '\n')
        ;
    printf("SENHA EH %s\n", secretario->senha);
    printf("NIVEL DE ACESSO: ");
    scanf("%[^\n]", secretario->acesso);
    while (getchar() != '\n')
        ;
    printf("ACESSO EH %s\n", secretario->acesso);
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");

    return secretario;
}

char* ObtemSenhaSecretario(tSecretario* s) {
    return s->senha;
}

char* ObtemLoginSecretario(tSecretario* s) {
    return s->usuario;
}

int EhAdminSecretario(tSecretario* s) {
    if (strcmp(s->acesso, "ADMIN") == 0) {
        return 1;
    } else if (strcmp(s->acesso, "USER") == 0) {
        return 0;
    } else {
        printf("SECRETARIO COM VALOR DE ACESSO INVALIDO\n");
    }
}
void LiberaSecretario(tSecretario* s) {
    if (s->pessoa) {
        free(s->pessoa);
    }
    if (s) {
        free(s);
    }
}

char* ObtemCPFSecretario(tSecretario* s) {
    return ObtemCPFAgente(s->pessoa);
}