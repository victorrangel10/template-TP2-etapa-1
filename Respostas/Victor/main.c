#include <stdio.h>
#include <stdlib.h>

#include "tAgente.h"
#include "tMedico.h"
#include "tSecretario.h"

/*void RealizaConsulta(tMedico* medico) {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: ");
    char cpf[15];
    scanf("%s", cpf);

    tAgente* paciente = VerificaCPFExistente(cpf);

    if (paciente == NULL) {
        printf("PACIENTE SEM CADASTRO\n\n");
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICAL\n");
        printf("############################################################");
        scanf("%[^\n]");
        scanf("%*c");
        return;
    }

    printf("- NOME: %s\n", ObtemNomeAgente(paciente));
    printf("- DATA DE NASCIMENTO: %s\n", ObtemDataNascimentoAgente(paciente));

    printf("DATA DA CONSULTA:\n");
    char dataCon[10];
    scanf("%s", dataCon);
    int diabetes, fumante, alergia, cancer;
    scanf("%d %d %d %d", &diabetes, &fumante, &alergia, &cancer);

    char tipoPele[5];
    scanf("%s", tipoPele);

    atualizaInformacoesPaciente(paciente, diabetes, fumante, alergia, cancer,
                                TransformaTipoPeleInteiro(tipoPele));

    int opt = 0;
    while (opt != 5) {
        ImprimeMenuConsulta();
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                CadastraLesao(medico, paciente);
                break;
            case 2:

                break;

            default:
                break;
        }
    }
}*/

int main() {
    FILE* banco = fopen("teste.bin", "wb");

    tSecretario* s = LeSecretario();

    SalvaSecretario(banco, s);

    LiberaSecretario(s);

    fclose(banco);
    return 0;
}