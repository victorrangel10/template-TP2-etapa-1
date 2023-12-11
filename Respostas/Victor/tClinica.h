#ifndef _TCLINICA_H_
#define _TCLINICA_H_

#define SECRETARIO 1
#define MEDICO 2
#define PACIENTE 3

#include "tAgente.h"
#include "tMedico.h"
#include "tSecretario.h"
#include "tFila.h"
#include "tConsulta.h"
#include "tLista.h"
#include "tRelatorio.h"

typedef struct tClinica tClinica;

void RealizaConsultaClinica(tClinica* clinica, FILE* banco, char* nomeAtendente, char* cpfAtendente, char* crmAtendente);

void SalvaClinicaBinario(tClinica* clinica, FILE* bancoCLINICA);

tClinica* RecuperaClinicaBinario(FILE* bancoCLINICA, FILE* bancoMEDICOS, FILE* bancoPACIENTES, FILE* bancoLESOES, FILE* bancoSECRETARIOS, FILE* bancoCONSULTAS);

void RecuperaSecretariosClinica(tClinica* clinica, FILE* banco);

void RecuperaMedicosClinica(tClinica* clinica, FILE* bancoMedicos);

void RecuperaPacientesClinica(tClinica* clinica, FILE* bancoPaciente);

tClinica* CriaClinica();

void CadastraPacienteClinica(tClinica* clinica, FILE* pathBanco);

void CadastraMedicoClinica(tClinica* clinica, FILE* Banco);

void CadastraSecretarioClinica(tClinica* clinica, FILE* banco);

int TemCPFIgualClinica(tClinica* clinica, char* cpf, int cargo);

void DesalocaClinica(tClinica* clinica);

void SalvaMedicosClinica(tClinica* clinica, FILE* bancoMedicos);

void SalvaSecretariosClinica(tClinica* clinica, FILE* bancoSecretarios);

int ObtemNMEdicosClinica(tClinica* c);

int ChecaLoginClinica(tClinica* c, char* nome, char* cpf, char* crm);

void GeraMenu(int tipoUsuario);

void BuscaPacientesClinica(tClinica* clinica);

void GeraRelatorioGeral(tClinica* clinica);

void ExibeMenuFilaClinica(tClinica* clinica, char* path);

#endif
