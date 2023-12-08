#ifndef _TCLINICA_H_
#define _TCLINICA_H_

#include <stdio.h>
#include <stdlib.h>

#include "tAgente.h"
#include "tConsulta.h"
#include "tFila.h"
#include "tMedico.h"
#include "tSecretario.h"
typedef struct tClinica tClinica;

tClinica* CriaClinica();
void CadastraPacienteClinica(tClinica* clinica, FILE* pathBanco);
void CadastraMedicoClinica(tClinica* clinica, FILE* Banco);
void CadastraSecretarioClinica(tClinica* clinica, FILE* banco);
void LiberaClinica(tClinica* clinica);

void SalvaMedicosClinica(tClinica* clinica, FILE* bancoMedicos);

void RecuperaMedicosClinica(tClinica* clinica, FILE* bancoMedicos);

void SalvaPacientesClinica(tClinica* clinica, FILE* bancoPacientes);

void RecuperaPacientesClinica(tClinica* clinica, FILE* bancoPaciente);

void SalvaSecretariosClinica(tClinica* clinica, FILE* bancoSecretarios);

void RecuperaSecretariosClinica(tClinica* clinica, FILE* banco);

#endif