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
    // 1. Inicializa 'opcao' para garantir que não comece com um valor aleatório
    int opcao = 0; 
    int contadordefrequencia = 0; 
    
    // Ponteiro para a struct chave principal (Frequencia[0])
    AnaliseFrequencia *freq_principal = &Frequencia[0]; 

    do {
        printf("\n");
        printf(WHITE_NEON"_______________________________________________________\n");
        printf(WHITE_NEON"|" CYAN_NEON"          MENU DE CRIPTOANALISE              "WHITE_NEON"|\n");       
        printf(WHITE_NEON"|" CYAN_NEON"[1] Apresentar estado atual                         "WHITE_NEON"|\n");       
        printf(WHITE_NEON"|" CYAN_NEON"[2] Analise de frequencia                         "WHITE_NEON"|\n");        
        printf(WHITE_NEON"|" CYAN_NEON"[3] Busca exata (Padrao no texto criptografado)   "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[4] Busca aproximada (Shift-And no parcial)       "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[5] Alterar chave                                 "WHITE_NEON"|\n");
        printf(WHITE_NEON"|" CYAN_NEON"[6] Exportar e Sair                               "WHITE_NEON"|\n");
        printf(WHITE_NEON"|_____________________________________________________|\n");
        printf("Escolha: ");
        
        // Lê a opção
        if (scanf("%d", &opcao) != 1) {
            // Se a leitura falhar (ex: usuário digitar letra), define a opção como inválida
            opcao = -1;
        }
        
        // 🚀 CORREÇÃO ESSENCIAL: Limpar o buffer de entrada (stdin)
        // Isso remove o caractere '\n' após o Enter e impede loops indesejados.
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 

        switch (opcao) {
            case 1:
                // Passa o endereço da primeira struct do array para preencher a chave
                executar_opcao_1_estado(conteudo, freq_principal, stats, contadordefrequencia);
                contadordefrequencia++; 
                break;

            case 2:
                executar_opcao_2_frequencia(stats);
                break;

            case 3: 
                printf("Ainda não foi implementado (Busca Exata)\n");
                break;

            case 4: 
                printf("Ainda não foi implementado (Busca Aprox)\n");
                break;

            case 5:
                // Passa o array completo Frequencia[26] (necessário se o mapeamento for mais complexo que César)
                executar_opcao_5_alterar(Frequencia); 
                break;

            case 6:
                // Passa o endereço da struct principal para exportação
                executar_opcao_6_exportar(freq_principal);
                // A função de exportação já encerra a execução lógica.
                // Não precisa de 'printf("Exportando resultado...");' após a chamada.
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}