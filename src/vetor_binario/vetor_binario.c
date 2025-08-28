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

void carregar_dados_no_vetor(InfoPalavra** p_vetor, int* p_tamanho, MusicaProcessada* dados_musica) {
    
    for (int i = 0; i < dados_musica->tamanho; i++) {
        
        TempPalavra palavra_temp = dados_musica->palavras[i];

        InfoPalavra nova_info;
        
        strcpy(nova_info.palavra, palavra_temp.palavra);
        strcpy(nova_info.nome_musica, dados_musica->nome_musica);
        strcpy(nova_info.nome_compositor, dados_musica->nome_compositor);
        strcpy(nova_info.estrofe, palavra_temp.estrofe_primeira_ocorrencia);
        nova_info.frequencia_na_musica = palavra_temp.freq_na_musica;
        
        nova_info.frequencia_total = palavra_temp.freq_na_musica;

        insere_no_vetor(p_vetor, p_tamanho, nova_info);
    }
}