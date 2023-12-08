#include <stdio.h>
#include <stdlib.h>

#include "tAgente.h"
#include "tClinica.h"
#include "tConsulta.h"
#include "tDocumento.h"
#include "tFila.h"
#include "tMedico.h"
#include "tSecretario.h"

tAgente* CadastraPaciente() {
    printf("#################### CADASTRO PACIENTE #######################\n");
    tAgente* a = LeAgente();
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("###############################################################");
    scanf("%*c");
    return a;
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
        printf("(6) RELATORIO GERAL\n");
        printf("(7) FILA DE IMPRESSAO\n");
        printf("(8) FINALIZAR O PROGRAMA\n");
    }

    printf("###############################################################\n");
}

int verificaTam(FILE* arquivo) {
    if (arquivo == NULL) {
        return 0;  // Arquivo não aberto corretamente
    }

    fseek(arquivo, 0, SEEK_END);  // Move o indicador de posição para o final do arquivo

    long tamanho = ftell(arquivo);  // Obtém a posição atual, que é o tamanho do arquivo

    rewind(arquivo);
    if (tamanho == 0) {
        printf("O arquivo está vazio.\n");
        return 0;
    } else {
        printf("O arquivo não está vazio.\n");
        return 1;
    }
}

char* ObtemCaminhoBancodeDados() {
    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS:\n");
    char* caminho = malloc(150 * sizeof(char));
    printf("digite o caminho:");
    scanf("%s", caminho);
    while (getchar() != '\n')
        ;
    printf("caminho eh:%s\n", caminho);
    printf("################################################\n");
    return caminho;
}

int main(int argc, char* argv[]) {
    if (argc<2)
    {
        printf("Erro: favor informar diretorio para impresao de arquivos");
        return 0;
    }
    
    char* caminho = ObtemCaminhoBancodeDados();
    char arqSecretarios[200];
    char arqMedicos[200];
    char arqPacientes[200];
    char arqConsultas[200];
    char arqLesoes[200];
    char arqClinica[200];

    sprintf(arqMedicos, "%s/medicos.bin", caminho);
    sprintf(arqSecretarios, "%s/secretarios.bin", caminho);
    sprintf(arqPacientes, "%s/pacientes.bin", caminho);
    sprintf(arqConsultas, "%s/consultas.bin", caminho);
    sprintf(arqLesoes, "%s/lesoes.bin", caminho);
    sprintf(arqClinica, "%s/clinica.bin", caminho);

    FILE* bancoSecretarios = fopen(arqSecretarios, "a+b");
    FILE* bancoMedicos = fopen(arqMedicos, "a+b");
    FILE* bancoPacientes = fopen(arqPacientes, "a+b");
    FILE* bancoConsultas = fopen(arqConsultas, "a+b");
    FILE* bancoLesoes = fopen(arqLesoes, "a+b");
    FILE* bancoClinica = fopen(arqClinica, "a+b");

    free(caminho);

    int ehNecessarioLogin = 0;
    tClinica* clinica;

    // Verifica se há dados registrados no banco da clinica e faz load
    if (verificaTam(bancoClinica)) {
        clinica = RecuperaClinicaBinario(bancoClinica, bancoMedicos, bancoPacientes, bancoLesoes, bancoSecretarios, bancoConsultas);
        ehNecessarioLogin = 1;
    } else {
        clinica = CriaClinica();
        CadastraSecretarioClinica(clinica, bancoSecretarios);
    }

    // Checa informacoes de login e senha
    int cargo;
    char nomeUsuario[101];
    char cpfUsuario[15];
    char crmUsuario[15];

    if (ehNecessarioLogin) {
        cargo = ChecaLoginClinica(clinica, nomeUsuario, cpfUsuario, crmUsuario);
    } else {
        cargo = 1;
    }

    // Comeca o programa de fato
    int opt;
    do {
        GeraMenu(cargo);
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                CadastraSecretarioClinica(clinica, bancoSecretarios);
                break;
            case 2:
                CadastraMedicoClinica(clinica, bancoMedicos);
                break;
            case 3:
                CadastraPacienteClinica(clinica, bancoPacientes);
                break;
            case 4:
                RealizaConsultaClinica(clinica, bancoConsultas, nomeUsuario, cpfUsuario, crmUsuario);
                break;
            case 5:
                BuscaPacientesClinica(clinica);
                break;
            case 6:

                break;

            case 7:
                ExibeMenuFilaClinica(clinica,argv[1]);
            default:
                break;
        }
    } while (opt != 8);

    // Fecha tudo e salva no banco
    fclose(bancoClinica);
    bancoClinica = fopen(arqClinica, "wb");
    SalvaClinicaBinario(clinica, bancoClinica);

    fclose(bancoClinica);
    fclose(bancoSecretarios);
    fclose(bancoLesoes);
    fclose(bancoConsultas);
    fclose(bancoPacientes);
    fclose(bancoMedicos);

    DesalocaClinica(clinica);

    return 0;
}