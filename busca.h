#ifndef BUSCA_H
#define BUSCA_H

#include "crypto.h"

// Opção 3: Busca Exata
// Procura 'padrao' dentro do 'texto_cifrado'.
// Retorna número de ocorrências e imprime posições.
void buscar_exata(const char *texto_cifrado, const char *padrao);

// Opção 4: Busca Aproximada (Shift-And) [cite: 92]
// Procura 'padrao' dentro do 'texto_parcial' (decifrado) com tolerância de erros.
// Deve considerar apenas erros de substituição[cite: 94].
void buscar_aproximada_shift_and(const char *texto_parcial, const char *padrao, int tolerancia);

#endif