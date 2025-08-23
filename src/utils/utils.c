#include "utils.h" 
#include "../Tipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MusicaProcessada processar_arquivo(const char* nome_arquivo) {
    MusicaProcessada resultado = {NULL, 0, "", ""};

    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return resultado; 
    }

    fgets(resultado.nome_musica, sizeof(resultado.nome_musica), arquivo);
    resultado.nome_musica[strcspn(resultado.nome_musica, "\n")] = 0;
    trim(resultado.nome_musica);

    fgets(resultado.nome_compositor, sizeof(resultado.nome_compositor), arquivo);
    resultado.nome_compositor[strcspn(resultado.nome_compositor, "\n")] = 0;
    trim(resultado.nome_compositor);
    
    char buffer_pula_linha[256];
    fgets(buffer_pula_linha, sizeof(buffer_pula_linha), arquivo); // Pula a linha em branco

    // --- FASE 1: CONTAGEM LOCAL ---
    TempPalavra* lista_temp = NULL;
    int tamanho_temp = 0;
    char linha_buffer[1024];

    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo) != NULL) {
        char linha_para_tokenizar[1024];
        strcpy(linha_para_tokenizar, linha_buffer);
        
        char* token = strtok(linha_para_tokenizar, " \t\n\r,-.!?();:\"'");
        while (token != NULL) {
            string_para_minusculo(token);
            if (strlen(token) > 3) {
                int encontrado = 0;
                for (int j = 0; j < tamanho_temp; j++) {
                    if (strcmp(lista_temp[j].palavra, token) == 0) {
                        lista_temp[j].freq_na_musica++;
                        encontrado = 1;
                        break;
                    }
                }
                if (encontrado == 0) {
                    lista_temp = (TempPalavra*) realloc(lista_temp, (tamanho_temp + 1) * sizeof(TempPalavra));
                    strcpy(lista_temp[tamanho_temp].palavra, token);
                    lista_temp[tamanho_temp].freq_na_musica = 1;
                    strncpy(lista_temp[tamanho_temp].estrofe_primeira_ocorrencia, linha_buffer, 100);
                    lista_temp[tamanho_temp].estrofe_primeira_ocorrencia[100] = '\0';
                    tamanho_temp++;
                }
            }
            token = strtok(NULL, " \t\n\r,-.!?();:\"'");
        }
    }
    
    fclose(arquivo);

    // Preenche a struct de resultado com a lista temporária
    resultado.palavras = lista_temp;
    resultado.tamanho = tamanho_temp;

    return resultado;
}