#ifndef ARQ_H
#define ARQ_H

// Lê todo o conteúdo de um arquivo e retorna uma string alocada dinamicamente.
// Retorna NULL em caso de erro.
char* ler_arquivo_texto(const char *caminho);
// Pega o conteudo que foi lido do arquivo, e faz a criptografia dele.
// Criptografia foi feita com cifra de deslocamento, com um numero x gerado aleatoriamente na função.
char* criptografia_cifra_deslocamento(char* conteudo);
// Escreve a chave e o texto decifrado em um arquivo de saída.
void salvar_resultado(const char *nome_arquivo, const char *arquivo_claro);
// Concatenar os 12 arquivos em 1 so
char* concatenar_arquivos();

#endif