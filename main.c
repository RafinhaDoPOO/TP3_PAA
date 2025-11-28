#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "arq.h"
#include "analise.h"

int main() {
    desenho_inicial();
    char nome_arquivo[256];
    printf(WHITE_NEON "Digite o nome do seu arquivo ex(Mydei.txt): "RESET);
    // Leitura, criptografia e salvamento do arquivo escolhido
    scanf("%s", nome_arquivo);
    char arquivoclaro[512];
    snprintf(arquivoclaro, sizeof(arquivoclaro),
             "Arquivos_textos_claro/%s", nome_arquivo);

    char destino[512];
    snprintf(destino, sizeof(destino),
             "Arquivos_textos_criptografados/%s", nome_arquivo);

    char *conteudo = ler_arquivo_texto(arquivoclaro);
    criptografia_cifra_deslocamento(conteudo);
    salvar_resultado(nome_arquivo, conteudo);

    //Leitura, criptografia e salvamento dos 12 arquivos
    char *conteudocompleto = concatenar_arquivos();
    criptografia_cifra_deslocamento(conteudocompleto);
    char nome_arquivo_completo[256] = "Arquivocompleto.txt";
    salvar_resultado(nome_arquivo_completo, conteudocompleto);
    // Stat e Analise do arquivo unico
    StatLetra stats[26];
    AnaliseFrequencia Frequencia[26];
    executar_analise_frequencia(conteudo, stats);
    Ajustando_Frequencia(stats, Frequencia);
    // Stat e Analise dos 12 arquivos
    StatLetra stats_completo[26];
    AnaliseFrequencia Frequencia_completo[26];
    executar_analise_frequencia(conteudocompleto, stats_completo);
    Ajustando_Frequencia(stats_completo, Frequencia_completo);
    // Agora o menu é responsabilidade do TAD interface
    interface_menu_principal(conteudo, stats, Frequencia, conteudocompleto, stats_completo,Frequencia_completo);

    return 0;

}