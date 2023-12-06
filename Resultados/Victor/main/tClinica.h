#ifndef _TCLINICA_H_
#define _TCLINICA_H_


#include <stdio.h> 
#include <stdlib.h>
#include "tMedico.h"
#include "tAgente.h"
#include "tSecretario.h"
#include "tFila.h"
#include "tConsulta.h"
typedef struct tClinica tClinica;


tClinica * CriaClinica();
void CadastraPacienteClinica(tClinica * clinica,FILE* pathBanco);
void CadastraMedicoClinica(tClinica * clinica,FILE* Banco);
void CadastraSecretarioClinica(tClinica * clinica, FILE* banco);
void LiberaClinica(tClinica* clinica);

#endif