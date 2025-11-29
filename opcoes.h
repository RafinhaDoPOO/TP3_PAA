#ifndef OPCOES_H
#define OPCOES_H

#include "analise.h"


void executar_opcao_1_estado(const char *texto_cifrado, AnaliseFrequencia *freq, StatLetra stats[26], int contador);

void executar_opcao_2_frequencia(StatLetra stats[26]);

void executar_opcao_3_busca_exata(const char *texto_cifrado);

void executar_opcao_4_busca_aprox(char *texto_cifrado);
void executar_opcao_5_alterar(AnaliseFrequencia *freq);
void executar_opcao_6_exportar(const AnaliseFrequencia *freq);

#endif
