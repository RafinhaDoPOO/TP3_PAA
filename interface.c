#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"

// Cores ANSI


void interface_analise_opcao_1(const char *texto_cifrado,  StatLetra stats[26],    AnaliseFrequencia Frequencia[26], int contador){
    char Alfabeto[26] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    printf(CYAN_NEON"\n______________________TEXTO CRIPTOGRAFADO___________________________\n");
    printf(WHITE_NEON"%s\n\n", texto_cifrado);
    printf(CYAN_NEON"______________________________________________________________________\n\n" RESET);

    // --- CORREÇÃO NA EXIBIÇÃO DA CHAVE ---
    printf(LIMA"_______________________CHAVE SUGERIDA__________________\n");
    printf(LIMA"| CIFRADO: "RESET);
    for (int i = 0; i < 26; i++) printf(WHITE_NEON "%c ", Alfabeto[i]); // Linha de cima: A..Z (Alfabeto Cifrado)
    printf(LIMA" |\n"RESET);

    printf(LIMA"| CLARO:   "RESET);
    for (int i = 0; i < 26; i++) {
        char substituta = '_';
        // Procura qual letra CLARA corresponde a letra CIFRADA (Alfabeto[i]) atual
        for (int j = 0; j < contador; j++) {
            if (Frequencia[j].letraFrequencia == Alfabeto[i]) { // Se a letra frequente for a letra atual do loop
                substituta = Frequencia[j].letraalfabeto;       // Mostra a letra sugerida (A, E, O...)
                break;
            }
        }
        printf(WHITE_NEON"%c ", substituta);
    }
    printf(LIMA" |\n"RESET);
    printf(LIMA"|______________________________________________________|\n"RESET);
    printf("\n");

    // --- CORREÇÃO NA DECIFRAGEM DO TEXTO ---
    printf(CYAN_NEON"_______________________TEXTO PARCIALMENTE DECIFRADO_____________________\n");

    for (int i = 0; texto_cifrado[i] != '\0'; i++) {
        char c = texto_cifrado[i];

        if (isalpha(c)) {
            char up = toupper(c);
            char resultado = c;
            int encontrado = 0;

            for (int j = 0; j < contador; j++) {
                // CORREÇÃO CRÍTICA AQUI:
                // Compara a letra do texto cifrado (up) com a letra que foi detectada na analise (letraFrequencia)
                if (Frequencia[j].letraFrequencia == up) {
                    resultado = Frequencia[j].letraalfabeto; // Substitui pela letra clara (A, B, C...)
                    encontrado = 1;
                    break;
                }
            }

            if (encontrado) {
                printf(LIMA "%c" RESET, resultado);
            } else {
                printf(WHITE_NEON"%c"RESET, c);
            }
        } else {
            printf(WHITE_NEON"%c"RESET, c);
        }
    }
    printf("\n");
    printf(CYAN_NEON"________________________________________________________\n"RESET);
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
printf(CYAN_NEON "=========================================================================================\n");
printf(CYAN_NEON "|                                                            __.oo.                      |\n");
printf(CYAN_NEON "|                                    _.u[[/;:,.         .odMMMMMM''                      |\n") ;
printf(CYAN_NEON "|                                 .o888UU[[[/;:-.. .o@P^    MMM^                         |\n");
printf(CYAN_NEON "|                                oN88888UU[[[/;::-..       dP^                           |\n");
printf(CYAN_NEON "|                               dNMMNN888UU[[[/;:--..  .o@P^                             |\n");
printf(CYAN_NEON "|                              ,MMMMMMN888UU[[/;::-...o@P^                               |\n");
printf(CYAN_NEON "|                              NNMMMNN888UU[[[/~.o@P^.                                   |\n");
printf(CYAN_NEON "|                              888888888UU[[[/o@^-...                                    |\n");
printf(CYAN_NEON "|                             oI8888UU[[[/o@P^:--...                                     |\n");
printf(CYAN_NEON "|                          .@^  YUU[[[/o@^;::---...                                      |\n");
printf(CYAN_NEON "|                        oMP     ^/o@p^;:::---...                                        |\n");
printf(CYAN_NEON "|                     .dMMM    .o@^ ^;::---....                                          |\n");
printf(CYAN_NEON "|                    dMMMMMMM@^ '      '^^^^                                             |\n");
printf(CYAN_NEON "|                    YMMMUP^                                                             |\n");
printf(CYAN_NEON "=========================================================================================\n");
printf(WHITE_NEON "                                               Tp3 - Projeto e Analise de Algoritmos\n\n" RESET);

printf(YELLOW_NEON "Novo Objetivo: Utilize a criptoanalise para decifrar a profecia!\n" RESET);
}

void interface_menu_principal(const char *conteudo, StatLetra stats[26], AnaliseFrequencia Frequencia[26]) {
    int opcao;
    int contadordefrequencia = 26;


    if (opcao == 1){
        
    }

    do {
        printf("\n");
        printf(WHITE_NEON"_______________________________________________________\n");
        printf(WHITE_NEON"|" CYAN_NEON"                 MENU DE CRIPTOANALISE               "WHITE_NEON"|\n");                   
        printf(WHITE_NEON"|" CYAN_NEON"[1] Apresentar estado atual                          "WHITE_NEON"|\n");                         
        printf(WHITE_NEON"|" CYAN_NEON"[2] Analise de frequencia                            "WHITE_NEON"|\n");                          
        printf(WHITE_NEON"|" CYAN_NEON"[3] Busca exata (Padrao no texto criptografado)      "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[4] Busca aproximada (Shift-And no parcial)          "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[5] Alterar chave                                    "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[6] Exportar e Sair                                  "WHITE_NEON"|\n");
        printf(WHITE_NEON"|_____________________________________________________|\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                interface_analise_opcao_1(conteudo, stats, Frequencia, contadordefrequencia);
                contadordefrequencia++;
                break;

            case 2:
                interfaceopcao2(stats);
                break;

            case 3://iago ta fazendo
                printf("Ainda não foi implementado\n");
                break;

            case 4://iago ta fazendo
                printf("Ainda não foi implementado\n");
                break;

            case 5:
                printf("Ainda não foi implementado\n");
                break;

            case 6:
             printf(WHITE_NEON "Exportando resultado e saindo...\n" RESET);
                  //implementar o exportar resultado
               
                return;
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}
