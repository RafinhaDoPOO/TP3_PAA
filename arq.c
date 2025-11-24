#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arq.h"

char* ler_arquivo_texto(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    // Descobre o tamanho do arquivo para alocar memória exata
    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    rewind(f);

    char *conteudo = (char*) malloc(tamanho + 1);
    if (conteudo) {
        fread(conteudo, 1, tamanho, f);
        conteudo[tamanho] = '\0'; // Null-terminator
    }
    
    fclose(f);
    return conteudo;
}

char* criptografia_cifra_deslocamento(char* conteudo){
// Verificar se o conteudo foi criado
    if (!conteudo) {
        return NULL;
    }
// Criação do numero de deslocamento, ele será aleatorio entre 1 a 26.
    srand(time(NULL));
    int x = (rand() % 26) + 1; 
// Vamos adicionar o deslocamento em todo o texto.
    for (int i = 0; conteudo[i] != '\0'; i++) {
        
        char c = conteudo[i];

        if (c >= 'a' && c <= 'z') {
            // minúsculas
            conteudo[i] = ((c - 'a' + x) % 26) + 'a';
        }
        else if (c >= 'A' && c <= 'Z') {
            // maiúsculas
            conteudo[i] = ((c - 'A' + x) % 26) + 'A';
        }
        // outros caracteres (espaço) ficam iguais
    }

    return conteudo;
}

void salvar_resultado(const char *caminho_saida, const char *nome_arquivo, const char *arquivo_claro) {
    // Monta o caminho final: pasta + "/" + nome do arquivo
    char destino[512];
    snprintf(destino, sizeof(destino), "%s/%s", caminho_saida, nome_arquivo);

    FILE *f = fopen(destino, "w");
    if (!f) {
        perror("Erro ao criar arquivo criptografado");
        return;
    }

    fprintf(f, "%s", arquivo_claro);
    fclose(f);
}
// INTERFACE APENAS PARA CASO DE TESTES DE MESA
void interface_leitura_arquivo(){
    char nome_arquivo[256];

    printf("Digite o nome do arquivo (ex: texto.txt): ");
    scanf("%255s", nome_arquivo);

    // Construindo caminho completo do arquivo claro
    char caminho_claro[512];
    snprintf(caminho_claro, sizeof(caminho_claro),
             "Arquivos_textos_claro/%s", nome_arquivo);

    // 1. Ler arquivo original
    char *conteudo = ler_arquivo_texto(caminho_claro);

    if (!conteudo) {
        printf("Erro ao ler arquivo. Encerrando...\n");
    }

    // 2. Criptografar
    char *criptografado = criptografia_cifra_deslocamento(conteudo);

    if (!criptografado) {
        printf("Erro na criptografia.\n");
        free(conteudo);
    }

    // 3. Salvar o resultado
    salvar_resultado("Arquivos_textos_criptografados", nome_arquivo, criptografado);

    printf("\nArquivo '%s' criptografado com sucesso!\n", nome_arquivo);
    printf("Saída salva em: Arquivos_textos_criptografados/%s\n", nome_arquivo);

    // Liberar memoria
    free(conteudo);
}
