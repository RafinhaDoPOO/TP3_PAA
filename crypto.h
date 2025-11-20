#ifndef CRYPTO_H
#define CRYPTO_H

typedef struct {
    char *texto_cifrado;       // O texto lido do arquivo (imutável após carga)
    char *texto_parcial;       // O buffer onde montamos o texto misturado (Cifrado + Decifrado)
    char chave[26];            // Mapeamento: Índice ('A'-'A') -> Valor (Letra Real)
    int chave_definida[26];    // Flags: 0 = não mapeado, 1 = mapeado
} EstadoCripto;

// Inicializa estruturas e aloca memória necessária
void inicializar_cripto(EstadoCripto *e, const char *texto_inicial);

// Libera memória
void destruir_cripto(EstadoCripto *e);

// Atualiza uma entrada na chave (Ex: 'X' cifrado é na verdade 'A') [cite: 127]
void atualizar_chave(EstadoCripto *e, char letra_cifrada, char letra_clara);

// Gera a string 'texto_parcial' baseada na chave atual para exibição/busca
// Deve misturar letras decifradas com as ainda cifradas [cite: 60]
void atualizar_texto_parcial(EstadoCripto *e);

#endif