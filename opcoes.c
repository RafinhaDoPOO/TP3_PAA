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
//_________________________________________________________________________________________________________

void executar_opcao_1_estado(const char *texto_cifrado,AnaliseFrequencia *freq, StatLetra stats[26], int contador){
    
    char mais_comum_cifrada = stats[0].letra;
    char mais_comum_idioma = 'A'; 
    int deslocamento = (mais_comum_cifrada - mais_comum_idioma + 26) % 26;
    
    int letra_esta_visivel[256] = {0}; 

    for(int i = 0; i < contador && i < 26; i++) {
        unsigned char letra_atual = stats[i].letra;
        letra_esta_visivel[letra_atual] = 1; 
    }
    

    char Alfabeto[26] = {
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
        char letra_cifrada_atual = Alfabeto[i];
        
        if (letra_esta_visivel[(unsigned char)letra_cifrada_atual]) {
            char decifrada = ((letra_cifrada_atual - 'A' - deslocamento + 26) % 26) + 'A';
            printf(WHITE_NEON"%c ", decifrada);
            freq->chaves[i] = decifrada; //salvando no vetor pra exportar
        } else {
            printf(WHITE_NEON"_ ");
            freq->chaves[i] = '_'; 
        }
        
    }
    printf(LIMA" |\n"RESET);
    printf(LIMA"|______________________________________________________|\n"RESET);
    printf("\n");


    printf(CYAN_NEON"_______________________TEXTO PROGRESSIVO__________________________\n");

    freq->texto_parcial = malloc(strlen(texto_cifrado) * sizeof(char));

    for (int i = 0; texto_cifrado[i] != '\0'; i++) {
        char c = texto_cifrado[i];
        freq->texto_parcial[i] = texto_cifrado[i];

        if (isalpha(c)) {
            char maiuscula = toupper(c);
            
            if (letra_esta_visivel[(unsigned char)maiuscula]) {
                char base = isupper(c) ? 'A' : 'a';
                char decifrado = ((c - base - deslocamento + 26) % 26) + base;
                freq->texto_parcial[i] = decifrado;
                printf(LIMA "%c" RESET, decifrado);
            } else {
                printf(WHITE_NEON"%c"RESET, c);
            }
        } else {
            printf(WHITE_NEON"%c"RESET, c);
        }
        
    }
    
    printf("\n");
    printf(CYAN_NEON"__________________________________________________________________\n"RESET);
    printf("\n\n");
}

//_________________________________________________________________________________________________________

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
    // Converter padrão para maiúsculas
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

    //quantia de ocorrencias
    printf(LIMA "Ocorrencias: %d\n" RESET, count);

    //exibindo onde tava
    if (count > 0) {
        printf(WHITE_NEON "\nDetalhes das Ocorrencias:\n" RESET);
        
        // Re-iterar para imprimir detalhes
        for (int j = 0; j < count; j++) {
            int pos = posicoes[j];
            int len = strlen(padrao);
            
            // Exibir a ocorrência (substring)
            printf(CYAN_NEON "  [%03d] " LIMA, pos); 
            
            // Imprime o texto casando o padrão
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

    // Converter padrão para maiúsculas
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

void executar_opcao_5_alterar(AnaliseFrequencia Frequencia[26]) {
    char original, cifrada;

    printf(CYAN_NEON "\n______________________ALTERAR CHAVE MANUALMENTE______________________\n" RESET);
    printf(WHITE_NEON "Informe a letra original, seguida da letra para a qual foi mapeada:\n");
    
    printf(WHITE_NEON "\nDIGITE: " RESET);
    
    if (scanf(" %c %c", &original, &cifrada) != 2) {
        while (getchar() != '\n'); 
        printf(RED_NEON "Erro na leitura. Tente novamente.\n" RESET);
        return;
    }

    original = toupper(original);
    cifrada = toupper(cifrada);

    if (!isalpha(original) || !isalpha(cifrada)) {
        printf(RED_NEON "Erro: Por favor, insira apenas letras validas.\n" RESET);
        return;
    }

    int idx_original = -1;       
    int idx_dono_anterior = -1;  

    for (int i = 0; i < 26; i++) {
        if (Frequencia[i].letraalfabeto == original) {
            idx_original = i;
        }
        if (Frequencia[i].letraFrequencia == cifrada) {
            idx_dono_anterior = i;
        }
    }

   if (idx_original != -1) {
    // Armazena o mapeamento cifrado **atual** da letra 'original'
    // Este é o valor que a letra "dona anterior" receberá na troca.
    char cifrada_velha_de_original = Frequencia[idx_original].letraFrequencia;
    
    // NOTA: A variável 'original' já contém a letra do texto simples que estamos modificando.

    if (idx_dono_anterior != -1 && idx_dono_anterior != idx_original) {
        
        // 1. A letra 'original' agora aponta para a nova 'cifrada'
        Frequencia[idx_original].letraFrequencia = cifrada;
        
        // 2. O antigo "dono" da 'cifrada' recebe o mapeamento antigo de 'original'
        Frequencia[idx_dono_anterior].letraFrequencia = cifrada_velha_de_original; 
        
        printf(YELLOW_NEON "\n[Aviso] Houve uma troca para manter a consistência:\n");
        // Use 'original' para se referir à letra que está tendo seu mapeamento alterado.
        printf("A letra '%c' cedeu o mapeamento '%c' e ficou com '%c'.\n", 
               original, cifrada_velha_de_original, cifrada);
    } else {
        // Se não houve troca, apenas atualiza o mapeamento
        Frequencia[idx_original].letraFrequencia = cifrada;
    }

    printf(LIMA "\nRegistrado com sucesso: %c -> %c\n" RESET, original, cifrada);
} else {
    printf(RED_NEON "Erro: Letra original nao encontrada na tabela.\n" RESET);
}
    printf(CYAN_NEON "_____________________________________________________________________\n" RESET);
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

