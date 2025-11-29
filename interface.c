#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"
#include "opcoes.h"
#include "cores.h"

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


void interface_menu_principal(
    const char *conteudo,
    StatLetra stats[26],
    AnaliseFrequencia Frequencia[26],
    const char *conteudo_completo,
    StatLetra stats_completo[26],
    AnaliseFrequencia Frequencia_completo[26]
){
    int opcao = 0; 
    int opcaoanalise = 0;
    int contadordefrequencia = 0;
    int contadordefrequenciatotal = 26;

    // ponteiro para a struct principal
    AnaliseFrequencia *freq_principal = &Frequencia[0];
    AnaliseFrequencia *freq_total = &Frequencia_completo[0];

    do {
        printf("\n");
        printf(WHITE_NEON"_______________________________________________________\n");
        printf(WHITE_NEON"|" CYAN_NEON"          MENU DE CRIPTOANALISE                      "WHITE_NEON"|\n");       
        printf(WHITE_NEON"|" CYAN_NEON"[1] Apresentar estado atual                          "WHITE_NEON"|\n");       
        printf(WHITE_NEON"|" CYAN_NEON"[2] Analise de frequencia                            "WHITE_NEON"|\n");        
        printf(WHITE_NEON"|" CYAN_NEON"[3] Busca exata (Padrao no texto criptografado)      "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[4] Busca aproximada (Shift-And no parcial)          "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[5] Alterar chave                                    "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[6] Exportar e Sair                                  "WHITE_NEON"|\n");
        printf(WHITE_NEON"|_____________________________________________________|\n");
        printf("Escolha: ");

        // leitura segura
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }

        // limpa buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {

            case 1:
                executar_opcao_1_estado(conteudo, freq_principal, stats, contadordefrequencia);
                contadordefrequencia++;
                break;

            case 2:
                printf("\n");
                printf(WHITE_NEON"_______________________________________________________________\n");
                printf(WHITE_NEON"|" YELLOW_NEON"                          ANALISE                           "WHITE_NEON" |\n");       
                printf(WHITE_NEON"|" CYAN_NEON"[1] Apresentar analise de frequencia do arquivo escolhido    "   WHITE_NEON"|\n");       
                printf(WHITE_NEON"|" CYAN_NEON"[2] Apresentar analise de frequencia dos 12 arquivos juntos  "   WHITE_NEON"|\n");    
                printf(WHITE_NEON"|_____________________________________________________________|\n");
                scanf("%d", &opcaoanalise);
                if(opcaoanalise == 1){
                    executar_opcao_2_frequencia(stats);
                }    
                else if(opcaoanalise == 2){
                    executar_opcao_2_frequencia(stats_completo);
                }
                else {
                printf(RED_NEON"Opcao invalida. Tente novamente.\n"WHITE_NEON);
                  }
                
                break;

            case 3: 
                executar_opcao_3_busca_exata(conteudo);
                break;

            case 4: 

               executar_opcao_4_busca_aprox(Frequencia->texto_parcial);
                
                break;

            case 5:
                
                executar_opcao_5_alterar(Frequencia); 
                break;

            case 6:
                
                executar_opcao_6_exportar(freq_principal);
                
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}