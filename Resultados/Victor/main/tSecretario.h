
#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_
#include <stdio.h>
typedef struct tSecretario tSecretario;


tSecretario* LeSecretario();

tSecretario* RecuperaSecretario(FILE* banco);

void SalvaSecretario(FILE* banco, tSecretario* secretario);

void LiberaSecretario(tSecretario* s);

#endif