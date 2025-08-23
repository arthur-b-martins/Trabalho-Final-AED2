#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_avl.h"

ArvoreAVL criar_arvore_avl() {
    return NULL;
}

void liberar_arvore_avl(ArvoreAVL raiz){
    if(raiz != NULL){
        liberar_arvore_avl(raiz->dir);
        liberar_arvore_avl(raiz->esq);
        free(raiz);
    }
}

static void rotacao_simples_direita(ArvoreAVL* raiz) {
    No_AVL* p = (*raiz)->esq;
    (*raiz)->esq = p->dir;
    p->dir = *raiz;
    (*raiz)->fator_balanceamento = 0; 
    p->fator_balanceamento = 0;
    *raiz = p;
}

static void rotacao_simples_esquerda(ArvoreAVL* raiz) {
    No_AVL* p = (*raiz)->dir;
    (*raiz)->dir = p->esq;
    p->esq = *raiz;
    (*raiz)->fator_balanceamento = 0;
    p->fator_balanceamento = 0;
    *raiz = p;
}

// Rotação para desbalanceamento Esquerda-Direita (ED)
static void rotacao_dupla_direita(ArvoreAVL* raiz) {
    No_AVL* u = (*raiz)->esq;
    No_AVL* v = u->dir;

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
static void rotacao_dupla_esquerda(ArvoreAVL* raiz) {
    No_AVL* u = (*raiz)->dir;
    No_AVL* v = u->esq;

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

int inserir_avl(ArvoreAVL* raiz, InfoPalavra info, int* cresceu) {
    // CASO BASE: A árvore (ou sub-árvore) está vazia. Ponto de inserção.
    if (*raiz == NULL) {
        No_AVL* novo_no = (No_AVL*) malloc(sizeof(No_AVL));
        if (novo_no == NULL) {
            *cresceu = 0;
            return 0;
        }
        novo_no->info = info;
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        novo_no->fator_balanceamento = 0; // Nó folha tem FB 0
        *raiz = novo_no;
        *cresceu = 1; // Sinaliza que a sub-árvore cresceu em altura
        return 1; // Sucesso
    }

    int comp = strcmp(info.palavra, (*raiz)->info.palavra);

    // PALAVRA JÁ EXISTE: Lógica de atualização, não altera a estrutura.
    if (comp == 0) {
        (*raiz)->info.frequencia_total += info.frequencia_na_musica;
        if (info.frequencia_na_musica > (*raiz)->info.frequencia_na_musica) {
            // Atualiza dados da música
            (*raiz)->info.frequencia_na_musica = info.frequencia_na_musica;
            strcpy((*raiz)->info.nome_musica, info.nome_musica);
            strcpy((*raiz)->info.nome_compositor, info.nome_compositor);
            strcpy((*raiz)->info.estrofe, info.estrofe);
        }
        *cresceu = 0; // A altura da árvore não mudou
        return 1; // Sucesso na atualização
    }

    // NAVEGAÇÃO RECURSIVA PARA A ESQUERDA
    if (comp < 0) {
        if (inserir_avl(&((*raiz)->esq), info, cresceu)) {
            // -- A "VOLTA" DA RECURSÃO PELA ESQUERDA --
            if (*cresceu) { // Se a sub-árvore esquerda cresceu...
                switch ((*raiz)->fator_balanceamento) {
                    case -1: // Estava pendendo para a direita, agora ficou balanceado
                        (*raiz)->fator_balanceamento = 0;
                        *cresceu = 0;
                        break;
                    case 0: // Estava balanceado, agora pende para a esquerda
                        (*raiz)->fator_balanceamento = 1;
                        *cresceu = 1;
                        break;
                    case 1: // Já pendia para a esquerda, agora desbalanceou! (+2)
                        if ((*raiz)->esq->fator_balanceamento == 1) // Caso Esquerda-Esquerda
                            rotacao_simples_direita(raiz);
                        else // Caso Esquerda-Direita
                            rotacao_dupla_direita(raiz);
                        *cresceu = 0;
                        break;
                }
            }
            return 1;
        }
    }
    // NAVEGAÇÃO RECURSIVA PARA A DIREITA
    else {
        if (inserir_avl(&((*raiz)->dir), info, cresceu)) {
            // -- A "VOLTA" DA RECURSÃO PELA DIREITA --
            if (*cresceu) { // Se a sub-árvore direita cresceu...
                switch ((*raiz)->fator_balanceamento) {
                    case 1: // Estava pendendo para a esquerda, agora ficou balanceado
                        (*raiz)->fator_balanceamento = 0;
                        *cresceu = 0;
                        break;
                    case 0: // Estava balanceado, agora pende para a direita
                        (*raiz)->fator_balanceamento = -1;
                        *cresceu = 1;
                        break;
                    case -1: // Já pendia para a direita, agora desbalanceou! (-2)
                        if ((*raiz)->dir->fator_balanceamento == -1) // Caso Direita-Direita
                            rotacao_simples_esquerda(raiz);
                        else // Caso Direita-Esquerda
                            rotacao_dupla_esquerda(raiz);
                        *cresceu = 0;
                        break;
                }
            }
            return 1;
        }
    }

    return 0; // Algo deu errado
}

