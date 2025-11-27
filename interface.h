#ifndef INTERFACE_H
#define INTERFACE_H

#include "analise.h"
#include "arq.h"
#include "cores.h"
void desenho_inicial();
void interface_analise_opcao_1(const char *texto_cifrado, StatLetra stats[26], AnaliseFrequencia Frequencia[26], int contador);

void interfaceopcao2(StatLetra stats[26]);

void interface_menu_principal(const char *conteudo,  StatLetra stats[26],  AnaliseFrequencia Frequencia[26]);

#endif
