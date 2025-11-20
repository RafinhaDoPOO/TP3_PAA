#include <stdio.h>
#include <stdlib.h>
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

void salvar_resultado(const char *caminho, const char *chave, const char *texto) {
    // Implementar fopen com "w" e fprintf seguindo a formatação pedida
    // [cite: 135]
}