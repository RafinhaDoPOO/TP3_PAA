#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"

void interface_analise_opcao_1(const char *texto_cifrado, StatLetra stats[26], AnaliseFrequencia Frequencia[26], int contador){
    
    // -------------------------------------------------------------------------
    // 1. CÁLCULO DO DESLOCAMENTO (A Lógica Matemática)
    // -------------------------------------------------------------------------
    // Vamos assumir que a letra mais frequente (stats[0]) é 'A'.
    // Mesmo que o contador seja baixo, precisamos desse cálculo fixo para que
    // a tradução seja coerente (matemática da Cifra de César).
    
    char mais_comum_cifrada = stats[0].letra;
    char mais_comum_idioma = 'A'; 
    int deslocamento = (mais_comum_cifrada - mais_comum_idioma + 26) % 26;

    // -------------------------------------------------------------------------
    // 2. DEFINIR QUAIS LETRAS SERÃO EXIBIDAS (A Lógica Visual)
    // -------------------------------------------------------------------------
    // Criamos um mapa para saber quais letras o usuário já "desbloqueou"
    // baseado no contador.
    int letra_esta_visivel[256] = {0}; // Zera tudo

    for(int i = 0; i < contador && i < 26; i++) {
        unsigned char letra_atual = stats[i].letra;
        letra_esta_visivel[letra_atual] = 1; 
        // Ex: Se 'X' é muito comum, marcamos que 'X' pode ser traduzido.
    }

    // -------------------------------------------------------------------------
    // 3. EXIBIÇÃO DA TABELA (CHAVE)
    // -------------------------------------------------------------------------
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
        
        // Só mostramos a tradução se esta letra estiver entre as 'contador' mais frequentes
        if (letra_esta_visivel[(unsigned char)letra_cifrada_atual]) {
            
            // Aplica a fórmula inversa para descobrir quem é a letra clara
            // LetraClara = (LetraCifrada - deslocamento)
            char decifrada = ((letra_cifrada_atual - 'A' - deslocamento + 26) % 26) + 'A';
            printf(WHITE_NEON"%c ", decifrada);
            
        } else {
            // Se ainda não chegamos nessa iteração, mostra oculto
            printf(WHITE_NEON"_ ");
        }
    }
    printf(LIMA" |\n"RESET);
    printf(LIMA"|______________________________________________________|\n"RESET);
    printf("\n");

    // -------------------------------------------------------------------------
    // 4. EXIBIÇÃO DO TEXTO (PARCIALMENTE DECIFRADO)
    // -------------------------------------------------------------------------
    printf(CYAN_NEON"_______________________TEXTO PROGRESSIVO__________________________\n");

    for (int i = 0; texto_cifrado[i] != '\0'; i++) {
        char c = texto_cifrado[i];

        if (isalpha(c)) {
            char maiuscula = toupper(c);
            
            // Verifica se essa letra já foi "liberada" pelo contador
            if (letra_esta_visivel[(unsigned char)maiuscula]) {
                
                char base = isupper(c) ? 'A' : 'a';
                // Aplica a decifragem matemática correta
                char decifrado = ((c - base - deslocamento + 26) % 26) + base;
                
                printf(LIMA "%c" RESET, decifrado);
            } else {
                // Se não foi liberada, mostra a letra original cifrada
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

void interfaceopcao2(StatLetra stats[26]) {
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

void interface_alterar_chave(AnaliseFrequencia Frequencia[26]) {
    char original, cifrada;

    printf(CYAN_NEON "\n______________________ALTERAR CHAVE MANUALMENTE______________________\n" RESET);
    printf(WHITE_NEON "Informe a letra original, seguida da letra para a qual foi mapeada:\n");
    
    
    printf(WHITE_NEON "\nDIGITE: " RESET);
    
    // O espaço antes de %c ignora pular linhas pendentes no buffer
    if (scanf(" %c %c", &original, &cifrada) != 2) {
        // Limpa buffer em caso de erro
        while (getchar() != '\n'); 
        printf(RED_NEON "Erro na leitura. Tente novamente.\n" RESET);
        return;
    }

    // Normaliza para maiúsculo
    original = toupper(original);
    cifrada = toupper(cifrada);

    if (!isalpha(original) || !isalpha(cifrada)) {
        printf(RED_NEON "Erro: Por favor, insira apenas letras validas.\n" RESET);
        return;
    }

    // --- Lógica de Troca (SWAP) ---
    // Precisamos encontrar os índices correspondentes para não duplicar mapeamentos
    int idx_original = -1;       // Onde está o 'A' (Original)
    int idx_dono_anterior = -1;  // Quem estava usando o 'X' (Cifrada) antes?

    for (int i = 0; i < 26; i++) {
        // Procura a posição da letra Original (ex: Onde está o 'A' na lista?)
        if (Frequencia[i].letraalfabeto == original) {
            idx_original = i;
        }
        // Procura se alguém JÁ está usando essa letra cifrada (ex: O 'E' já estava mapeado para 'X'?)
        if (Frequencia[i].letraFrequencia == cifrada) {
            idx_dono_anterior = i;
        }
    }

    // Executa a alteração
    if (idx_original != -1) {
        
        char cifrada_velha = Frequencia[idx_original].letraFrequencia;

        if (idx_dono_anterior != -1 && idx_dono_anterior != idx_original) {
            // SITUAÇÃO: A letra cifrada já pertencia a outra letra original. Vamos trocar.
            // Exemplo: 'A' apontava para 'J'. 'E' apontava para 'X'.
            // Usuário diz: "Quero A -> X".
            // Resultado: 'A' vira 'X'. 'E' ganha o 'J' (sobra da troca).
            
            Frequencia[idx_original].letraFrequencia = cifrada;      // A -> X
            Frequencia[idx_dono_anterior].letraFrequencia = cifrada_velha; // E -> J
            
            printf(YELLOW_NEON "\n[Aviso] Houve uma troca para manter a consistência:\n");
            printf("A letra '%c' cedeu o mapeamento '%c' e ficou com '%c'.\n", 
                   Frequencia[idx_dono_anterior].letraalfabeto, cifrada, cifrada_velha);
        } else {
            // SITUAÇÃO: Apenas atualiza (raro acontecer sem troca em tabela cheia 1-pra-1)
            Frequencia[idx_original].letraFrequencia = cifrada;
        }

        printf(LIMA "\nRegistrado com sucesso: %c -> %c\n" RESET, original, cifrada);
    } else {
        printf(RED_NEON "Erro: Letra original nao encontrada na tabela.\n" RESET);
    }
    printf(CYAN_NEON "_____________________________________________________________________\n" RESET);
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
                interface_alterar_chave(Frequencia);
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
