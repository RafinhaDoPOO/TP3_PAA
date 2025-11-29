#ifndef ARQ_H
#define ARQ_H


char* ler_arquivo_texto(const char *caminho);

char* criptografia_cifra_deslocamento(char* conteudo);

void salvar_resultado(const char *nome_arquivo, const char *arquivo_claro);

char* concatenar_arquivos();

#endif