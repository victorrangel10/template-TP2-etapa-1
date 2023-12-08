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

int verificaTam(const char * caminho_do_arquivo) {
    // Caminho para o arquivo binário
   
    // Abre o arquivo em modo de leitura binária
    FILE *arquivo = fopen(caminho_do_arquivo, "rb");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Move o ponteiro para o final do arquivo
    fseek(arquivo, 0, SEEK_END);

    // Obtém a posição atual do ponteiro
    long tamanho_do_arquivo = ftell(arquivo);


    rewind(arquivo);

   
    fclose(arquivo);

    return tamanho_do_arquivo;
}

int main() {
    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS:\n");
    char caminho[200];
    scanf("%s\n", caminho);
    printf("################################################\n");
    char arqSecretarios[200];
    char arqMedicos[200];
    char arqPacientes[200];
    char arqConsultas[200];
    char arqLesoes[200];

    sprintf(arqMedicos, "%s/medicos.bin", caminho);
    sprintf(arqSecretarios, "%s/secretarios.bin", caminho);
    sprintf(arqPacientes, "%s/pacientes.bin", caminho);
    sprintf(arqConsultas, "%s/consultas.bin", caminho);
    sprintf(arqLesoes, "%s/lesoes.bin", caminho);

    FILE* bancoSecretarios = fopen(arqSecretarios,"a+b");
    FILE* bancoMedicos = fopen(arqMedicos,"a+b");

    FILE* bancoPacientes = fopen(arqPacientes,"a+b");
    FILE* bancoConsultas = fopen(arqConsultas,"a+b");
    FILE* bancoLesoes = fopen(arqLesoes,"a+b");

    tClinica * clinica = CriaClinica();

    int ehNecessarioLogin=0;
    if (!verificaTam(arqMedicos) && !verificaTam(arqSecretarios))
    {
        
        CadastraSecretarioClinica(clinica,bancoSecretarios);

    }else{
        ehNecessarioLogin=1;
        if (verificaTam(arqMedicos))
        {
            RecuperaMedicosClinica(clinica,bancoMedicos);
        }if (verificaTam(arqSecretarios))
        {
            RecuperaSecretariosClinica(clinica,bancoSecretarios);
        }if (verificaTam(arqPacientes))
        {
            RecuperaPacientesClinica(clinica,bancoPacientes);
        }
        
        
    }
    int cargo=0;
    if (ehNecessarioLogin)
    {
        cargo=ChecaLogin(clinica);
    }

    RodaPrograma(cargo);

    DesalocaClinica(clinica);
    fclose(bancoSecretarios);
    fclose(bancoLesoes);
    fclose(bancoConsultas);
    fclose(bancoPacientes);
    fclose(bancoMedicos);

    return 0;

    
    
}