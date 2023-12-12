#include "tConsulta.h"

struct tConsulta {
    char nomeAplicador[101];
    char CRM[15];
    tAgente* paciente;
    char data[15];
    int fumante, diabetes, alergia, cancer, tipoPele;
    tLesao** lesoes;
    int nlesoes;
};

tConsulta* criaConsulta(char* crm, char* nomeapl, tAgente* paciente) {
    tConsulta* c = calloc(1, sizeof(tConsulta));
    strcpy(c->nomeAplicador, nomeapl);
    strcpy(c->CRM, crm);
    c->paciente = ClonaAgente(paciente);
    c->lesoes = NULL;
    return c;
}

void DesalocaConsulta(tConsulta* c) {
    if (c) {
        if (c->nlesoes) {
            for (size_t i = 0; i < c->nlesoes; i++) {
                if (c->lesoes[i]) desalocaLesao(c->lesoes[i]);
            }
            free(c->lesoes);
        }
        LiberaAgente(c->paciente);
        free(c);
    }
}

void RealizaConsulta(tConsulta* consulta, tFila* fila, FILE* bancoConsulta, FILE* bancoLesoes) {
    // printf("- NOME: %s\n", ObtemNomeAgente(consulta->paciente));
    // printf("- DATA DE NASCIMENTO: %s\n", ObtemDataNascimentoAgente(consulta->paciente));
    printf("DATA DA CONSULTA:\n");

    scanf("%[^\n]%*c", consulta->data);
    printf("DATA EH %s\n", consulta->data);
    printf("POSSUI DIABETES:");
    scanf("%d", &consulta->diabetes);
    printf("FUMANTE:");
    scanf("%d", &consulta->fumante);
    printf("ALERGIA A MEDICAMENTO: ");
    scanf("%d", &consulta->alergia);
    printf("HISTORICO DE CANCER: ");
    scanf("%d", &consulta->cancer);
    printf("TIPO DE PELE: ");
    char tipoPele[5];
    printf("############################################################\n");
    while (getchar() != '\n')
        scanf("%[^\n]%*c", tipoPele);
    scanf("%s", tipoPele);

    if (strcmp(tipoPele, "I") == 0) {
        consulta->tipoPele = 1;
    } else if (strcmp(tipoPele, "II") == 0) {
        consulta->tipoPele = 2;
    } else if (strcmp(tipoPele, "III") == 0) {
        consulta->tipoPele = 3;
    } else if (strcmp(tipoPele, "IV") == 0) {
        consulta->tipoPele = 4;
    } else if (strcmp(tipoPele, "V") == 0) {
        consulta->tipoPele = 5;
    }
    printf("TIPO PELE EH %d\n", consulta->tipoPele);
    // ---------------------------------------------------------------------------------------------------------------

    int opt = 0;
    do {
        ImprimeMenuConsulta();
        scanf("%d", &opt);
        while (getchar() != '\n')
            ;
        switch (opt) {
            case 1:
                CadastraLesao(consulta);
                break;
            case 2:
                CadastraReceita(consulta, fila);
                break;
            case 3:
                GeraBiopsia(consulta, fila);
                break;
            case 4:
                GeraEncaminhamento(consulta, fila);
                break;
            case 5:
                SalvaConsultaBin(bancoConsulta, bancoLesoes, consulta);
                break;
        }
    } while (opt != 5);
}

tAgente* ObtemPacienteConsulta(tConsulta* c) {
    return c->paciente;
}

int ObtemNLesoesConsulta(tConsulta* c) {
    return c->nlesoes;
}

int ObtemTamanhoLesoes(tConsulta* consulta) {
    int tmp = 0;
    for (size_t i = 0; i < consulta->nlesoes; i++) {
        tmp += ObtemTamanhoLesao(consulta->lesoes[i]);
    }
    return tmp;
}

int ObtemTotalCrioterapias(tConsulta* consulta) {
    int tmp = 0;
    for (size_t i = 0; i < consulta->nlesoes; i++) {
        tmp += VaiPraCrioterapiaLesao(consulta->lesoes[i]);
    }
    return tmp;
}

int ObtemTotalCirurgias(tConsulta* consulta) {
    int tmp = 0;
    for (size_t i = 0; i < consulta->nlesoes; i++) {
        tmp += VaiPraCirurgiaLesao(consulta->lesoes[i]);
    }
    return tmp;
}

void ImprimeMenuConsulta() {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) CADASTRAR LESAO\n");
    printf("\t(2) GERAR RECEITA MEDICA\n");
    printf("\t(3) SOLICITACAO DE BIOPSIA\n");
    printf("\t(4) ENCAMINHAMENTO\n");
    printf("\t(5) ENCERRAR CONSULTA\n");
    printf("############################################################\n");
}

void CadastraLesao(tConsulta* consulta) {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("DIAGNOSTICO CLINICO: ");
    char diag[100], regiao[100];
    scanf("%[^\n]", diag);
    while (getchar() != '\n')
        ;
    printf("REGIAO DO CORPO: ");
    scanf("%[^\n]", regiao);
    while (getchar() != '\n')
        ;
    int tamanho = 0;
    printf("TAMANHO: ");
    scanf("%d", &tamanho);
    printf("ENVIAR PARA CIRURGIA: ");
    int cirurgia = 0;
    scanf("%d", &cirurgia);
    int crio = 0;
    printf("ENVIAR PARA CRIOTERAPIA: ");
    scanf("%d", &crio);

    printf("DIAG: %s \n REGIAO: %s\n", diag, regiao);
    char rotulo[6];
    sprintf(rotulo, "L%d", consulta->nlesoes + 1);
    while (getchar() != '\n')
        ;

    printf("ROTULO EH %s\n", rotulo);
    consulta->nlesoes++;

    consulta->lesoes = realloc(consulta->lesoes, consulta->nlesoes * sizeof(tLesao*));

    tLesao* les = criaLesao(rotulo, diag, regiao, tamanho, cirurgia, crio);

    consulta->lesoes[consulta->nlesoes - 1] = les;

    // SalvaLesao()

    printf("LESAO COM TAMANHO %d CADASTRADA\n", ObtemTamanhoLesao(consulta->lesoes[consulta->nlesoes - 1]));

    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    while (getchar() != '\n')
        ;
}

void CadastraReceita(tConsulta* consulta, tFila* fila) {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("RECEITA MEDICA:\n");

    char tipoUso[100], nome[100], instruc[100], tipomed[100];
    int qtd;
    printf("TIPO DE USO: ");
    scanf("%[^\n]", tipoUso);
    while (getchar() != '\n')
        ;
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]", nome);
    while (getchar() != '\n')
        ;
    printf("TIPO DE MEDICAMENTO: ");
    scanf("%[^\n]", tipomed);
    while (getchar() != '\n')
        ;
    printf("QUANTIDADE: ");
    scanf("%d", &qtd);
    while (getchar() != '\n')
        ;
    printf("INSTRUCOES DE USO: ");
    scanf("%[^\n]", instruc);
    while (getchar() != '\n')
        ;
    int type = 0;
    if (strcmp(tipoUso, "ORAL") == 0) {
        type = 0;
    } else if (strcmp(tipoUso, "TOPICO") == 0) {
        type = 1;
    }

    tReceita* r = criaReceita(ObtemNomeAgente(consulta->paciente), type, nome, tipomed, instruc, qtd, consulta->nomeAplicador, consulta->CRM, consulta->data);

    insereDocumentoFila(fila, r, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);

    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    while (getchar() != '\n')
        ;
}

int TemLesaoCirurgicaConsulta(tConsulta* c) {
    if (c) {
        for (size_t i = 0; i < c->nlesoes; i++) {
            if (VaiPraCirurgiaLesao(c->lesoes[i])) {
                return 1;
            }
        }
    }
    return 0;
}

void GeraBiopsia(tConsulta* consulta, tFila* fila) {
    printf("#################### CONSULTA MEDICA ######################\n");
    if (!TemLesaoCirurgicaConsulta(consulta)) {
        printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        while (getchar() != '\n')
            ;

        return;
    }

    tBiopsia* b = criaBiopsia(ObtemNomeAgente(consulta->paciente), consulta->nlesoes, ObtemCPFAgente(consulta->paciente), consulta->lesoes, consulta->nomeAplicador, consulta->CRM, consulta->data);
    insereDocumentoFila(fila, b, imprimeNaTelaBiospsia, imprimeEmArquivoBiopsia, desalocaBiopsia);
    printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    while (getchar() != '\n')
        ;
}

void GeraEncaminhamento(tConsulta* consulta, tFila* fila) {
    printf("#################### CONSULTA MEDICA ######################\n");
    printf("ENCAMINHAMENTO:\n");
    printf("ESPECIALIDADE ENCAMINHADA:");
    char especialidade[100], motivo[100];
    scanf("%[^\n]", especialidade);
    while (getchar() != '\n')
        ;
    printf("MOTIVO: ");
    scanf("%[^\n]", motivo);
    while (getchar() != '\n')
        ;

    tEncaminhamento* e = CriaEncaminhamento(ObtemNomeAgente(consulta->paciente), ObtemCPFAgente(consulta->paciente), especialidade, motivo, consulta->nomeAplicador, consulta->CRM, consulta->data);
    insereDocumentoFila(fila, e, ImprimeTelaEncaminhamento, ImprimeArquivoEncaminhamento, DesalocaEncaminhamento);

    printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    while (getchar() != '\n')
        ;
}

void SalvaLesoes(tLesao** lesoes, int num, FILE* bancoLesoes) {
    for (size_t i = 0; i < num; i++) {
        SalvaLesao(bancoLesoes, lesoes[i]);
    }
}

void RecuperaLesoesConsulta(FILE* banco, int num, tConsulta* consulta) {
    for (size_t i = 0; i < num; i++) {
        consulta->lesoes[i] = RecuperaLesao(banco);
    }
}

void SalvaConsultaBin(FILE* bancoConsulta, FILE* bancoLesoes, tConsulta* c) {
    if (c) {
        fwrite(c, sizeof(tConsulta), 1, bancoConsulta);

        RegistraAgenteBancoDados(c->paciente, bancoConsulta);

        SalvaLesoes(c->lesoes, c->nlesoes, bancoLesoes);

        /*fwrite(c->data, sizeof(char), strlen(c->data) + 1, bancoConsulta);

         fwrite(c->nomeAplicador, sizeof(char), strlen(c->nomeAplicador) + 1, bancoConsulta);

         fwrite(c->CRM, sizeof(char), strlen(c->CRM) + 1, bancoConsulta);*/
    }
}

tConsulta* RecuperaConsulta(FILE* bancoConsulta, FILE* bancoLesoes) {
    tConsulta* c = malloc(sizeof(tConsulta));

    fread(c, sizeof(tConsulta), 1, bancoConsulta);

    c->paciente = RecuperaAgenteBancoDados(bancoConsulta);

    c->lesoes = malloc(c->nlesoes * sizeof(tLesao*));

    RecuperaLesoesConsulta(bancoLesoes, c->nlesoes, c);

    /*  fread(c->data, sizeof(char), 15, bancoConsulta);

      fread(c->nomeAplicador, sizeof(char), 101, bancoConsulta);

      fread(c->CRM, sizeof(char), 15, bancoConsulta);*/

    return c;
}
char* ObtemGeneroPacienteConsulta(tConsulta* c) {
    return ObtemGeneroAgente(c->paciente);
}

int TemConsultaComMesmoPaciente(tConsulta** consultas, tConsulta* c, int n) {
    int tmp = 0;
    for (size_t i = 0; i < n; i++) {
        printf("ITERACAO %d\n", i);
        printf("VENDO SE %s EH IGUAL A %s", ObtemNomeAgente(ObtemPacienteConsulta(consultas[i])), ObtemNomeAgente(ObtemPacienteConsulta(c)));

        if (ObtemCPFAgente(ObtemPacienteConsulta(consultas[i])) == ObtemCPFAgente(ObtemPacienteConsulta(c)) && !JaFoiAtendidoPaciente(ObtemPacienteConsulta(consultas[i]))) {
            printf("SIM EH IGUAL\n");
            tmp++;
            AtendeuPaciente(ObtemPacienteConsulta(consultas[i]));
        }
    }
    return tmp > 1;
}