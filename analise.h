#ifndef ANALISE_H
#define ANALISE_H

typedef struct {
    char letra;
    int contagem;
    float frequencia;
} StatLetra;

void executar_analise_frequencia(const char *texto_cifrado);
void interface_analise_de_frequencia();
//void chute_baseado_frequencia(StatLetra stats[26], const char *texto_cifrado);

#endif