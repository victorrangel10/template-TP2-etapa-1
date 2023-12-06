
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

tClinica* CriaClinica() {
    tClinica* cli = calloc(1, sizeof(tClinica*));
    cli->medicos = NULL;
    cli->pacientes = NULL;
    cli->secretarios = NULL;
    cli->consultas = NULL;
    return cli;
}

void CadastraPacienteClinica(tClinica* clinica, FILE* pathBanco) {
    if (clinica) {
        /* code */

        tAgente* paciente = LeAgente();
        clinica->pacientes = realloc(clinica->pacientes, (clinica->nPacientes + 1) * sizeof(tAgente*));
        clinica->pacientes[clinica->nPacientes] = paciente;
        clinica->nPacientes++;
        RegistraAgenteBancoDados(paciente, pathBanco);
    }
}

void CadastraMedicoClinica(tClinica* clinica, FILE* Banco) {
    if (clinica) {
        tMedico* medico = LeMedico();
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
        /* code */

        tSecretario* secretario = LeSecretario();
        clinica->secretarios = realloc(clinica->secretarios, (clinica->nSecretarios + 1) * sizeof(tSecretario*));
        clinica->secretarios[clinica->nSecretarios] = secretario;
        clinica->nSecretarios++;
        SalvaSecretario(banco, secretario);
    }
}

void LiberaClinica(tClinica* clinica) {
    if (clinica) {
        /* code */

        printf("CHEGOU AQUI\n");
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
            free(clinica->secretarios);
        }
        printf("CHEGOU AQUI3\n");
        //  if (clinica->filaImpressao) {
        //   desalocaFila(clinica->filaImpressao);
        //  }
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


void RecuperaMedicosClinica(tClinica* clinica, FILE* bancoMedicos) {
    // Lê o número total de médicos
    fread(&clinica->nMedicos, sizeof(int), 1, bancoMedicos);

    // Aloca memória para a quantidade correta de médicos na clínica
    clinica->medicos = malloc(clinica->nMedicos * sizeof(tMedico*));
    if (clinica->medicos == NULL) {
        perror("Erro ao alocar memória para médicos");
        exit(EXIT_FAILURE);
    }

    // Itera sobre cada médico e os recupera do arquivo
    for (size_t i = 0; i < clinica->nMedicos; i++) {
        clinica->medicos[i] = RecuperaMedico(bancoMedicos);
    }
}


void SalvaPacientesClinica(tClinica* clinica,FILE* bancoPacientes) {
    // Salva o número total de pacientes
    fwrite(clinica->nPacientes, sizeof(int), 1, clinica);

    // Itera sobre cada paciente e o salva no arquivo
    for (int i = 0; i < clinica->nPacientes; i++) {
        RegistraAgenteBancoDados(clinica->pacientes[i],bancoPacientes);
    }
}


void RecuperaPacientesClinica(tClinica* clinica, FILE* bancoPaciente) {
    // Lê o número total de pacientes
    fread(&clinica->nPacientes, sizeof(int), 1, bancoPaciente);

    // Aloca memória para a quantidade correta de médicos na clínica
    clinica->pacientes = malloc(clinica->nPacientes * sizeof(tMedico*));
    if (clinica->pacientes == NULL) {
        perror("Erro ao alocar memória para pacientes");
        exit(EXIT_FAILURE);
    }

    // Itera sobre cada paciente e os recupera do arquivo
    for (size_t i = 0; i < clinica->nPacientes; i++) {
        clinica->pacientes[i] = RecuperaAgenteBancoDados(bancoPaciente);
    }
}


void SalvaSecretariosClinica(tClinica* clinica,FILE* bancoSecretarios) {
    // Salva o número total de pacientes
    fwrite(clinica->nSecretarios, sizeof(int), 1, clinica);

    // Itera sobre cada paciente e o salva no arquivo
    for (int i = 0; i < clinica->nSecretarios; i++) {
        SalvaSecretario(bancoSecretarios,clinica->secretarios[i]);
    }
}

void RecuperaSecretariosClinica(tClinica* clinica, FILE* banco) {
    // Lê o número total de pacientes
    fread(&clinica->nSecretarios, sizeof(int), 1, banco);

    // Aloca memória para a quantidade correta de médicos na clínica
    clinica->secretarios = malloc(clinica->nSecretarios * sizeof(tSecretario*));
    if (clinica->secretarios == NULL) {
        perror("Erro ao alocar memória para pacientes");
        exit(EXIT_FAILURE);
    }

    // Itera sobre cada paciente e os recupera do arquivo
    for (size_t i = 0; i < clinica->nPacientes; i++) {
        clinica->secretarios[i] = RecuperaSecretario(banco);
    }
}