#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include "vetor_binario.h"
#include "../Tipos.h"
#include "../utils/utils.h"

int busca_binaria(InfoPalavra* vetor, int tamanho, char* palavra) {
    int inf = 0, sup = tamanho-1, meio;
    while(inf <= sup){

        meio = (inf + sup)/2;
        int comp = strcmp(vetor[meio].palavra, palavra);

        if(comp == 0){
            return meio;
        }else if (comp > 0){
            sup = meio-1;
        }else{
            inf = meio+1;
        }
    }
    return -1;
}

void insere_no_vetor(InfoPalavra** vetor, int* tamanho, InfoPalavra nova_info) {

    int indice = busca_binaria(*vetor, *tamanho, nova_info.palavra);

    if(indice != -1){
        (*vetor)[indice].frequencia_total += nova_info.frequencia_na_musica;
        if((*vetor)[indice].frequencia_na_musica < nova_info.frequencia_na_musica){
             (*vetor)[indice].frequencia_na_musica = nova_info.frequencia_na_musica;
             strcpy((*vetor)[indice].nome_musica,nova_info.nome_musica);
             strcpy((*vetor)[indice].nome_compositor,nova_info.nome_compositor);
             strcpy((*vetor)[indice].estrofe,nova_info.estrofe);

        }
    }else if(indice == -1){
        int i;
        for(i = 0; i < *tamanho; i++){
            if(strcmp((*vetor)[i].palavra,nova_info.palavra)>0){
                break;
            }
        }
        *vetor = realloc(*vetor,(*tamanho + 1) * sizeof(InfoPalavra));

        memmove(&(*vetor)[i + 1],&(*vetor)[i],(*tamanho - i) * sizeof(InfoPalavra));

        (*vetor)[i] = nova_info;
        (*tamanho)++;

    }   
}

void carregar_arquivo_no_vetor( char* nome_arquivo, InfoPalavra** p_vetor, int* p_tamanho){
    
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char nome_musica[100];
    char nome_compositor[100];
    char buffer_linha[256];

    fgets(nome_musica, sizeof(nome_musica), arquivo);
    nome_musica[strcspn(nome_musica, "\n")] = 0; 
    trim(nome_musica); 

    fgets(nome_compositor,sizeof(nome_compositor),arquivo);
    nome_compositor[strcspn(nome_compositor, "\n")] = 0; 
    trim(nome_compositor); 

    fgets(buffer_linha,sizeof(buffer_linha), arquivo);

    TempPalavra* lista_temp = NULL;
    int tamanho_temp = 0;
    

    while (fgets(buffer_linha, sizeof(buffer_linha), arquivo) != NULL) {
        char linha_original[256];
        strcpy(linha_original, buffer_linha);

        char* token;
        const char delimitadores[] = " \t\n\r,-.!?();:\"'";
        
        token = strtok(buffer_linha,delimitadores);

        while(token!=NULL){

            string_para_minusculo(token);

            if (strlen(token) > 3) {
                int encontrado = 0; 
                for (int j = 0; j < tamanho_temp; j++){
                    if(strcmp(lista_temp[j].palavra,token) == 0){
                        lista_temp[j].freq_na_musica++;
                        encontrado = 1;
                        break;
                    }
                }
                if(encontrado == 0){
                    lista_temp = (TempPalavra*) realloc(lista_temp,(tamanho_temp + 1) * sizeof(TempPalavra));

                    strcpy(lista_temp[tamanho_temp].palavra, token);
                    strncpy(lista_temp[tamanho_temp].estrofe_primeira_ocorrencia,linha_original, 100);
                    lista_temp[tamanho_temp].estrofe_primeira_ocorrencia[100] = '\0';
                    lista_temp[tamanho_temp].freq_na_musica = 1;

                    tamanho_temp++;
                }
            }
            token = strtok(NULL, delimitadores);
        }
    
    }
    for (int i = 0; i < tamanho_temp; i++){
        InfoPalavra nova_info_final;

        strcpy(nova_info_final.palavra, lista_temp[i].palavra);
        strcpy(nova_info_final.nome_musica,nome_musica);
        strcpy(nova_info_final.nome_compositor, nome_compositor);
        strcpy(nova_info_final.estrofe, lista_temp[i].estrofe_primeira_ocorrencia);
        nova_info_final.frequencia_na_musica = lista_temp[i].freq_na_musica;
        nova_info_final.frequencia_total = lista_temp[i].freq_na_musica;

        insere_no_vetor(p_vetor, p_tamanho, nova_info_final);
     }

    free(lista_temp);
    fclose(arquivo);
    
}
