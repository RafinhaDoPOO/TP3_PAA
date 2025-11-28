#ifndef INTERFACE_H
#define INTERFACE_H

#include "analise.h"
#include "arq.h"
#include "cores.h"
void desenho_inicial();
void interface_menu_principal(const char *conteudo, StatLetra stats[26], AnaliseFrequencia Frequencia[26],const char *conteudo_completo, StatLetra stats_completo[26], AnaliseFrequencia Frequencia_completo[26]);

#endif
