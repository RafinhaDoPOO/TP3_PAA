#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "opcoes.h"
#include "cores.h" // Supondo que suas cores estejam aqui

// --- OPÇÃO 1 ---
// Assinatura agora inclui AnaliseFrequencia Frequencia[26]
void executar_opcao_1_estado(const char *texto_cifrado, StatLetra stats[26], AnaliseFrequencia Frequencia[26], int contador){
    
    char mais_comum_cifrada = stats[0].letra;
    char mais_comum_idioma = 'A'; 
    int deslocamento = (mais_comum_cifrada - mais_comum_idioma + 26) % 26;
    
    int letra_esta_visivel[256] = {0}; 

    for(int i = 0; i < contador && i < 26; i++) {
        unsigned char letra_atual = stats[i].letra;
        letra_esta_visivel[letra_atual] = 1; 
    }

    char Alfabeto[26] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    printf(CYAN_NEON"\n______________________TEXTO CRIPTOGRAFADO___________________________\n");
    printf(WHITE_NEON"%s\n\n", texto_cifrado);
    
    printf(LIMA"_______________________CHAVE PARCIAL___________________\n");
    printf(LIMA"| "RESET);
    for (int i = 0; i < 26; i++) printf(WHITE_NEON "%c ", Alfabeto[i]); 
    printf(LIMA" |\n"RESET);

    printf(LIMA"| "RESET);
    for (int i = 0; i < 26; i++) {
        char letra_cifrada_atual = Alfabeto[i];
        
        if (letra_esta_visivel[(unsigned char)letra_cifrada_atual]) {
            char decifrada = ((letra_cifrada_atual - 'A' - deslocamento + 26) % 26) + 'A';
            printf(WHITE_NEON"%c ", decifrada);
        } else {
            printf(WHITE_NEON"_ ");
        }
    }
    printf(LIMA" |\n"RESET);
    printf(LIMA"|______________________________________________________|\n"RESET);
    printf("\n");

    printf(CYAN_NEON"_______________________TEXTO PROGRESSIVO__________________________\n");

    for (int i = 0; texto_cifrado[i] != '\0'; i++) {
        char c = texto_cifrado[i];

        if (isalpha(c)) {
            char maiuscula = toupper(c);
            
            if (letra_esta_visivel[(unsigned char)maiuscula]) {
                char base = isupper(c) ? 'A' : 'a';
                char decifrado = ((c - base - deslocamento + 26) % 26) + base;
                printf(LIMA "%c" RESET, decifrado);
            } else {
                printf(WHITE_NEON"%c"RESET, c);
            }
        } else {
            printf(WHITE_NEON"%c"RESET, c);
        }
    }
    printf("\n");
    printf(CYAN_NEON"__________________________________________________________________\n"RESET);
    printf("\n\n");
}

// --- OPÇÃO 2 ---
void executar_opcao_2_frequencia(StatLetra stats[26]) {
    printf("\n");
    printf(CYAN_NEON"____________________________\n");
    printf(CYAN_NEON"| " LIMA "ANALISE DE FREQUENCIA:"CYAN_NEON"  |\n");
    printf(CYAN_NEON"| "LIMA "Letra" CYAN_NEON"|"LIMA "Contagem" CYAN_NEON"|"LIMA "Frequencia (%%)"CYAN_NEON" |\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 26; i++) {
        if (stats[i].contagem > 0) {
            printf(CYAN_NEON "|" WHITE_NEON" %c "  CYAN_NEON "|"  WHITE_NEON  " %d "  CYAN_NEON   "|"  WHITE_NEON " %.2f " CYAN_NEON"|\n"
                    , stats[i].letra, stats[i].contagem, stats[i].frequencia);
        }
    }
}

// --- OPÇÃO 5 ---
// NOME CORRIGIDO: de interface_alterar_chave para executar_opcao_5_alterar
void executar_opcao_5_alterar(AnaliseFrequencia Frequencia[26]) {
    char original, cifrada;

    printf(CYAN_NEON "\n______________________ALTERAR CHAVE MANUALMENTE______________________\n" RESET);
    printf(WHITE_NEON "Informe a letra original, seguida da letra para a qual foi mapeada:\n");
    
    printf(WHITE_NEON "\nDIGITE: " RESET);
    
    if (scanf(" %c %c", &original, &cifrada) != 2) {
        while (getchar() != '\n'); 
        printf(RED_NEON "Erro na leitura. Tente novamente.\n" RESET);
        return;
    }

    original = toupper(original);
    cifrada = toupper(cifrada);

    if (!isalpha(original) || !isalpha(cifrada)) {
        printf(RED_NEON "Erro: Por favor, insira apenas letras validas.\n" RESET);
        return;
    }

    int idx_original = -1;       
    int idx_dono_anterior = -1;  

    for (int i = 0; i < 26; i++) {
        if (Frequencia[i].letraalfabeto == original) {
            idx_original = i;
        }
        if (Frequencia[i].letraFrequencia == cifrada) {
            idx_dono_anterior = i;
        }
    }

    if (idx_original != -1) {
        char cifrada_velha = Frequencia[idx_original].letraFrequencia;

        if (idx_dono_anterior != -1 && idx_dono_anterior != idx_original) {
            Frequencia[idx_original].letraFrequencia = cifrada;
            Frequencia[idx_dono_anterior].letraFrequencia = cifrada_velha; 
            
            printf(YELLOW_NEON "\n[Aviso] Houve uma troca para manter a consistência:\n");
            printf("A letra '%c' cedeu o mapeamento '%c' e ficou com '%c'.\n", 
                   Frequencia[idx_dono_anterior].letraalfabeto, cifrada, cifrada_velha);
        } else {
            Frequencia[idx_original].letraFrequencia = cifrada;
        }

        printf(LIMA "\nRegistrado com sucesso: %c -> %c\n" RESET, original, cifrada);
    } else {
        printf(RED_NEON "Erro: Letra original nao encontrada na tabela.\n" RESET);
    }
    printf(CYAN_NEON "_____________________________________________________________________\n" RESET);
}