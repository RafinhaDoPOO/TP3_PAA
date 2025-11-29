#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arq.h"
#include <string.h>
char* ler_arquivo_texto(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }


    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    rewind(f);

    char *conteudo = (char*) malloc(tamanho + 1);
    if (conteudo) {
        fread(conteudo, 1, tamanho, f);
        conteudo[tamanho] = '\0';
    }
    
    fclose(f);
    return conteudo;
}

//____________________________________________________________________________________________


char* criptografia_cifra_deslocamento(char* conteudo){

    if (!conteudo) {
        return NULL;
    }

    srand(time(NULL));
    int x = (rand() % 26) + 1; 

    for (int i = 0; conteudo[i] != '\0'; i++) {
        
        char c = conteudo[i];

        if (c >= 'a' && c <= 'z') {
            
            conteudo[i] = ((c - 'a' + x) % 26) + 'a';
        }
        else if (c >= 'A' && c <= 'Z') {
            
            conteudo[i] = ((c - 'A' + x) % 26) + 'A';
        }
      
    }

    return conteudo;
}
//____________________________________________________________________________________________

void salvar_resultado(const char *nome_arquivo, const char *arquivo_claro) {

    char destino[512];
    snprintf(destino, sizeof(destino), "Arquivos_textos_criptografados/%s",nome_arquivo);

    FILE *f = fopen(destino, "w");
    if (!f) {
        perror("Erro ao criar arquivo criptografado");
        return;
    }

    fprintf(f, "%s", arquivo_claro);
    fclose(f);

}
//______________________________________________________________________________________________
char* concatenar_arquivos() {
    
    const char *arquivos[] = {
        "Arquivos_textos_claro/Aglaea.txt",
        "Arquivos_textos_claro/Anaxa.txt",
        "Arquivos_textos_claro/Castorice.txt",
        "Arquivos_textos_claro/Cerydra.txt",
        "Arquivos_textos_claro/Cipher.txt",
        "Arquivos_textos_claro/Cyrene.txt",
        "Arquivos_textos_claro/Dang Heng - Terravox.txt", 
        "Arquivos_textos_claro/Hyacine.txt",
        "Arquivos_textos_claro/Hysilens.txt",
        "Arquivos_textos_claro/Mydei.txt",
        "Arquivos_textos_claro/Phainon.txt",
        "Arquivos_textos_claro/Tribios.txt"
    };
    

    int num_arquivos = sizeof(arquivos) / sizeof(arquivos[0]);


    char *conteudo_total = (char*) malloc(1); 
    if (!conteudo_total) {
        perror("Falha ao alocar memoria inicial");
        return NULL;
    }
    conteudo_total[0] = '\0'; 


  
    for (int i = 0; i < num_arquivos; i++) {
      
        char *conteudo_parcial = ler_arquivo_texto(arquivos[i]);
        
      
        if (conteudo_parcial) {
            size_t tam_atual = strlen(conteudo_total);
            size_t tam_parcial = strlen(conteudo_parcial);
            
           
            size_t tam_novo = tam_atual + tam_parcial + 1; 

        
            char *temp = (char*) realloc(conteudo_total, tam_novo);

            if (temp) {
                conteudo_total = temp;
                
                strcat(conteudo_total, conteudo_parcial);
            } else {
                perror("Falha ao realocar memoria durante a concatenacao");
                free(conteudo_parcial);
                free(conteudo_total);
                return NULL;
            }
            
        
            free(conteudo_parcial);
        }
    }
    
    return conteudo_total;
}

//____________________________________________________________________________________________
