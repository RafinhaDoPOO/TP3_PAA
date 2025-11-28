#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> 
//#include "busca.h"


//Implementacao do algoritmo KMP, para buscar os casamentos exatos
// Referencia do algoritmo kmp https://www.geeksforgeeks.org/dsa/kmp-algorithm-for-pattern-searching/
int* computeLPSArray(char* pat) {
    int m = strlen(pat);
    int *lps = malloc(m * sizeof(int));

    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}


int* buscar_exata(char *texto, char *padrao) {
    int n = strlen(texto);
    int m = strlen(padrao);

    int *lps = computeLPSArray(padrao);

    int capacidade = 10;
    int *resultado = malloc(capacidade * sizeof(int));
    int count = 0;

    int i = 0, j = 0;

    while (i < n) {
        if (texto[i] == padrao[j]) {
            i++; j++;
        }

        if (j == m) {
            if (count >= capacidade) {
                capacidade *= 2;
                resultado = realloc(resultado, capacidade * sizeof(int));
            }
            resultado[count++] = i - j;
            j = lps[j - 1];
        }

        else if (i < n && texto[i] != padrao[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    resultado[count] = -1; // marca fim
    free(lps);
    return resultado;
}





void buscar_aproximada_shift_and(const char *texto_parcial, const char *padrao, int tolerancia) {
    // Implementação do Shift-And Aproximado
    
    // 1. Pré-processamento: Criar máscaras de bits para cada caractere do padrão.
    //    long mascaras[256]; 
    
    // 2. Busca:
    //    Manter conjunto de estados R (bits).
    //    Iterar pelo texto_parcial atualizando R.
    //    Lembrar que a busca é no texto PARCIAL (mistura de cifrado/decifrado).
    
    printf("Resultados da busca aproximada para '%s' com erro %d:\n", padrao, tolerancia);
    // Loop de busca aqui...
}

