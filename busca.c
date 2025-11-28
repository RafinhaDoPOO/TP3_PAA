#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> 
#include <stdint.h>
#include <stdlib.h>
#include "busca.h"


//Implementacao do algoritmo KMP, para buscar os casamentos exatos
// Referencia do algoritmo kmp https://www.geeksforgeeks.org/dsa/kmp-algorithm-for-pattern-searching/
int* computeLPSArray(const char* pat) {
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


int* buscar_exata(const char *texto, const char *padrao) {
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





// shiftand_kmismatch.c


// Imprime ocorrência
void report_occurrence(int pos) {
    printf("Match at position %d\n", pos);
}

/*
 Shift-And aproximado (k mismatches - apenas substituições).
 Requisitos: m (tamanho do padrão) <= 64.
 Parâmetros:
  - texto: string do texto
  - n: comprimento do texto
  - padrao: padrão
  - m: comprimento do padrão
  - k: número máximo de substituições permitidas
*/


void shiftand_kmismatch(const char *texto, int n, const char *padrao, int m, int k) {
    if (k < 0) return;
    if (m == 0) return;
    if (m > 64) {
        fprintf(stderr, "ERROR: padrão muito grande (m > 64). Use versão multi-word.\n");
        return;
    }

    // Construir B: para cada caractere c, B[c] tem bit i = 1 se padrao[i] == c
    uint64_t B[256];
    for (int i = 0; i < 256; ++i) B[i] = 0ULL;

    for (int i = 0; i < m; ++i) {
        unsigned char c = (unsigned char) padrao[i];
        B[c] |= (1ULL << i);
    }

    // D[e] representa bitmask de prefixes que casam com <= e mismatches
    // Inicialmente todos D[e] = 0
    uint64_t *D = (uint64_t*) calloc((size_t)(k + 1), sizeof(uint64_t));
    if (!D) { perror("calloc"); return; }

    // Mask para testar ocorrência completa: bit m-1
    uint64_t match_bit = 1ULL << (m - 1);

    for (int j = 0; j < n; ++j) {
        unsigned char tc = (unsigned char) texto[j];

        // Guardar antigos (precisamos do D[e-1] antigo ao atualizar D[e])
        uint64_t prev = D[0];

        // Atualiza D[0] (0 mismatches) — Shift-And clássico
        uint64_t newD0 = ((D[0] << 1) | 1ULL) & B[tc];
        D[0] = newD0;

        // Atualiza D[e] para e = 1..k
        for (int e = 1; e <= k; ++e) {
            uint64_t oldDe = D[e];         // D[e] antigo
            // calcular novo De usando:
            // 1) casar sem novo erro: ((De << 1) | 1) & B[tc]
            // 2) usar 1 substituição proveniente de prev (D[e-1] antigo) deslocado
            uint64_t part1 = ((oldDe << 1) | 1ULL) & B[tc];
            uint64_t part2 = (prev << 1);  // prev é D[e-1] antigo
            uint64_t newDe = part1 | part2;
            // atualizar prev para próxima iteração (prev <- oldDe)
            prev = oldDe;
            D[e] = newDe;
        }

        // Verifica ocorrência: algum D[e] tem bit (m-1) = 1 ?
        for (int e = 0; e <= k; ++e) {
            if (D[e] & match_bit) {
                int pos = j - m + 1;
                if (pos >= 0) report_occurrence(pos);
                break; // se queremos reportar apenas uma vez por posição
            }
        }
    }

    free(D);
}



