#ifndef _TMEDICO_H_
#define _TMEDICO_H_

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "tAgente.h"


typedef struct tMedico tMedico;

tMedico* LeMedico();

void SalvaMedico(FILE* banco, tMedico* medico);

tMedico* RecuperaMedico(FILE* banco);

void LiberaMedico(tMedico* m);

#endif
