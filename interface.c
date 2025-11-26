#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "analise.h"
#include "arq.h"

// Cores ANSI
#define RESET   "\033[0m"
#define GREEN   "\033[32m"

void interface_analise_opcao_1(const char *texto_cifrado, StatLetra stats[26],AnaliseFrequencia Frequencia[26], int contador){
    char Alfabeto[26] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

    printf("\n=== Texto criptografado ===\n");
    printf("%s\n\n", texto_cifrado);

    // -------------------------------
    // Imprime chave usada no chute
    // -------------------------------

   printf("=== Chave ===\n");

// imprime alfabeto
for (int i = 0; i < 26; i++) {
    printf("%c ", Alfabeto[i]);
}
printf("\n");

// imprime substituições
for (int i = 0; i < 26; i++) {
    char substituta = '_';  // padrão: não mapeado ainda

    // procurar no vetor Frequencia
    for (int j = 0; j < contador; j++) { 
        // só usa até "contador"
        if (Frequencia[j].letraalfabeto == Alfabeto[i]) {
            substituta = Frequencia[j].letraFrequencia;
            break;
        }
    }

    printf("%c ", substituta);
}
printf("\n");

    

    printf("=== Texto parcialmente decifrado ===\n");

for (int i = 0; texto_cifrado[i] != '\0'; i++)
{
    char c = texto_cifrado[i];

    if (isalpha(c))
    {
        char up = toupper(c);
        char resultado = c;   // por padrão: mantém a letra criptografada
        int encontrado = 0;

        // verifica se a letra já foi decifrada
        for (int j = 0; j < contador; j++)
        {
            if (Frequencia[j].letraalfabeto == up)
            {
                resultado = Frequencia[j].letraFrequencia;
                encontrado = 1;
                break;
            }
        }

        if (encontrado)
        {
            // ✔ letra que já sabemos → verde
            printf(GREEN "%c" RESET, resultado);
        }
        else
        {
            // ✔ letra ainda desconhecida → mostra criptografada
            printf("%c", c);
        }
    }
    else
    {
        // pontuação, espaços, etc
        printf("%c", c);
    }
}

printf("\n\n");

}



void interfaceopcao2(StatLetra stats[26]){
    printf("Análise de Frequência:\n");
    printf("Letra | Contagem | Frequência (%%)\n");
    printf("--------------------------------\n");
    
    // 3. O array 'resultados' agora está preenchido e ordenado.
    //    Você pode iterar sobre ele para usá-lo ou imprimi-lo.
    for (int i = 0; i < 26; i++) {
        // Para imprimir apenas as letras que apareceram
        if (stats[i].contagem > 0) {
            printf("  %c   |    %d     |    %.2f\n", 
                   stats[i].letra, 
                   stats[i].contagem, 
                   stats[i].frequencia);
        }
    };
}

int main() {
    int opcao;
    int contadordefrequencia = 0;
    char nome_arquivo[256];
    printf("Digite o nome do seu arquivo : \n");
    scanf("%s", nome_arquivo);
    interface_leitura_arquivo(nome_arquivo);
    char destino[512];
    snprintf(destino, sizeof(destino), "Arquivos_textos_criptografados/%s",nome_arquivo);
    char *conteudo = ler_arquivo_texto(destino);
    StatLetra stats[26];
    AnaliseFrequencia Frequencia[26];


    executar_analise_frequencia(conteudo, stats);
    Ajustando_Frequencia(stats, Frequencia);
    // 3. Loop Principal 
    do {
        printf("\n=== MENU DE CRIPTOANALISE ===\n");
        printf("1. Apresentar estado atual\n");
        printf("2. Analise de frequencia\n");
        printf("3. Busca exata (Padrao no texto criptografado)\n");
        printf("4. Busca aproximada (Shift-And no parcial)\n");
        printf("5. Alterar chave\n");
        printf("6. Exportar e Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: interface_analise_opcao_1(conteudo,stats,Frequencia,contadordefrequencia);
            contadordefrequencia++;
            break;
            case 2: interfaceopcao2(stats); break;
            case 3: printf("Ainda não foi implementado"); break;
            case 4: printf("Ainda não foi implementado"); break;
            case 5: printf("Ainda não foi implementado"); break;
            case 6: printf("Ainda não foi implementado"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (opcao != 6);

    return 0;
}