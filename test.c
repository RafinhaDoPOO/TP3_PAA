#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "analise.h"
#include "arq.h"

int main() {
    int opcao;
    int contadordefrequencia = 0;
    char nome_arquivo[256];
    printf("Digite o nome do seu arquivo : \n");
    scanf("%s", nome_arquivo);
    interface_leitura_arquivo(nome_arquivo);
    char destino[512];
    snprintf(destino, sizeof(destino), "Arquivos_textos_criptografados/%s",nome_arquivo);
    char *conteudo = ler_arquivo_texto(destino);
    StatLetra stats[26];
    AnaliseFrequencia Frequencia[26];


    executar_analise_frequencia(conteudo, stats);
    Ajustando_Frequencia(stats, Frequencia);
    // 3. Loop Principal 
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
            case 1: interface_analise(conteudo,stats,Frequencia,contadordefrequencia);
            contadordefrequencia++;
            break;
            case 2: ; break;
            case 3: printf("Ainda não foi implementado"); break;
            case 4: printf("Ainda não foi implementado"); break;
            case 5: printf("Ainda não foi implementado"); break;
            case 6: printf("Ainda não foi implementado"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (opcao != 6);

    return 0;
}