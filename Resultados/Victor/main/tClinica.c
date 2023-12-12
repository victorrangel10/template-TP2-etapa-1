#define SECRETARIO 1
#define MEDICO 2
#define PACIENTE 3
#include "tClinica.h"

struct tClinica {
    tAgente** pacientes;
    int nPacientes;

    tMedico** medicos;
    int nMedicos;

    tSecretario** secretarios;
    int nSecretarios;

    tFila* filaImpressao;
    int nDocsFila;

    tConsulta** consultas;
    int nConsultas;

    int nAtendidosPreviamente;
};

tAgente* BuscaPacienteClinica(tClinica* c, char* cpf) {
    for (size_t i = 0; i < c->nPacientes; i++) {
        if (strcmp(ObtemCPFAgente(c->pacientes[i]), cpf) == 0) {
            return c->pacientes[i];
        }
    }
    return NULL;
}

void RealizaConsultaClinica(tClinica* clinica, FILE* bancoConsulta, FILE* bancoLesoes, char* nomeAtendente, char* cpfAtendente, char* crmAtendente) {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE:");
    char cpfPaciente[15];
    scanf("%[^\n]", cpfPaciente);
    while (getchar() != '\n')
        ;
    tAgente* paciente = BuscaPacienteClinica(clinica, cpfPaciente);

    if (paciente == NULL) {
        printf("PACIENTE SEM CADASTRO\n\n");
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("##########################################################");
        scanf("%*c");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("---\n");
    printf("-NOME: %s\n", ObtemNomeAgente(paciente));
    printf("-DATA DE NASCIMENTO: %s", ObtemDataNascimentoAgente(paciente));
    printf("---\n");

    tConsulta* consulta = criaConsulta(crmAtendente, nomeAtendente, paciente);

    RealizaConsulta(consulta, clinica->filaImpressao, bancoConsulta, bancoLesoes);

    clinica->consultas = realloc(clinica->consultas, (clinica->nConsultas + 1) * sizeof(tConsulta*));

    clinica->consultas[clinica->nConsultas] = consulta;

    clinica->nConsultas++;

    printf("CONSULTA NUMERO %d COM PACIENTE %s de idade %d com %d lesoes realizada e salva\n", clinica->nConsultas, ObtemNomeAgente(ObtemPacienteConsulta(clinica->consultas[clinica->nConsultas - 1])), ObtemIdadePaciente(ObtemPacienteConsulta(clinica->consultas[clinica->nConsultas - 1])), ObtemNLesoesConsulta(clinica->consultas[clinica->nConsultas - 1]));

    AtendeuPaciente(paciente);
    if (JaFoiAtendidoPaciente(paciente)) {
        printf("\n\n\n\n\n PACIENTE %s ATENDIDO\n\n\n\n\n\n", ObtemNomeAgente(paciente));
    }
}

void SalvaClinicaBinario(tClinica* clinica, FILE* bancoCLINICA) {
    if (clinica) {
        fwrite(clinica, sizeof(tClinica), 1, bancoCLINICA);

        // fwrite(&clinica->nPacientes, sizeof(int), 1, bancoCLINICA);

        // fwrite(&clinica->nMedicos, sizeof(int), 1, bancoCLINICA);

        // fwrite(&clinica->nSecretarios, sizeof(int), 1, bancoCLINICA);

        // fwrite(&clinica->nConsultas, sizeof(int), 1, bancoCLINICA);
    }
}

tClinica* RecuperaClinicaBinario(FILE* bancoCLINICA, FILE* bancoMEDICOS, FILE* bancoPACIENTES, FILE* bancoLESOES, FILE* bancoSECRETARIOS, FILE* bancoCONSULTAS) {
    tClinica* c = calloc(1, sizeof(tClinica));
    if (c == NULL) {
        perror("Erro alocando memoria pra clinica");
        exit(EXIT_FAILURE);
    }

    // Recuperando todos os dados da clinica
    fread(c, sizeof(tClinica), 1, bancoCLINICA);

    // fread(&c->nPacientes, sizeof(int), 1, bancoCLINICA);

    printf("NUMERO DE PACIENTES RECUPERADOS: %d\n", c->nPacientes);

    // fread(&c->nMedicos, sizeof(int), 1, bancoCLINICA);
    printf("NUMERO DE MEDICOS RECUPERADOS: %d\n", c->nMedicos);
    // fread(&c->nSecretarios, sizeof(int), 1, bancoCLINICA);
    printf("NUMERO DE SECRETARIOS RECUPERADOS: %d\n", c->nSecretarios);
    // fread(&c->nConsultas, sizeof(int), 1, bancoCLINICA);
    printf("NUMERO DE CONSULTAS RECUPERADOS: %d\n", c->nConsultas);

    // Recuperando os pacientes
    c->pacientes = malloc(c->nPacientes * sizeof(tAgente*));
    // criando espaco para o vetor de agentes
    if (c->pacientes == NULL) {
        perror("Erro ao alocar memória para pacientes");
        exit(EXIT_FAILURE);
    }
    RecuperaPacientesClinica(c, bancoPACIENTES);  // Recupera os pacientes do arquivo

    // Recuperando medicos
    c->medicos = malloc(c->nMedicos * sizeof(tMedico*));
    if (c->medicos == NULL) {
        perror("Erro ao alocar memória para medicos");
        exit(EXIT_FAILURE);
    }
    RecuperaMedicosClinica(c, bancoMEDICOS);

    // Recuperando secretarios
    c->secretarios = malloc(c->nSecretarios * sizeof(tSecretario*));
    if (c->secretarios == NULL) {
        perror("Erro ao alocar memória para pacientes");
        exit(EXIT_FAILURE);
    }
    RecuperaSecretariosClinica(c, bancoSECRETARIOS);

    // Recuperando consultas
    c->consultas = malloc(c->nConsultas * sizeof(tConsulta*));
    for (size_t i = 0; i < c->nConsultas; i++) {
        c->consultas[i] = RecuperaConsulta(bancoCONSULTAS, bancoLESOES);
    }

    c->filaImpressao = criaFila();
    return c;
}

void RecuperaSecretariosClinica(tClinica* clinica, FILE* banco) {
    // Itera sobre cada paciente e os recupera do arquivo
    printf("NUMERO DE SECRETARIOS DA CLINICA EH OFICIALMENTE %d", clinica->nSecretarios);
    for (size_t i = 0; i < clinica->nSecretarios; i++) {
        clinica->secretarios[i] = RecuperaSecretario(banco);

        printf("NOME DO SECRETARIO RECUPERADO EH %s\n", ObtemNomeSecretario(clinica->secretarios[i]));
    }
}

void RecuperaMedicosClinica(tClinica* clinica, FILE* bancoMedicos) {
    // Itera sobre cada médico e os recupera do arquivo
    for (size_t i = 0; i < clinica->nMedicos; i++) {
        clinica->medicos[i] = RecuperaMedico(bancoMedicos);
    }
}
void RecuperaPacientesClinica(tClinica* clinica, FILE* bancoPaciente) {
    // Itera sobre cada paciente e os recupera do arquivo
    for (size_t i = 0; i < clinica->nPacientes; i++) {
        clinica->pacientes[i] = RecuperaAgenteBancoDados(bancoPaciente);
    }
}

tClinica* CriaClinica() {
    tClinica* cli = calloc(1, sizeof(tClinica));
    if (cli == NULL) {
        perror("ERRO AO ALOCAR CLINICA");
        exit(EXIT_FAILURE);
    }

    cli->medicos = NULL;
    cli->pacientes = NULL;
    cli->secretarios = NULL;
    cli->consultas = NULL;
    cli->filaImpressao = criaFila();
    return cli;
}

void CadastraPacienteClinica(tClinica* clinica, FILE* pathBanco) {
    if (clinica) {
        printf("#################### CADASTRO PACIENTE #######################\n");
        tAgente* paciente = LeAgente();

        // Checa se tem cpf repetido
        if (TemCPFIgualClinica(clinica, ObtemCPFAgente(paciente), PACIENTE)) {
            LiberaAgente(paciente);
            printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA\n");
            return;
        }
        // Se nao tiver, adiciona no array e registra no banco de dados
        clinica->pacientes = realloc(clinica->pacientes, (clinica->nPacientes + 1) * sizeof(tAgente*));
        clinica->pacientes[clinica->nPacientes] = paciente;
        clinica->nPacientes++;
        RegistraAgenteBancoDados(paciente, pathBanco);
        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("###############################################################");
        while (getchar() != '\n')
            ;
    }
}

void CadastraMedicoClinica(tClinica* clinica, FILE* Banco) {
    if (clinica) {
        tMedico* medico = LeMedico();

        if (TemCPFIgualClinica(clinica, ObtemCPFMedico(medico), MEDICO)) {
            LiberaMedico(medico);
            printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA\n");
            return;
        }

        clinica->medicos = realloc(clinica->medicos, (clinica->nMedicos + 1) * sizeof(tMedico*));
        clinica->medicos[clinica->nMedicos] = medico;

        clinica->nMedicos++;
        SalvaMedico(Banco, medico);
    }
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("###############################################################\n");
    while (getchar() != '\n')
        ;
}

void CadastraSecretarioClinica(tClinica* clinica, FILE* banco) {
    if (clinica) {
        tSecretario* secretario;

        if (clinica->nSecretarios == 0) {
            secretario = LePrimeiroSecretario();
        } else {
            secretario = LeSecretario();
        }

        // Checagem de CPF
        if (TemCPFIgualClinica(clinica, ObtemCPFSecretario(secretario), SECRETARIO)) {
            LiberaSecretario(secretario);
            printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA\n");
            return;
        }
        if (clinica->nSecretarios) {
            printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
            while (getchar() != '\n')
                ;
        }

        SalvaSecretario(banco, secretario);

        clinica->secretarios = realloc(clinica->secretarios, (clinica->nSecretarios + 1) * sizeof(tSecretario*));
        clinica->secretarios[clinica->nSecretarios] = secretario;
        clinica->nSecretarios++;
    }
}

int TemCPFIgualClinica(tClinica* clinica, char* cpf, int cargo) {
    //
    if (cargo == SECRETARIO) {
        for (size_t i = 0; i < clinica->nSecretarios; i++) {
            if (strcmp(cpf, ObtemCPFSecretario(clinica->secretarios[i])) == 0) {
                return 1;
            }
        }
    }

    if (cargo == MEDICO) {
        for (size_t i = 0; i < clinica->nMedicos; i++) {
            if (strcmp(cpf, ObtemCPFMedico(clinica->medicos[i])) == 0) {
                return 1;
            }
        }
    }

    if (cargo == PACIENTE) {
        for (size_t i = 0; i < clinica->nPacientes; i++) {
            if (strcmp(cpf, ObtemCPFAgente(clinica->pacientes[i])) == 0) {
                return 1;
            }
        }
    }

    return 0;
}

void DesalocaClinica(tClinica* clinica) {
    if (clinica) {
        if (clinica->pacientes != NULL) {
            printf("entrou pra liberar pacientes \n");
            for (size_t i = 0; i < clinica->nPacientes; i++) {
                if (clinica->pacientes[i]) {
                    printf("Liberando Paciente %s\n", ObtemNomeAgente(clinica->pacientes[i]));
                    LiberaAgente(clinica->pacientes[i]);
                }
            }
            free(clinica->pacientes);
        }
        printf("PACIENTES LIBERADOS\n");

        if (clinica->medicos != NULL) {
            printf("entrou pra liberar medicos \n");
            for (size_t i = 0; i < clinica->nMedicos; i++) {
                if (clinica->medicos[i]) {
                    printf("Liberando MEDICO %s\n", ObtemNomeMedico(clinica->medicos[i]));
                    LiberaMedico(clinica->medicos[i]);
                }
            }
            free(clinica->medicos);
        }
        printf("MEDICOS LIBERADOS\n");

        if (clinica->secretarios != NULL) {
            printf("entrou pra liberar SECRETARIOS \n");
            for (size_t i = 0; i < clinica->nSecretarios; i++) {
                if (clinica->secretarios[i]) {
                    printf("Liberando SECRETARIO %s\n", ObtemNomeSecretario(clinica->secretarios[i]));
                    LiberaSecretario(clinica->secretarios[i]);
                }
            }
            if (clinica->secretarios) free(clinica->secretarios);
        }
        printf("SECRETARIOS LIBERADOS\n");

        if (clinica->filaImpressao) {
            desalocaFila(clinica->filaImpressao);
        }
        if (clinica->consultas) {
            for (size_t i = 0; i < clinica->nConsultas; i++) {
                if (clinica->consultas[i]) {
                    DesalocaConsulta(clinica->consultas[i]);
                }
            }
            if (clinica->consultas) free(clinica->consultas);
        }

        if (clinica) free(clinica);
        printf("CHEGOU AQUI4\n");
    }
}

void SalvaMedicosClinica(tClinica* clinica, FILE* bancoMedicos) {
    fwrite(&clinica->nMedicos, sizeof(int), 1, bancoMedicos);

    for (size_t i = 0; i < clinica->nMedicos; i++) {
        SalvaMedico(bancoMedicos, clinica->medicos[i]);
    }
}

/*void SalvaPacientesClinica(tClinica* clinica, FILE* bancoPacientes) {
    // Itera sobre cada paciente e o salva no arquivo
    for (int i = 0; i < clinica->nPacientes; i++) {
        RegistraAgenteBancoDados(clinica->pacientes[i], bancoPacientes);
    }
} */

void SalvaSecretariosClinica(tClinica* clinica, FILE* bancoSecretarios) {
    // Itera sobre cada paciente e o salva no arquivo
    for (int i = 0; i < clinica->nSecretarios; i++) {
        SalvaSecretario(bancoSecretarios, clinica->secretarios[i]);
    }
}

int ObtemNMEdicosClinica(tClinica* c) {
    return c->nMedicos;
}

int ChecaLoginClinica(tClinica* c, char* nome, char* cpf, char* crm) {
    // SE PRECISAR RETORNAR O SECRETARIO NO FUTURO, CRIE UMA VARIAVEL NA MAIN E MANDE O ENDEREÇO PRA CA
    //  ASSIM CONSEGUE RETORNAR O VALOR LA PRA FORA E USAR, E AQUI RETORNA O SECRETARIO ENCONTRADO;
    char login[100], senha[100];
    printf("######################## ACESSO MINI-SADE #####################\n");
    printf("DIGITE SEU LOGIN: ");
    scanf("%[^\n]", &login);
    while (getchar() != '\n')
        ;
    printf("login eh  %s\n", login);
    printf("DIGITE SUA SENHA: ");
    scanf("%[^\n]", &senha);
    while (getchar() != '\n')
        ;
    printf("senha eh: %s", senha);

    // Roda todos os secretarios ate achar um login igual

    //  printf("LOGIN DO SECRETARIO ANALISADO EH :%s\n",ObtemLoginSecretario(c->secretarios[0]));

    // printf("NUMERO DE SECRETARIOS DA CLINICA EH %d\n",c->nSecretarios);

    for (size_t i = 0; i < c->nSecretarios; i++) {
        printf("LOGIN EH :%s\n", login);
        if (strcmp(login, ObtemLoginSecretario(c->secretarios[i])) == 0) {
            // Verifica se a senha eh igual
            if (strcmp(senha, ObtemSenhaSecretario(c->secretarios[i])) == 0) {
                if (EhAdminSecretario(c->secretarios[i])) {
                    *nome = '\0';

                    strcpy(cpf, ObtemCPFSecretario(c->secretarios[i]));

                    *crm = '\0';
                    return 1;
                } else {
                    *nome = '\0';
                    strcpy(cpf, ObtemCPFSecretario(c->secretarios[i]));

                    *crm = '\0';
                    return 2;
                }
            }
        }
    }

    // Roda todos os medicos ate achar um login igual
    for (size_t i = 0; i < c->nMedicos; i++) {
        if (strcmp(login, ObtemLoginMedico(c->medicos[i])) == 0) {
            // Verifica se a senha eh igual
            if (strcmp(senha, ObtemSenhaMedico(c->medicos[i])) == 0) {
                strcpy(nome, ObtemNomeMedico(c->medicos[i]));
                strcpy(cpf, ObtemCPFMedico(c->medicos[i]));
                strcpy(crm, ObtemCRMMedico(c->medicos[i]));
                return 3;
            }
        }
    }

    // Caso nao achou ninguém
    printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
    return 0;
}

int temNomeIgualPacientesClinica(tClinica* c, char* nome) {
    for (size_t i = 0; i < c->nPacientes; i++) {
        if (strcmp(ObtemNomeAgente(c->pacientes[i]), nome) == 0) {
            return 1;
        }
    }
    return 0;
}

void BuscaPacientesClinica(tClinica* clinica) {
    printf("#################### BUSCAR PACIENTES #######################\n");
    printf("NOME DO PACIENTE: ");
    char nomeBuscado[101];
    scanf("%[^\n]", nomeBuscado);
    while (getchar() != '\n')
        ;

    if (temNomeIgualPacientesClinica(clinica, nomeBuscado)) {
        printf("PACIENTES ENCONTRADOS \n");

        tLista* l = criaLista(nomeBuscado, clinica->pacientes, clinica->nPacientes);

        imprimeNaTelaLista(l);

        printf("ESCOLHA UMA OPCAO:\n");
        printf("\t(1) ENVIAR LISTA PARA IMPRESSAO");
        printf("\t(2) RETORNAR AO MENU PRINCIPAL");
        int opt;
        scanf("%d", &opt);
        while (getchar() != '\n')
            ;
        if (opt == 1) {
            insereDocumentoFila(clinica->filaImpressao, l, imprimeNaTelaLista, imprimeEmArquivoLista, desalocaLista);
            printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
            printf("############################################################\n");
            while (getchar() != '\n')
                return;
        } else if (opt == 2) {
            desalocaLista(l);
        }
        printf("############################################################\n");
    } else {
        printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        while (getchar() != '\n')
            ;
    }
}

void ExibeMenuFilaClinica(tClinica* clinica, char* path) {
    int opt = 0;

    do {
        printf("################ FILA DE IMPRESSAO MEDICA ##################\n");
        printf("ESCOLHA UMA OPCAO:\n");
        printf("\t(1) EXECUTAR FILA DE IMPRESSAO\n");
        printf("\t(2) RETORNAR AO MENU PRINCIPAL\n");
        printf("############################################################");

        scanf("%d", &opt);
        while (getchar() != '\n')
            ;

        if (opt == 2) {
            return;
        }
        if (opt == 1) {
            printf("################ FILA DE IMPRESSAO MEDICA ##################\n");
            printf("EXECUTANDO FILA DE IMPRESSAO:\n");
            imprimeFila(clinica->filaImpressao, path);

            printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU ANTERIOR\n");
            printf("############################################################\n");
            while (getchar() != '\n')
                ;
        }
    } while (opt != 2);
}

void GeraRelatorioGeral(tClinica* clinica) {
    int atendidos = 0, sumIdades = 0, masc = 0, fem = 0, outros = 0, sumTamLesoes = 0, totalLesoes = 0, cirurgias = 0, crioterapia = 0;

    for (size_t i = 0; i < clinica->nPacientes; i++) {
        if (!FoiContadoPaciente(clinica->pacientes[i])) {
            ContaPaciente(clinica->pacientes[i]);

            sumIdades += ObtemIdadePaciente(clinica->pacientes[i]);

            char* sexoCidadao = ObtemGeneroAgente(clinica->pacientes[i]);
            if (strcmp(sexoCidadao, "MASCULINO") == 0) {
                masc++;
            } else if (strcmp(sexoCidadao, "FEMININO") == 0) {
                fem++;
            } else if (strcmp(sexoCidadao, "OUTROS") == 0) {
                outros++;
            }
        }
        int tmp = 0;

        for (size_t k = 0; k < clinica->nConsultas; k++) {
            if (strcmp(ObtemCPFAgente(clinica->pacientes[i]), ObtemCPFAgente(ObtemPacienteConsulta(clinica->consultas[k]))) == 0) {
                tmp++;
                if (tmp == 1) {
                    atendidos++;
                }
            }
        }
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------------

    for (size_t i = 0; i < clinica->nConsultas; i++) {
        totalLesoes += ObtemNLesoesConsulta(clinica->consultas[i]);
        sumTamLesoes += ObtemTamanhoLesoes(clinica->consultas[i]);
        crioterapia += ObtemTotalCrioterapias(clinica->consultas[i]);
        cirurgias += ObtemTotalCirurgias(clinica->consultas[i]);

        int n = 0;

        /* if (!TemConsultaComMesmoPaciente(clinica->consultas, clinica->consultas[i], clinica->nConsultas)) {
             if (tamVet == 0) {
                 tamVet++;
                 vetorCPF = malloc(tamVet * sizeof(char*));
                 vetorCPF[tamVet - 1] = malloc(strlen(ObtemCPFAgente(ObtemPacienteConsulta(clinica->consultas[i]))) + 1);
                 strcpy(vetorCPF[tamVet - 1] , ObtemCPFAgente(ObtemPacienteConsulta(clinica->consultas[i])));
                 atendidos++;
             }

             for (size_t k = 0; k < tamVet; k++) {
                 if (strcmp(vetorCPF[k], ObtemCPFAgente(ObtemPacienteConsulta(clinica->consultas[i]))) == 0) {  // se eh igual a outro cpf
                     continue;
                 } else {  // senao
                     tamVet++;
                     vetorCPF = realloc(vetorCPF, tamVet * sizeof(char*));
                     vetorCPF[tamVet - 1] = malloc(strlen(ObtemCPFAgente(ObtemPacienteConsulta(clinica->consultas[i]))) + 1);
                     strcpy(vetorCPF[tamVet - 1], (ObtemPacienteConsulta(clinica->consultas[i])));
                 }
             }
         }*/
    }

    tRelatorio* rel = criaRelatorio(sumIdades, clinica->nConsultas, masc, fem, outros, totalLesoes, sumTamLesoes, cirurgias, crioterapia, atendidos, clinica->nPacientes);

    imprimeNaTelaRelatorio(rel);

    printf("SELECIONE UMA OPCAO: \n");
    printf("\t (1) ENVIAR PARA LISTA DE IMPRESAO\n");
    printf("\t (2) RETORNAR AO MENU PRINCIPAL \n");
    int opt = 0;
    scanf("%d", &opt);
    while (getchar() != '\n')
        ;
    if (opt == 1) {
        insereDocumentoFila(clinica->filaImpressao, rel, imprimeNaTelaRelatorio, imprimeEmArquivoRelatorio, desalocaRelatorio);
        printf("DOCUMENTO ENVIADO PARA LISTA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU INICIAL\n");
        printf("#################################\n");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("#################################\n");
}
