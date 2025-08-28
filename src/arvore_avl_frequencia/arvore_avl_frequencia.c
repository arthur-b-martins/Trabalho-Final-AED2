#include "arvore_avl_frequencia.h"
#include <stdlib.h>
#include <string.h>
#include "Tipos.h"

ArvoreAVL_Freq criar_arvore_avl_freq(){
    return NULL;
}

void liberar_lista_palavras(ListaPalavras* lista) {
    ListaPalavras* atual = lista;
    ListaPalavras* proximo;

    while (atual != NULL) {
        proximo = atual->prox; 
        free(atual);           
        atual = proximo;       
    }
}


void liberar_arvore_avl_freq(ArvoreAVL_Freq raiz) {
    if (raiz == NULL) {
        return;
    }
    liberar_arvore_avl_freq(raiz->esq);
    liberar_arvore_avl_freq(raiz->dir);

    liberar_lista_palavras(raiz->palavras);
    free(raiz);
}

// funções para inserir -----------------------

void adicionar_palavra_lista(ListaPalavras** lista, char* palavra) {
    ListaPalavras* novo_no_lista = (ListaPalavras*) malloc(sizeof(ListaPalavras));
    if (novo_no_lista == NULL) return;

    strcpy(novo_no_lista->palavra, palavra);
    novo_no_lista->prox = *lista; 
    *lista = novo_no_lista;
}

void rotacao_simples_direita_freq(ArvoreAVL_Freq* raiz) {
    No_AVL_Freq* nova_raiz = (*raiz)->esq;
    (*raiz)->esq = nova_raiz->dir;
    nova_raiz->dir = *raiz;
    (*raiz)->fator_balanceamento = 0;
    nova_raiz->fator_balanceamento = 0;
    *raiz = nova_raiz;
}

void rotacao_simples_esquerda_freq(ArvoreAVL_Freq* raiz) {
    No_AVL_Freq* nova_raiz = (*raiz)->dir;
    (*raiz)->dir = nova_raiz->esq;
    nova_raiz->esq = *raiz;
    (*raiz)->fator_balanceamento = 0;
    nova_raiz->fator_balanceamento = 0;
    *raiz = nova_raiz;
}

// Rotação para desbalanceamento Esquerda-Direita (ED)
void rotacao_dupla_direita_freq(ArvoreAVL_Freq* raiz) {
    No_AVL_Freq* u = (*raiz)->esq;
    No_AVL_Freq* v = u->dir;

    u->dir = v->esq;
    v->esq = u;
    (*raiz)->esq = v->dir;
    v->dir = *raiz;

    // Ajuste dos fatores de balanceamento
    if (v->fator_balanceamento == -1) { // Inserido na sub-árvore direita de v
        (*raiz)->fator_balanceamento = 0;
        u->fator_balanceamento = 1;
    } else if (v->fator_balanceamento == 1) { // Inserido na sub-árvore esquerda de v
        (*raiz)->fator_balanceamento = -1;
        u->fator_balanceamento = 0;
    } else { // v é o próprio nó inserido
        (*raiz)->fator_balanceamento = 0;
        u->fator_balanceamento = 0;
    }
    v->fator_balanceamento = 0;
    *raiz = v;
}

// Rotação para desbalanceamento Direita-Esquerda (DE)
void rotacao_dupla_esquerda_freq(ArvoreAVL_Freq* raiz) {
    No_AVL_Freq* u = (*raiz)->dir;
    No_AVL_Freq* v = u->esq;

    u->esq = v->dir;
    v->dir = u;
    (*raiz)->dir = v->esq;
    v->esq = *raiz;
    
    // Ajuste dos fatores de balanceamento
    if (v->fator_balanceamento == 1) { // Inserido na sub-árvore esquerda de v
        (*raiz)->fator_balanceamento = 0;
        u->fator_balanceamento = -1;
    } else if (v->fator_balanceamento == -1) { // Inserido na sub-árvore direita de v
        (*raiz)->fator_balanceamento = 1;
        u->fator_balanceamento = 0;
    } else { // v é o próprio nó inserido
        (*raiz)->fator_balanceamento = 0;
        u->fator_balanceamento = 0;
    }
    v->fator_balanceamento = 0;
    *raiz = v;
}

int inserir_avl_freq(ArvoreAVL_Freq* raiz, InfoPalavra* info, int* cresceu) {
    // CASO BASE: A árvore (ou sub-árvore) está vazia. Ponto de inserção de um nó de frequencia.
    if (*raiz == NULL) {
        No_AVL_Freq* novo_no_arvore = (No_AVL_Freq*) malloc(sizeof(No_AVL_Freq));
        if (novo_no_arvore == NULL) {
            *cresceu = 0;
            return 0;
        }
        
        novo_no_arvore->frequencia = info->frequencia_total;
        novo_no_arvore->esq = NULL;
        novo_no_arvore->dir = NULL;
        novo_no_arvore->fator_balanceamento = 0;
        novo_no_arvore->palavras = NULL;

        // Adiciona a primeira palavra na nova lista de frequência
        adicionar_palavra_lista(&(novo_no_arvore->palavras), info->palavra);

        *raiz = novo_no_arvore;
        *cresceu = 1; 
        return 1; 
    }

    // CASO RECURSIVO: A árvore não está vazia.
    
    if (info->frequencia_total < (*raiz)->frequencia) {
        // --- Inserir à ESQUERDA ---
        if (inserir_avl_freq(&((*raiz)->esq), info, cresceu)) {
            
            if (*cresceu) {
                switch ((*raiz)->fator_balanceamento) {
                    case -1: (*raiz)->fator_balanceamento = 0; *cresceu = 0; break;
                    case 0:  (*raiz)->fator_balanceamento = 1; *cresceu = 1; break;
                    case 1: 
                        if ((*raiz)->esq->fator_balanceamento == 1)
                            rotacao_simples_direita_freq(raiz);
                        else
                            rotacao_dupla_direita_freq(raiz);
                        *cresceu = 0;
                        break;
                }
            }
            return 1;
        }
    }
    else if (info->frequencia_total > (*raiz)->frequencia) {
        // --- Inserir à DIREITA ---
        if (inserir_avl_freq(&((*raiz)->dir), info, cresceu)) {
            
            if (*cresceu) {
                switch ((*raiz)->fator_balanceamento) {
                    case 1:  (*raiz)->fator_balanceamento = 0; *cresceu = 0; break;
                    case 0:  (*raiz)->fator_balanceamento = -1; *cresceu = 1; break;
                    case -1: // Desbalanceou (-2)
                        if ((*raiz)->dir->fator_balanceamento == -1)
                            rotacao_simples_esquerda_freq(raiz);
                        else
                            rotacao_dupla_esquerda_freq(raiz);
                        *cresceu = 0;
                        break;
                }
            }
            return 1;
        }
    }
    else {
        // se a frequencia ja existe, diciona a palavra à lista encadeada do nó atual.
        adicionar_palavra_lista(&((*raiz)->palavras), info->palavra);
        *cresceu = 0; // altura da arvore nao mudou.
        return 1;
    }

    return 0;
}


No_AVL_Freq* buscar_avl_freq(ArvoreAVL_Freq raiz, int freq_busca) {
    // A frequência não foi encontrada.
    if (raiz == NULL) {
        return NULL;
    }

    // Encontramos o nó.
    if (freq_busca == raiz->frequencia) {
        return raiz;
    }

    else if (freq_busca < raiz->frequencia) {
        return buscar_avl_freq(raiz->esq, freq_busca);
    }

    else {
        return buscar_avl_freq(raiz->dir, freq_busca);
    }
}


