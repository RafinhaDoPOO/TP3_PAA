#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arq.h"
#include "analise.h"

void executar_analise_frequencia(const char *texto_cifrado, StatLetra stats[26])
{

    // 1. Inicializar (A-Z)
    for (int i = 0; i < 26; i++)
    {
        stats[i].letra = 'A' + i;
        stats[i].contagem = 0;
        stats[i].frequencia = 0.0;
    }

    int total = 0;

    // 2. Contar ocorrências
    for (int i = 0; texto_cifrado[i] != '\0'; i++)
    {
        char c = texto_cifrado[i];

        if (isalpha(c))
        {
            c = toupper(c);
            stats[c - 'A'].contagem++;
            total++;
        }
    }

    // 3. Calcular frequências
    for (int i = 0; i < 26; i++)
    {
        if (total > 0)
            stats[i].frequencia = (stats[i].contagem * 100.0f) / total;
    }

    // 4. Ordenar array stats por contagem (decrescente)
    for (int i = 0; i < 26 - 1; i++)
    {
        for (int j = 0; j < 26 - i - 1; j++)
        {
            if (stats[j].contagem < stats[j + 1].contagem)
            {
                StatLetra tmp = stats[j];
                stats[j] = stats[j + 1];
                stats[j + 1] = tmp;
            }
        }
    }
    // 5. Imprimir resultados
    printf("Letra,  Cont.,  Freq.\n");

    for (int i = 0; i < 26; i++)
    {
        if (stats[i].contagem > 0)
        {
            printf("%c%12d%8.2f%%\n",
                   stats[i].letra,
                   stats[i].contagem,
                   stats[i].frequencia);
        }
    }
}

void Ajustando_Frequencia(StatLetra stats[26], AnaliseFrequencia Frequencia[26])
{
    const char freq_pt[26] = {
        'A', 'E', 'O', 'S', 'R', 'N', 'I', 'D', 'M', 'U', 'T', 'C', 'L', 'P', 'V', 'G', 'H', 'Q', 'B', 'F', 'Z', 'J', 'X', 'K', 'W', 'Y'};

    // Ordenar stats
    for (int i = 0; i < 25; i++)
        for (int j = i + 1; j < 26; j++)
            if (stats[j].contagem > stats[i].contagem)
            {
                StatLetra tmp = stats[i];
                stats[i] = stats[j];
                stats[j] = tmp;
            }

    // Preencher resultado
    for (int i = 0; i < 26; i++)
    {
        Frequencia[i].letraalfabeto = freq_pt[i];       // letra esperada
        Frequencia[i].letraFrequencia = stats[i].letra; // letra real do texto
    }
}
