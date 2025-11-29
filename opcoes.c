#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "opcoes.h"
#include "busca.h"
#include "cores.h" 
#include "analise.h"
#define MAX_FILENAME 256
#define MAX_TEXTO 100000
#define MAX_PADRAO 256

void executar_opcao_1_estado(
        const char *texto_cifrado,
        AnaliseFrequencia *freq,
        StatLetra stats[26],
        int contador
) {
    char mais_comum_cifrada = stats[0].letra;
    char mais_comum_idioma  = 'A'; 
    int deslocamento = (mais_comum_cifrada - mais_comum_idioma + 26) % 26;

    int letra_esta_visivel[256] = {0};
    for (int i = 0; i < contador && i < 26; i++) {
        unsigned char letra_atual = stats[i].letra;
        letra_esta_visivel[letra_atual] = 1;
    }

    const char Alfabeto[26] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    printf(CYAN_NEON"\n______________________TEXTO CRIPTOGRAFADO___________________________\n");
    printf(WHITE_NEON"%s\n\n", texto_cifrado);

    printf(LIMA"_______________________CHAVE PARCIAL___________________\n");
    printf(LIMA"| "RESET);
    for (int i = 0; i < 26; i++) printf(WHITE_NEON "%c ", Alfabeto[i]);
    printf(LIMA" |\n"RESET);

    printf(LIMA"| "RESET);

    
    for (int i = 0; i < 26; i++) {
        char cifrada = Alfabeto[i];

        if (freq->travada[i] == 1) {
            
            printf(WHITE_NEON "%c ", freq->chaves[i]);
            continue;
        }

     
        if (letra_esta_visivel[(unsigned char)cifrada]) {
            char decifrada = ((cifrada - 'A' - deslocamento + 26) % 26) + 'A';
            printf(WHITE_NEON "%c ", decifrada);
           
            freq->chaves[i] = decifrada;
        } else {
            printf(WHITE_NEON "_ ");
           
            if (freq->travada[i] == 0) freq->chaves[i] = '_';
        }
    }

    printf(LIMA" |\n"RESET);
    printf(LIMA"|______________________________________________________|\n"RESET);
    printf("\n");


    printf(CYAN_NEON"_______________________TEXTO PROGRESSIVO__________________________\n");

    size_t len = strlen(texto_cifrado);

    if (freq->texto_parcial) {
        free(freq->texto_parcial);
        freq->texto_parcial = NULL;
    }
    freq->texto_parcial = malloc(len + 1);
    if (!freq->texto_parcial) {
        perror("malloc");
        return;
    }
    freq->texto_parcial[len] = '\0';

    for (size_t i = 0; i < len; ++i) {
        char c = texto_cifrado[i];
        freq->texto_parcial[i] = c;

        if (isalpha((unsigned char)c)) {
            char maiuscula = toupper((unsigned char)c);
            int idx = maiuscula - 'A';

          
            if (freq->chaves[idx] != '_' && freq->chaves[idx] != '\0') {
                char decifrada = freq->chaves[idx];
                char base = isupper((unsigned char)c) ? 'A' : 'a';
                char ajustada = (decifrada - 'A') + base;

                freq->texto_parcial[i] = ajustada;
                printf(LIMA "%c" RESET, ajustada);
                continue;
            }

        
            if (letra_esta_visivel[(unsigned char)maiuscula]) {
                char base = isupper((unsigned char)c) ? 'A' : 'a';
                char decifrado = ((c - base - deslocamento + 26) % 26) + base;

                freq->texto_parcial[i] = decifrado;
                printf(LIMA "%c" RESET, decifrado);
            } else {
                printf(WHITE_NEON "%c" RESET, c);
            }

        } else {
            printf(WHITE_NEON "%c" RESET, c);
        }
    }

    printf("\n" CYAN_NEON"__________________________________________________________________\n"RESET);
    printf("\n\n");
}
void executar_opcao_2_frequencia(StatLetra stats[26]) {
    printf("\n");
    printf(CYAN_NEON"____________________________________\n");
    printf(CYAN_NEON"| " LIMA "ANALISE DE FREQUENCIA:"CYAN_NEON"            |\n");
    printf(CYAN_NEON"| "LIMA "Letra" CYAN_NEON" | "LIMA "Contagem" CYAN_NEON" | "LIMA "Frequencia (%%)"CYAN_NEON" |\n");
    printf(CYAN_NEON"|___________________________________|\n");

    for (int i = 0; i < 26; i++) {
        if (stats[i].contagem > 0) {
            printf(CYAN_NEON "|" WHITE_NEON" %c "  CYAN_NEON "|"  WHITE_NEON  " %d "  CYAN_NEON   "|"  WHITE_NEON " %.2f " CYAN_NEON"|\n"
                    , stats[i].letra, stats[i].contagem, stats[i].frequencia);
        }
    }
}
//_________________________________________________________________________________________________________
void executar_opcao_3_busca_exata(const char *texto_cifrado) {
    char padrao[MAX_PADRAO + 1];
    int *posicoes = NULL;
    int count = 0;

    printf(CYAN_NEON "\n____________________BUSCA EXATA (KMP)____________________\n" RESET);
    printf(WHITE_NEON "Qual o padrao utilizado? (Apenas letras serao consideradas)\n" RESET);
    printf(WHITE_NEON "> " RESET);
    
    if (scanf("%s", padrao) != 1) {
        printf(RED_NEON "Erro na leitura do padrao.\n" RESET);
        return;
    }

    for (int i = 0; padrao[i] != '\0'; i++) {
        padrao[i] = toupper((unsigned char)padrao[i]);
    }

    
    posicoes = buscar_exata(texto_cifrado, padrao);
    
    if (posicoes == NULL) {
        printf(RED_NEON "Erro: Falha na alocacao de memoria.\n" RESET);
        return;
    }

    
    printf("\n" LIMA "________Resultado da Busca__________\n" RESET);
    printf(WHITE_NEON "Padrao: %s (tamanho %lu)\n", padrao, strlen(padrao));
    

    int i = 0;
    while (posicoes[i] != -1) {
        count++;
        i++;
    }


    printf(LIMA "Ocorrencias: %d\n" RESET, count);

  
    
    if (count > 0) {
        printf(WHITE_NEON "\nDetalhes das Ocorrencias:\n" RESET);
        

        for (int j = 0; j < count; j++) {
            int pos = posicoes[j];
            int len = strlen(padrao);
            
          
            printf(CYAN_NEON "  [%03d] " LIMA, pos); 
            
     
            for (int k = 0; k < len; k++) {
                printf("%c", texto_cifrado[pos + k]);
            }
            printf(RESET "\n");
        }
    }
    
    free(posicoes);

    printf(CYAN_NEON "________________________________________________________\n" RESET);
}
//_________________________________________________________________________________________________________
void executar_opcao_4_busca_aprox(char *texto_cifrado){
    char padrao[MAX_PADRAO + 1];
    int k;
    printf("\n");
    printf(CYAN_NEON "\n____________________BUSCA APROXIMADA (SHIFT-AND)____________________\n" RESET);
    printf(WHITE_NEON "Qual o padrao utilizado? (Apenas letras serao consideradas)\n" RESET);
    printf(WHITE_NEON "> " RESET);
    
    if (scanf("%s", padrao) != 1) {
        printf(RED_NEON "Erro na leitura do padrao.\n" RESET);
        return;
    }


    for (int i = 0; padrao[i] != '\0'; i++) {
        padrao[i] = toupper((unsigned char)padrao[i]);
    }

    printf(WHITE_NEON "Quantos mismatches (substituicoes) sao permitidos? " RESET);
    if (scanf("%d", &k) != 1 || k < 0 || k > 64) {
        printf(RED_NEON "Erro: Numero invalido de mismatches. Deve ser entre 0 e 64.\n" RESET);
        return;
    }

    shiftand_kmismatch(texto_cifrado, strlen(texto_cifrado), padrao, strlen(padrao), k);

    printf(CYAN_NEON "________________________________________________________\n" RESET);
}
//_________________________________________________________________________________________________________

void executar_opcao_5_alterar(AnaliseFrequencia *freq) {
    char cifrada, decifrada;

    printf(CYAN_NEON "\n_______________________ALTERAR CHAVE________________________\n" RESET);
    printf(WHITE_NEON "Informe a letra cifrada e a letra decifrada (ex: A S): " RESET);

    if (scanf(" %c %c", &cifrada, &decifrada) != 2) {
        printf(RED_NEON "Entrada inválida.\n" RESET);
        return;
    }

    cifrada   = toupper(cifrada);
    decifrada = toupper(decifrada);

    if (!isalpha(cifrada) || !isalpha(decifrada)) {
        printf(RED_NEON "As entradas devem ser letras.\n" RESET);
        return;
    }

    int idx = cifrada - 'A';

    
    freq->chaves[idx]  = decifrada;
    freq->travada[idx] = 1;  

    printf(LIMA "Registrado: %c -> %c\n" RESET, cifrada, decifrada);
    printf(CYAN_NEON "_________________________________________________________________\n" RESET);
}

//_________________________________________________________________________________________________________
void executar_opcao_6_exportar(const AnaliseFrequencia *freq) {
    char nome_arquivo[MAX_FILENAME] = "";
    FILE *arquivo = NULL;

    printf("\n" CYAN_NEON "_______________________________________________________\n" RESET);
    printf(CYAN_NEON           "|                  MENU DE EXPORTACAO                  |\n" RESET);
    printf(CYAN_NEON      "|______________________________________________________|\n" RESET);
    printf("\n");

    printf(WHITE_NEON "DIGITE O NOME DO ARQUIVO PARA SALVAR A CHAVE(ex: chave.txt): " RESET);
    
   
    if (scanf("%255s", nome_arquivo) != 1) {
        printf(RED_NEON "Erro ao ler o nome do arquivo.\n" RESET);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    
    
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
   
    if (strlen(nome_arquivo) == 0) {
        printf(RED_NEON "\nERRO: O nome do arquivo nao pode ser vazio (Falha na leitura).\n" RESET);
        return;
    }

   
    arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf(RED_NEON "\nERRO na criacao do arquivo!\n" RESET);
        return; 
    }

 
    for (int i = 0; i < 26; i++) {
        fprintf(arquivo, "%c ", 'A' + i); 
    }
    fprintf(arquivo, "\n");
    
    for (int i = 0; i < 26; i++) {
        fprintf(arquivo, "%c ", freq->chaves[i]);
    }
    fprintf(arquivo, "\n");

    fclose(arquivo);
    printf("\n" LIMA "SUCESSO: CHAVE SALVA EM '%s'.\n" RESET, nome_arquivo);
    printf(YELLOW_NEON "ENCERRANDO\n" RESET);
}