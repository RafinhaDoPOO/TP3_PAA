#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "crypto.h"

void inicializar_cripto(EstadoCripto *e, const char *texto_inicial) {
    e->texto_cifrado = strdup(texto_inicial);
    e->texto_parcial = strdup(texto_inicial); // Inicialmente igual
    
    for(int i=0; i<26; i++) {
        e->chave[i] = '\0';
        e->chave_definida[i] = 0;
    }
}

void atualizar_chave(EstadoCripto *e, char letra_cifrada, char letra_clara) {
    if(isalpha(letra_cifrada)) {
        int idx = toupper(letra_cifrada) - 'A';
        e->chave[idx] = toupper(letra_clara);
        e->chave_definida[idx] = 1;
        
        // Após mudar a chave, precisamos regerar o texto visualizável
        atualizar_texto_parcial(e);
    }
}

void atualizar_texto_parcial(EstadoCripto *e) {
    // Percorre e->texto_cifrado.
    // Se a letra tem mapeamento em e->chave, escreve a decifrada em e->texto_parcial.
    // Se não tem, mantém a cifrada.
}