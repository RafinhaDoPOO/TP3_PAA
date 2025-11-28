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

//____________________________________________________________________________________________
//função de criptografia inicial

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
//____________________________________________________________________________________________

void salvar_resultado(const char *nome_arquivo, const char *arquivo_claro) {
    // Monta o caminho final: pasta + "/" + nome do arquivo
    char destino[512];
    snprintf(destino, sizeof(destino), "Arquivos_textos_criptografados/%s",nome_arquivo);

    FILE *f = fopen(destino, "w");
    if (!f) {
        perror("Erro ao criar arquivo criptografado");
        return;
    }

    fprintf(f, "%s", arquivo_claro);
    fclose(f);

}
//_____________________________________________________________________________________________
//Não esta sendo usada ainda

// INTERFACE APENAS PARA CASO DE TESTES DE MESA
void leitura_arquivo(char *nome_arquivo){

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

    // 3. Salvar resultado 
    salvar_resultado(nome_arquivo, criptografado);

    // Liberar memoria
    free(conteudo);
}
