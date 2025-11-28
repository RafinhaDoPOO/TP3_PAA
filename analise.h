#ifndef ANALISE_H
#define ANALISE_H

typedef struct{
    char letra;
    int contagem;
    float frequencia;
} StatLetra;

typedef struct{
    char letraalfabeto;
    char letraFrequencia;
    char chaves[26];
    char *texto_parcial;
} AnaliseFrequencia;

void executar_analise_frequencia(const char *texto_cifrado, StatLetra stats[26]);
void Ajustando_Frequencia(StatLetra stats[26], AnaliseFrequencia Frequencia[26]);
int trocar_mapeamento_chave(AnaliseFrequencia Frequencia[26], char original, char cifrada);

#endif