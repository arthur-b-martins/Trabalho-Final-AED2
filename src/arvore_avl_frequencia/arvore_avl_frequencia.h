#ifndef AVL_FREQ_H
#define AVL_FREQ_H

#include "../Tipos.h"

// Nó da lista encadeada para palavras com a mesma frequência
typedef struct ListaPalavras {
    char palavra[50];
    struct ListaPalavras* prox;
} ListaPalavras;

typedef struct No_AVL_Freq {
    int frequencia;             
    ListaPalavras* palavras;      
    struct No_AVL_Freq* esq;
    struct No_AVL_Freq* dir;
    int fator_balanceamento;
} No_AVL_Freq;

typedef No_AVL_Freq* ArvoreAVL_Freq;

ArvoreAVL_Freq criar_arvore_avl_freq();
void liberar_arvore_avl_freq(ArvoreAVL_Freq raiz);
int inserir_avl_freq(ArvoreAVL_Freq* raiz, InfoPalavra* info, int* cresceu);
No_AVL_Freq* buscar_avl_freq(ArvoreAVL_Freq raiz, int freq_busca);

#endif