#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "arq.h"
#include "analise.h"

int main() {

    desenho_inicial();
   
    char nome_arquivo[256];

    // Vetores principais de análise
    StatLetra stats[26];
    StatLetra stats_completo[26];
    AnaliseFrequencia Frequencia[26];
    AnaliseFrequencia Frequencia_completo[26];

    // Inicializar as chaves e travas
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            Frequencia[i].chaves[j] = '_';
            Frequencia[i].travada[j] = 0;
            Frequencia[i].texto_parcial = NULL;

            Frequencia_completo[i].chaves[j] = '_';
            Frequencia_completo[i].travada[j] = 0;
            Frequencia_completo[i].texto_parcial = NULL;
        }
    }

    printf(WHITE_NEON "Digite o nome do seu arquivo ex(Mydei.txt): " RESET);
    scanf("%s", nome_arquivo);

    char arquivoclaro[512];
    snprintf(arquivoclaro, sizeof(arquivoclaro),
             "Arquivos_textos_claro/%s", nome_arquivo);

    char destino[512];
    snprintf(destino, sizeof(destino),
             "Arquivos_textos_criptografados/%s", nome_arquivo);

    // Lê, criptografa e salva o arquivo individual
    char *conteudo = ler_arquivo_texto(arquivoclaro);
    criptografia_cifra_deslocamento(conteudo);
    salvar_resultado(nome_arquivo, conteudo);

    // Lê, criptografa e salva os 12 arquivos concatenados
    char *conteudocompleto = concatenar_arquivos();
    criptografia_cifra_deslocamento(conteudocompleto);
    salvar_resultado("Arquivocompleto.txt", conteudocompleto);

    // Estatísticas e frequências – arquivo individual
    executar_analise_frequencia(conteudo, stats);
    Ajustando_Frequencia(stats, Frequencia);

    // Estatísticas e frequências – arquivos completos
    executar_analise_frequencia(conteudocompleto, stats_completo);
    Ajustando_Frequencia(stats_completo, Frequencia_completo);

    // Abre o menu
    interface_menu_principal(
        conteudo, stats, Frequencia,
        conteudocompleto, stats_completo, Frequencia_completo
    );

    return 0;
}
