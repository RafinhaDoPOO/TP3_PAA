#ifndef BUSCA_H
#define BUSCA_H

#include "cores.h"

int* buscar_exata(const char *texto, const char *padrao);
void shiftand_kmismatch(const char *texto, int n, const char *padrao, int m, int k);

#endif