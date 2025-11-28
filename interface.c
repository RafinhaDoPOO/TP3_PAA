#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"
#include "opcoes.h"

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
    int contadordefrequencia = 0;


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

        switch (opcao) {
            case 1:
                // Agora os argumentos batem com o .h
                executar_opcao_1_estado(conteudo, stats, Frequencia, contadordefrequencia);
                contadordefrequencia++;
                break;

            case 2:
                executar_opcao_2_frequencia(stats);
                break;

            case 3: // Iago ta fazendo
                printf("Ainda não foi implementado (Busca Exata)\n");
                // executar_opcao_3_busca_exata();
                break;

            case 4: // Iago ta fazendo 
                printf("Ainda não foi implementado (Busca Aprox)\n");
                // executar_opcao_4_busca_aprox();
                break;

            case 5:
                // Nome corrigido para padronização
                executar_opcao_5_alterar(Frequencia);
                break;

            case 6:
                // Implementação simples da chamada para exportar
                printf(WHITE_NEON "Exportando resultado...\n" RESET);
                break;

            default:
                printf("Opcao invalida!\n");}
    } while (opcao != 6);
}
