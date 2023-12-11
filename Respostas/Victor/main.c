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
    } else {
        printf("TIPO DE USUARIO ERRADO \n");
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

char* ObtemCaminhoBancodeDados(char* agrv) {
    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS:\n");
    char* caminho = malloc(150 * sizeof(char));
    printf("digite o caminho:");
    char aux[150];
    scanf("%s", aux);
    while (getchar() != '\n')
        ;

    sprintf(caminho, "%s/%s", agrv, aux);
    printf("caminho eh:%s\n", caminho);
    printf("################################################\n");
    return caminho;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Erro: favor informar diretorio para impresao de arquivos");
        return 0;
    }

    char* caminho = ObtemCaminhoBancodeDados(argv[1]);
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

    tClinica* clinica;

    // Verifica se há dados registrados no banco da clinica e faz load
    if (verificaTam(bancoClinica)) {
        rewind(bancoClinica);
        rewind(bancoSecretarios);
        rewind(bancoLesoes);
        rewind(bancoMedicos);
        rewind(bancoPacientes);
        rewind(bancoConsultas);

        clinica = RecuperaClinicaBinario(bancoClinica, bancoMedicos, bancoPacientes, bancoLesoes, bancoSecretarios, bancoConsultas);
    } else {
        clinica = CriaClinica();
        CadastraSecretarioClinica(clinica, bancoSecretarios);
    }

    // Checa informacoes de login e senha
    int cargo = 0;
    char nomeUsuario[101];
    char cpfUsuario[15];
    char crmUsuario[15];

    while (cargo == 0) {
        cargo = ChecaLoginClinica(clinica, nomeUsuario, cpfUsuario, crmUsuario);
    }

    printf("CARGO EH %d\n", cargo);
    // Comeca o programa de fato
    int opt = 0;
    do {
        GeraMenu(cargo);

        scanf("%d", &opt);
        while (getchar() != '\n')
            ;
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
                GeraRelatorioGeral(clinica);
                break;
            case 7:
                ExibeMenuFilaClinica(clinica, argv[1]);
            case 8:
                break;
        }

        printf("opt eh: %d", opt);
    } while (opt != 8);

    // Fecha tudo e salva no banco
    fclose(bancoClinica);

    bancoClinica = fopen(arqClinica, "wb");
    SalvaClinicaBinario(clinica, bancoClinica);

    DesalocaClinica(clinica);

    fclose(bancoClinica);
    fclose(bancoSecretarios);
    fclose(bancoLesoes);
    fclose(bancoConsultas);
    fclose(bancoPacientes);
    fclose(bancoMedicos);

    return 0;
}