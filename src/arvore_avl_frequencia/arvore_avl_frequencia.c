#include "arvore_avl_frequencia.h"
#include <stdlib.h>

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

