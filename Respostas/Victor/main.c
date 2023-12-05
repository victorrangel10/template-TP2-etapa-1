#include <stdio.h>
#include <stdlib.h>

#include "tAgente.h"
#include "tMedico.h"

int main() {
    FILE* banco = fopen("teste.bin", "wb");

    tMedico* a = LeMedico();

    SalvaMedico(banco,a);

    LiberaMedico(a);

    fclose(banco);
    return 0;
}