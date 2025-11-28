#ifndef OPCOES_H
#define OPCOES_H

#include "analise.h" // Certifique-se que as structs StatLetra e AnaliseFrequencia estão aqui

// Opção 1: Estado Atual 
// (Adicionado o parâmetro AnaliseFrequencia para igualar à implementação)
void executar_opcao_1_estado(const char *texto_cifrado, StatLetra stats[26], AnaliseFrequencia Frequencia[26], int contador);

// Opção 2: Análise de Frequência
void executar_opcao_2_frequencia(StatLetra stats[26]);

// Opção 3 e 4: (Placeholders)
void executar_opcao_3_busca_exata();
void executar_opcao_4_busca_aprox();

// Opção 5: Alterar Chave
// (O nome aqui deve ser igual ao da implementação)
void executar_opcao_5_alterar(AnaliseFrequencia Frequencia[26]);

// Opção 6: Exportar
void executar_opcao_6_exportar(const char *texto_cifrado, AnaliseFrequencia Frequencia[26]);

#endif