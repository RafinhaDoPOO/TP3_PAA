#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"

// Cores ANSI


void interface_analise_opcao_1(const char *texto_cifrado,
                               StatLetra stats[26],
                               AnaliseFrequencia Frequencia[26],
                               int contador)
{
    char Alfabeto[26] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    printf("\n=== Texto criptografado ===\n");
    printf("%s\n\n", texto_cifrado);

    printf("=== Chave ===\n");

    // imprime alfabeto
    for (int i = 0; i < 26; i++) {
        printf("%c ", Alfabeto[i]);
    }
    printf("\n");

    // imprime substituições
    for (int i = 0; i < 26; i++) {
        char substituta = '_';

        for (int j = 0; j < contador; j++) {
            if (Frequencia[j].letraalfabeto == Alfabeto[i]) {
                substituta = Frequencia[j].letraFrequencia;
                break;
            }
        }

        printf("%c ", substituta);
    }
    printf("\n");

    // decifra parcialmente
    printf("=== Texto parcialmente decifrado ===\n");

    for (int i = 0; texto_cifrado[i] != '\0'; i++) {
        char c = texto_cifrado[i];

        if (isalpha(c)) {
            char up = toupper(c);
            char resultado = c;
            int encontrado = 0;

            for (int j = 0; j < contador; j++) {
                if (Frequencia[j].letraalfabeto == up) {
                    resultado = Frequencia[j].letraFrequencia;
                    encontrado = 1;
                    break;
                }
            }

            if (encontrado) {
                printf(GREEN "%c" RESET, resultado);
            } else {
                printf("%c", c);
            }
        } else {
            printf("%c", c);
        }
    }

    printf("\n\n");
}

void interfaceopcao2(StatLetra stats[26]) {
    printf("Análise de Frequência:\n");
    printf("Letra | Contagem | Frequência (%%)\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 26; i++) {
        if (stats[i].contagem > 0) {
            printf("  %c   |    %d     |    %.2f\n",
                   stats[i].letra,
                   stats[i].contagem,
                   stats[i].frequencia);
        }
    }
}

void desenho_inicial(){
printf(BLUE_NEON "=========================================================================================\n");
printf(BLUE_NEON "|                                                            __.oo.                      |\n");
printf(BLUE_NEON "|                                    _.u[[/;:,.         .odMMMMMM''                      |\n") ;
printf(BLUE_NEON "|                                 .o888UU[[[/;:-.. .o@P^    MMM^                         |\n");
printf(BLUE_NEON "|                                oN88888UU[[[/;::-..       dP^                           |\n");
printf(BLUE_NEON "|                               dNMMNN888UU[[[/;:--..  .o@P^                             |\n");
printf(BLUE_NEON "|                              ,MMMMMMN888UU[[/;::-...o@P^                               |\n");
printf(BLUE_NEON "|                              NNMMMNN888UU[[[/~.o@P^.                                   |\n");
printf(BLUE_NEON "|                              888888888UU[[[/o@^-...                                    |\n");
printf(BLUE_NEON "|                             oI8888UU[[[/o@P^:--...                                     |\n");
printf(BLUE_NEON "|                          .@^  YUU[[[/o@^;::---...                                      |\n");
printf(BLUE_NEON "|                        oMP     ^/o@p^;:::---...                                        |\n");
printf(BLUE_NEON "|                     .dMMM    .o@^ ^;::---....                                          |\n");
printf(BLUE_NEON "|                    dMMMMMMM@^ '      '^^^^                                             |\n");
printf(BLUE_NEON "|                    YMMMUP^                                                             |\n");
printf(BLUE_NEON "=========================================================================================\n");
printf(WHITE_NEON "                                               Tp3 - Projeto e Analise de Algoritmos\n\n" RESET);

printf(YELLOW_NEON "Novo Objetivo: Utilize a criptoanalise para decifrar a profecia!\n" RESET);
}

void interface_menu_principal(const char *conteudo, StatLetra stats[26], AnaliseFrequencia Frequencia[26]) {
    int opcao;
    int contadordefrequencia = 0;



    do {
        printf("\n=== MENU DE CRIPTOANALISE ===\n");
        printf("1. Apresentar estado atual\n");
        printf("2. Analise de frequencia\n");
        printf("3. Busca exata (Padrao no texto criptografado)\n");
        printf("4. Busca aproximada (Shift-And no parcial)\n");
        printf("5. Alterar chave\n");
        printf("6. Exportar e Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                interface_analise_opcao_1(conteudo, stats, Frequencia, contadordefrequencia);
                contadordefrequencia++;
                break;

            case 2:
                interfaceopcao2(stats);
                break;

            case 3:
                printf("Ainda não foi implementado\n");
                break;

            case 4:
                printf("Ainda não foi implementado\n");
                break;

            case 5:
                printf("Ainda não foi implementado\n");
                break;

            case 6:
                printf("Ainda não foi implementado\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}
