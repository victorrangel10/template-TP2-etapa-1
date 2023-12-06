#include <stdio.h>
#include <stdlib.h>

#include "tAgente.h"
#include "tMedico.h"
#include "tSecretario.h"
#include "tFila.h"
#include "tDocumento.h"
#include "tConsulta.h"


tAgente * CadastraPaciente(){
    printf("#################### CADASTRO PACIENTE #######################\n");
    tAgente * a = LeAgente();
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("###############################################################");
    scanf("%*c");
    return a;
}


int main() {
    FILE* banco = fopen("teste.bin", "wb");

    tFila * fila = criaFila();

    tAgente * paciente = CadastraPaciente();

    tMedico * medico = LeMedico();

    tConsulta * consulta = criaConsulta(medico,paciente);
    RealizaConsulta(consulta,fila);
    printf("CHEGOU\n");
    DesalocaConsulta(consulta);

    printf("CHEGOU1\n");

    desalocaFila(fila);
       printf("CHEGOU2\n");

    fclose(banco);
    return 0;
}