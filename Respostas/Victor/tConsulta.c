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
    c->paciente = paciente;
    c->lesoes == NULL;
    return c;
}

void DesalocaConsulta(tConsulta* c) {
    if (c) {
        if (c->lesoes != NULL) {
            for (size_t i = 0; i < c->nlesoes; i++) {
                desalocaLesao(c->lesoes[i]);
            }
            free(c->lesoes);
        }
        free(c);
    }
}

void RealizaConsulta(tConsulta* consulta, tFila* fila) {
    printf("- NOME: %s\n", ObtemNomeAgente(consulta->paciente));
    printf("- DATA DE NASCIMENTO: %s\n", ObtemDataNascimentoAgente(consulta->paciente));
    printf("DATA DA CONSULTA:\n");
    char dataCon[10];
    scanf("%[^\n]%*c", dataCon);
    printf("DATA EH %s\n", dataCon);
    printf("POSSUI DIABETES:");
    scanf("%d", &consulta->diabetes);
    printf("FUMANTE:");
    scanf("%d", &consulta->fumante);
    printf("ALERGIA A MEDICAMENTO: ");
    scanf("%d", &consulta->alergia);
    printf("HISTORICO DE CANCER: ");
    scanf("%d%*[^\n]%*c", &consulta->cancer);
    printf("TIPO DE PELE: ");
    char tipoPele[5];
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
        scanf("%*[^\n]");
        scanf("%*c");
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
                return;
                break;
        }
    } while (opt != 5);
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
    consulta->nlesoes++;
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("DIAGNOSTICO CLINICO: ");
    char diag[100], regiao[100];
    scanf("%[^\n]%*c", diag);
    printf("REGIAO DO CORPO: ");
    scanf("%[^\n]%*c", regiao);
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
    sprintf(rotulo, "L%d", consulta->nlesoes);

    printf("ROTULO EH %s\n", rotulo);

    consulta->lesoes = realloc(consulta->lesoes, consulta->nlesoes * sizeof(tLesao*));

    tLesao* les = criaLesao(rotulo, diag, regiao, tamanho, cirurgia, crio);

    consulta->lesoes[consulta->nlesoes - 1] = les;

    // SalvaLesao()

    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%*c\n");
}

void CadastraReceita(tConsulta* consulta, tFila* fila) {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("RECEITA MEDICA:\n");

    char tipoUso[100], nome[100], instruc[100], tipomed[100];
    int qtd;
    printf("TIPO DE USO: ");
    scanf("%[^\n]%*c", tipoUso);
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]%*c", nome);
    printf("TIPO DE MEDICAMENTO: ");
    scanf("%[^\n]%*c", tipomed);
    printf("QUANTIDADE: ");
    scanf("%d%*c", &qtd);
    printf("INSTRUCOES DE USO: ");
    scanf("%[^\n]%*c", instruc);
    int type = 0;
    if (strcmp(tipoUso, "ORAL")) {
        type = 0;
    } else if (strcmp(tipoUso, "TOPICO")) {
        type = 1;
    }

    tReceita* r = criaReceita(ObtemNomeAgente(consulta->paciente), type, nome, tipomed, instruc, qtd, consulta->nomeAplicador, consulta->CRM, consulta->data);

    insereDocumentoFila(fila, r, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);

    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    while (getchar() != '\n')
        ;
}

void GeraBiopsia(tConsulta* consulta, tFila* fila) {
    printf("#################### CONSULTA MEDICA ######################\n");
    if (consulta->nlesoes == 0) {
        printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        scanf("%*[^\n]\n");
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
    scanf("%[^\-n]%*c", especialidade);
    printf("MOTIVO: ");
    scanf("%[^\n]%*c", motivo);

    tEncaminhamento* e = CriaEncaminhamento(ObtemNomeAgente(consulta->paciente), ObtemCPFAgente(consulta->paciente), especialidade, motivo, consulta->nomeAplicador, consulta->CRM, consulta->data);
    insereDocumentoFila(fila, e, ImprimeTelaEncaminhamento, ImprimeArquivoEncaminhamento, DesalocaEncaminhamento);
    printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    while (getchar() != '\n')
        ;
}

void SalvaConsultaBin(FILE* bancoConsulta, FILE* bancoLesoes, tConsulta* c) {
    if (c) {
        fwrite(c, sizeof(tConsulta), 1, bancoConsulta);

        RegistraAgenteBancoDados(bancoConsulta, c->paciente);

        fwrite(&c->nlesoes,sizeof(int),1,bancoConsulta);

        fwrite(c->lesoes, sizeof(tLesao*), c->nlesoes, bancoConsulta);

        SalvaLesoes(c->lesoes, c->nlesoes, bancoLesoes);

        fwrite(c->data, sizeof(char), strlen(c->data) + 1, bancoConsulta);

        fwrite(c->nomeAplicador, sizeof(char), strlen(c->nomeAplicador) + 1, bancoConsulta);

        fwrite(c->CRM, sizeof(char), strlen(c->CRM) + 1, bancoConsulta);
    }
}

void SalvaLesoes(tLesao** lesoes, int num, FILE* bancoLesoes) {
    fwrite(&num, sizeof(char), 1, bancoLesoes);
    for (size_t i = 0; i < num; i++) {
        SalvaLesao(bancoLesoes, lesoes[i]);
    }
}

void RecuperaLesoesConsulta(FILE* bancoConsulta, tConsulta* consulta) {
    fread(consulta, sizeof(tConsulta), 1, bancoConsulta);

    consulta->paciente = RecuperaAgenteBancoDados(bancoConsulta);

    fread(&consulta->nlesoes,)
}

void RecuperaConsulta() {
}