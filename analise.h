#ifndef ANALISE_H
#define ANALISE_H

#include <stddef.h>

typedef struct{
    char letra;
    int contagem;
    float frequencia;
} StatLetra;


typedef struct{
    char letraalfabeto;      
    char letraFrequencia;  
    char chaves[26];         
    int  travada[26];        
    char *texto_parcial;    
} AnaliseFrequencia;

void executar_analise_frequencia(const char *texto_cifrado, StatLetra stats[26]);
void Ajustando_Frequencia(StatLetra stats[26], AnaliseFrequencia Frequencia[26]);

#endif
