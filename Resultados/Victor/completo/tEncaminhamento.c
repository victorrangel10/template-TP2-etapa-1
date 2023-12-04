#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tEncaminhamento.h"




struct tEncaminhamento
{
    char  nomePaciente[101];
    char  cpf[15];
    char  especialidade[51];
    char  motivo[301];
    char nomeMedico[101];
    char crm[13];
    char dataStr[11];
};



tEncaminhamento * CriaEncaminhamento(char * nomep,char * cpf, char * especialidade, char* motivo, char* nomedico, char* crm,char *data){

    tEncaminhamento* t = calloc(1,sizeof(tEncaminhamento));
    if (t==NULL)
    {
        exit(1);
    }

    strcpy(t->nomePaciente,nomep);
    strcpy(t->cpf,cpf);
    strcpy(t->especialidade,especialidade);
    strcpy(t->motivo,motivo);
    strcpy(t->nomeMedico,nomedico);
    strcpy(t->crm,crm);
    strcpy(t->dataStr,data);

    return t;
}

void DesalocaEncaminhamento(void * dado){
    if (dado!=NULL)
    {
       free(dado);
    }

}

void ImprimeTelaEncaminhamento (tEncaminhamento * e){

    if(e==NULL) return; 

    printf("PACIENTE:%s\n",e->nomePaciente);
    printf("CPF:%s\n",e->cpf);
    printf("\n");
    printf("MOTIVO:%s\n",e->motivo);
    printf("\n");
    printf("%s (%s)\n",e->nomeMedico,e->crm);
    printf("%s\n",e->dataStr);
    
}


void ImprimeArquivoEncaminhamento(tEncaminhamento* e, void* path){
 char dest[101];
 char * caminho = (char*) path;
 sprintf(dest,"%s/encaminhamento.txt",caminho);
 FILE * arq = fopen(dest,"w");

    fprintf(arq,"PACIENTE:%s\n",e->nomePaciente);
    fprintf(arq,"CPF:%s\n",e->cpf);
    fprintf(arq,"\n");
    fprintf(arq,"MOTIVO:%s\n",e->motivo);
    fprintf(arq,"\n");
    fprintf(arq,"%s (%s)\n",e->nomeMedico,e->crm);
    fprintf(arq,"%s\n",e->dataStr);
    
 fclose(arq);
}



