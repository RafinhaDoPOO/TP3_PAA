#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "arq.h"
#include "analise.h"

int main() {
    desenho_inicial();
    char nome_arquivo[256];
    printf(WHITE_NEON "Digite o nome do seu arquivo ex(mydei.txt): "RESET);
    scanf("%s", nome_arquivo);
    
    interface_leitura_arquivo(nome_arquivo);

    char destino[512];
    snprintf(destino, sizeof(destino),
             "Arquivos_textos_criptografados/%s", nome_arquivo);

    char *conteudo = ler_arquivo_texto(destino);

    StatLetra stats[26];
    AnaliseFrequencia Frequencia[26];

    executar_analise_frequencia(conteudo, stats);
    Ajustando_Frequencia(stats, Frequencia);

    // Agora o menu é responsabilidade do TAD interface
    interface_menu_principal(conteudo, stats, Frequencia);

    return 0;
}