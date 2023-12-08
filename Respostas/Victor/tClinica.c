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
};

void RealizaConsultaClinica(tClinica* clinica, FILE* banco, char* nomeAtendente, char* cpfAtendente, char* crmAtendente) {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE:");
    char cpfPaciente[15];
    scanf("%[^\n]", cpfPaciente);
    while (getchar() != '\n')
        ;
    tAgente* paciente = BuscaPacienteClinica(clinica, cpfPaciente);

    if (paciente == NULL) {
        printf("PACIENTE SEM CADASTRO\n\n");
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n") /
            printf("##########################################################");
        scanf("%*c");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("---\n");
    printf("-NOME:%s\n", ObtemNomeAgente(paciente));
    printf("-DATA DE NASCIMENTO:%s", ObtemDataNascimentoAgente(paciente));
    printf("---\n");

    tConsulta* consulta = criaConsulta(crmAtendente, nomeAtendente, paciente);

    clinica->consultas = realloc(clinica->nConsultas, (clinica->nConsultas + 1) * sizeof(tConsulta*));

    clinica->consultas[clinica->nConsultas] = consulta;

    clinica->nConsultas++;

    RealizaConsulta(consulta, clinica->filaImpressao);
}

void SalvaClinicaBinario(tClinica* clinica, FILE* bancoCLINICA) {
    if (clinica) {
        fwrite(clinica, sizeof(tClinica), 1, bancoCLINICA);

        fwrite(&clinica->nPacientes, sizeof(int), 1, bancoCLINICA);

        fwrite(&clinica->nMedicos, sizeof(int), 1, bancoCLINICA);

        fwrite(&clinica->nSecretarios, sizeof(int), 1, bancoCLINICA);

        fwrite(&clinica->nConsultas, sizeof(int), 1, bancoCLINICA);
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

    fread(&c->nPacientes, sizeof(int), 1, bancoCLINICA);

    fread(&c->nMedicos, sizeof(int), 1, bancoCLINICA);

    fread(&c->nSecretarios, sizeof(int), 1, bancoCLINICA);

    fread(&c->nConsultas, sizeof(int), 1, bancoCLINICA);

    // Recuperando os pacientes
    c->pacientes = malloc(c->nPacientes * sizeof(tAgente*));  // criando espaco para o vetor de agentes
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

    return c;
}

void RecuperaSecretariosClinica(tClinica* clinica, FILE* banco) {
    // Itera sobre cada paciente e os recupera do arquivo
    for (size_t i = 0; i < clinica->nPacientes; i++) {
        clinica->secretarios[i] = RecuperaSecretario(banco);
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

    return cli;
}

void CadastraPacienteClinica(tClinica* clinica, FILE* pathBanco) {
    if (clinica) {
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

        // printf("CHEGOU\n");
        clinica->medicos = realloc(clinica->medicos, (clinica->nMedicos + 1) * sizeof(tMedico*));
        clinica->medicos[clinica->nMedicos] = medico;
        //   printf("CHEGOU2\n");
        clinica->nMedicos++;
        SalvaMedico(Banco, medico);
        //  printf("CHEGOU3\n");
    }
}

void CadastraSecretarioClinica(tClinica* clinica, FILE* banco) {
    if (clinica) {
        tSecretario* secretario = LeSecretario();

        // Checagem de CPF
        if (TemCPFIgualClinica(clinica, ObtemCPFSecretario(secretario), SECRETARIO)) {
            LiberaSecretario(secretario);
            printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA\n");
            return;
        }

        clinica->secretarios = realloc(clinica->secretarios, (clinica->nSecretarios + 1) * sizeof(tSecretario*));
        clinica->secretarios[clinica->nSecretarios] = secretario;
        clinica->nSecretarios++;
        SalvaSecretario(banco, secretario);
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
            for (size_t i = 0; i < clinica->nPacientes; i++) {
                if (clinica->pacientes[i]) LiberaAgente(clinica->pacientes[i]);
            }
            free(clinica->pacientes);
        }
        printf("CHEGOU AQUI1\n");
        if (clinica->medicos != NULL) {
            for (size_t i = 0; i < clinica->nMedicos; i++) {
                if (clinica->medicos[i]) LiberaMedico(clinica->medicos[i]);
            }
            free(clinica->medicos);
        }
        printf("CHEGOU AQUI2\n");

        if (clinica->secretarios != NULL) {
            for (size_t i = 0; i < clinica->nSecretarios; i++) {
                if (clinica->secretarios[i]) LiberaSecretario(clinica->secretarios[i]);
            }
            if (clinica->secretarios) free(clinica->secretarios);
        }
        printf("CHEGOU AQUI3\n");
        //  if (clinica->filaImpressao) {
        //   desalocaFila(clinica->filaImpressao);
        //  }
        if (clinica->filaImpressao) {
            desalocaFila(clinica->filaImpressao);
        }
        if (clinica->consultas) {
            for (size_t i = 0; i < clinica->nConsultas; i++) {
                DesalocaConsulta(clinica->consultas[i]);
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
    scanf("%[%^\n]]\n", login);
    printf("login eh> %s\n", login);
    printf("DIGITE SUA SENHA: ");
    while (getchar() != '\n')
        ;
    scanf("%[^\n]%*c", senha);
    printf("senha eh: %s", senha);

    // Roda todos os secretarios ate achar um login igual
    for (size_t i = 0; i < c->nSecretarios; i++) {
        if (strcmp(login, ObtemLoginSecretario(c->secretarios[i])) == 0) {
            // Verifica se a senha eh igual
            if (strcmp(senha, ObtemSenhaSecretario(c->secretarios[i])) == 0) {
                if (EhAdminSecretario(c->secretarios[i])) {
                    *nome = ObtemNomeSecretario(c->secretarios[i]);

                    *cpf = ObtemCPFSecretario(c->secretarios[i]);

                    *crm = NULL;
                    return 1;
                } else {
                    *nome = ObtemNomeSecretario(c->secretarios[i]);

                    *cpf = ObtemCPFSecretario(c->secretarios[i]);

                    *crm = NULL;
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
                *nome = ObtemNomeMedico(c->medicos[i]);
                *cpf = ObtemCPFMedico(c->medicos[i]);
                *crm = ObtemCRMMedico(c->medicos[i]);
                return 3;
            }
        }
    }

    // Caso nao achou ninguém
    printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
    return 0;
}

void GeraMenu(int tipoUsuario) {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");

    if (tipoUsuario == 1) {  // Para admin
        printf("(1) CADASTRAR SECRETARIO\n");
        printf("(2) CADASTRAR MEDICO\n");
        printf("(3) CADASTRAR PACIENTE\n");
        printf("(4) REALIZAR CONSULTA\n");
        printf("(5) BUSCAR PACIENTES\n");
        printf("(6) RELATORIO GERAL\n");
        printf("(7) FILA DE IMPRESSAO\n");
        printf("(8) FINALIZAR O PROGRAMA\n");
    } else if (tipoUsuario == 2) {  // Para user
        printf("(2) CADASTRAR MEDICO\n");
        printf("(3) CADASTRAR PACIENTE\n");
        printf("(5) BUSCAR PACIENTES\n");
        printf("(6) RELATORIO GERAL\n");
        printf("(7) FILA DE IMPRESSAO\n");
        printf("(8) FINALIZAR O PROGRAMA\n");
    } else if (tipoUsuario == 3) {  // Para medico
        printf("(4) REALIZAR CONSULTA\n");
        printf("(5) BUSCAR PACIENTES\n");
        printf("(8) FINALIZAR O PROGRAMA\n");
    }

    printf("###############################################################\n");
}

int temNomeIgualPacientesClinica(tClinica * c,char * nome){
    for (size_t i = 0; i < c->nPacientes; i++)
    {
        if (strcmp(ObtemNomeAgente(c->pacientes[i]),nome)==0)
        {
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
        if (opt == 2) {
            insereDocumentoFila(clinica->filaImpressao, l, imprimeNaTelaLista, imprimeEmArquivoLista, desalocaLista);
        }
        return;
    }
}