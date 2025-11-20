#ifndef ARQ_H
#define ARQ_H

// Lê todo o conteúdo de um arquivo e retorna uma string alocada dinamicamente.
// Retorna NULL em caso de erro.
char* ler_arquivo_texto(const char *caminho);

// Escreve a chave e o texto decifrado em um arquivo de saída.
void salvar_resultado(const char *caminho, const char *chave, const char *texto);

#endif