#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_bst.h"

ArvoreBST criar_arvore_bst() {
    return NULL;
}

void liberar_arvore_bst(ArvoreBST raiz) {
    if (raiz == NULL) {
        return;
    }
    liberar_arvore_bst(raiz->esq); 
    liberar_arvore_bst(raiz->dir); 
    free(raiz);                 
}

int inserir_bst(ArvoreBST* raiz, InfoPalavra info) {
    // CASO BASE: A árvore (ou sub-árvore) está vazia (*raiz é NULL).
    if (*raiz == NULL) {
        No_BST* novo_no = (No_BST*) malloc(sizeof(No_BST));
        
        if (novo_no == NULL) {
            return 0;
        }
        
        novo_no->info = info;
        
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        
        *raiz = novo_no;
        
        return 1; 
    }

    // COMPARAÇÃO: Compara a palavra a ser inserida com a palavra na raiz da sub-árvore atual
    // Para sabermos se devemos "andar" para a direita ou para a esquerda na árvore
    int comp = strcmp(info.palavra, (*raiz)->info.palavra);

    // CASO RECURSIVO 1: A nova palavra vem antes na ordem alfabética,
    // e deverá ser inserida a esquerda
    if (comp < 0) {
        return inserir_bst(&((*raiz)->esq), info);
    }

    // CASO RECURSIVO 2: A nova palavra vem depois.
    else if (comp > 0) {
        return inserir_bst(&((*raiz)->dir), info);
    }

    // CASO 3: A palavra já existe (comp == 0).
    // Conforme o projeto, devemos ATUALIZAR as informações.
    else {
        (*raiz)->info.frequencia_total += info.frequencia_na_musica;
        
        // Verifica se a frequência da palavra na música ATUAL é maior que a MÁXIMA frequência já registrada.
        if (info.frequencia_na_musica > (*raiz)->info.frequencia_na_musica) {
            // Se for, atualizamos os dados da música de referência.
            (*raiz)->info.frequencia_na_musica = info.frequencia_na_musica;
            strcpy((*raiz)->info.nome_musica, info.nome_musica);
            strcpy((*raiz)->info.nome_compositor, info.nome_compositor);
            strcpy((*raiz)->info.estrofe, info.estrofe);
        }
        
        return 1;
    }
}

InfoPalavra* buscar_bst(ArvoreBST raiz, char* palavra) {
    // CASO BASE 1: A árvore (ou sub-árvore) é nula.
    if (raiz == NULL) {
        return NULL; // palavra não encontrada.
    }

    // COMPARAÇÃO: Compara a palavra buscada com a palavra na raiz da sub-árvore atual.
    int comp = strcmp(palavra, raiz->info.palavra);

    // CASO BASE 2: Palavra encontrada (comp == 0).
    if (comp == 0) {
        return &(raiz->info);
    }
    // CASO RECURSIVO 1: A palavra buscada é menor que a do nó atual.
    else if (comp < 0) {
        return buscar_bst(raiz->esq, palavra);
    }
    // CASO RECURSIVO 2: A palavra buscada é maior que a do nó atual.
    else {
        return buscar_bst(raiz->dir, palavra);
    }
}

void carregar_dados_na_bst(ArvoreBST* p_raiz, MusicaProcessada* dados_musica) {
    for (int i = 0; i < dados_musica->tamanho; i++) {
        TempPalavra palavra_temp = dados_musica->palavras[i];
        
        InfoPalavra nova_info;
        strcpy(nova_info.palavra, palavra_temp.palavra);
        strcpy(nova_info.nome_musica, dados_musica->nome_musica);
        strcpy(nova_info.nome_compositor, dados_musica->nome_compositor);
        strcpy(nova_info.estrofe, palavra_temp.estrofe_primeira_ocorrencia);
        nova_info.frequencia_na_musica = palavra_temp.freq_na_musica;
        nova_info.frequencia_total = palavra_temp.freq_na_musica;

        inserir_bst(p_raiz, nova_info);
    }
}