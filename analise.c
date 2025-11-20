#include <stdio.h>
#include <ctype.h>
#include "analise.h"

typedef struct {
    char letra;
    int contagem;
    float frequencia;
} StatLetra;

void executar_analise_frequencia(const char *texto_cifrado) {
    StatLetra stats[26];
    // 1. Inicializar stats (A-Z)
    // 2. Percorrer texto_cifrado e contar ocorrências
    // 3. Calcular percentuais (contagem / total_letras * 100)
    // 4. Ordenar array stats por contagem (Bubble Sort ou qsort)
    // 5. Imprimir tabela lado a lado com a tabela de referência do PDF [cite: 71]
}