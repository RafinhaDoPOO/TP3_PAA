#include <stdio.h>
#include <ctype.h>
#include "analise.h"

void executar_analise_frequencia(const char *texto_cifrado) {

    StatLetra stats[26];

    // 1. Inicializar (A-Z)
    for (int i = 0; i < 26; i++) {
        stats[i].letra = 'A' + i;
        stats[i].contagem = 0;
        stats[i].frequencia = 0.0;
    }

    int total = 0;

    // 2. Contar ocorrências
    for (int i = 0; texto_cifrado[i] != '\0'; i++) {
        char c = texto_cifrado[i];

        if (isalpha(c)) {
            c = toupper(c);
            stats[c - 'A'].contagem++;
            total++;
        }
    }

    // 3. Calcular frequências
    for (int i = 0; i < 26; i++) {
        if (total > 0)
            stats[i].frequencia = (stats[i].contagem * 100.0f) / total;
    }

    // 4. Ordenar array stats por contagem (decrescente)
    for (int i = 0; i < 26 - 1; i++) {
        for (int j = 0; j < 26 - i - 1; j++) {
            if (stats[j].contagem < stats[j+1].contagem) {
                StatLetra tmp = stats[j];
                stats[j] = stats[j+1];
                stats[j+1] = tmp;
            }
        }
    }
    // 5. Imprimir resultados
    printf("Letra,  Cont.,  Freq.\n");

    for (int i = 0; i < 26; i++) {
        if (stats[i].contagem > 0) {
            printf("%c%12d%8.2f%%\n",
               stats[i].letra,
               stats[i].contagem,
               stats[i].frequencia);
        }
    }

}
/*
void chute_baseado_frequencia(StatLetra stats[26], const char *texto_cifrado) {
    const float freq_portugues[26] = {
        14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40,
        0.02, 2.78, 4.74, 5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34,
        4.63, 1.67, 0.01, 0.21, 0.01, 0.47
    };

    // 1. Descobrir a letra mais frequente do texto cifrado
    int idx_mais_frequente = 0;
    for (int i = 1; i < 26; i++) {
        if (stats[i].contagem > stats[idx_mais_frequente].contagem)
            idx_mais_frequente = i;
    }

    char letra_cifrada = stats[idx_mais_frequente].letra;

    // Letra mais frequente do português (A)
    char letra_portugues = 'A';

    // 2. Calcular deslocamento X = C - P
    int X = ( (letra_cifrada - letra_portugues) + 26 ) % 26;

    printf("\n===== CHUTE BASEADO EM FREQUÊNCIA =====\n");
    printf("Letra mais frequente no texto cifrado : %c\n", letra_cifrada);
    printf("Letra mais frequente no português     : A\n");
    printf("Chute de deslocamento X = %d\n\n", X);

    printf("===== MAPA DE SUBSTITUIÇÕES =====\n");
    printf("Cifrado -> Claro\n");

    char mapa[26];

    for (int i = 0; i < 26; i++) {
        char cifrada = 'A' + i;
        char clara   = 'A' + ((i - X + 26) % 26);
        mapa[i] = clara;
        printf("%c -> %c\n", cifrada, clara);
    }

    printf("\n===== TEXTO PARCIALMENTE DECIFRADO =====\n");

    for (int i = 0; texto_cifrado[i] != '\0'; i++) {
        char c = texto_cifrado[i];
        if (c >= 'A' && c <= 'Z') {
            char dec = mapa[c - 'A'];
            printf("%c", dec);
        }
        else
            printf("%c", c);
    }

    printf("\n========================================\n");
}
*/
// INTERFACE CRIADA APENAS PARA TESTE DE MESA
void interface_analise_de_frequencia(){
char caminho[256];
    printf("Digite o nome do arquivo criptografado: ");
    scanf("%255s", caminho);

    // Ler conteúdo do arquivo (função já existente)
    char *texto_cifrado = ler_arquivo_texto(caminho);

    if (!texto_cifrado) {
        printf("Erro ao carregar o arquivo.\n");
        return 1;
    }

    printf("\n=== Texto criptografado carregado ===\n%s\n\n", texto_cifrado);

    printf("=== Executando análise de frequência ===\n\n");
    executar_analise_frequencia(texto_cifrado);

    free(texto_cifrado);
}