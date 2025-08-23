#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "../Tipos.h" 

typedef struct No_AVL {
    InfoPalavra info;           
    struct No_AVL* esq;         
    struct No_AVL* dir;         
    int fator_balanceamento;    // (hE - hD)
} No_AVL;

typedef No_AVL* ArvoreAVL;


ArvoreAVL criar_arvore_avl();
void liberar_arvore_avl(ArvoreAVL raiz);
int inserir_avl(ArvoreAVL* raiz, InfoPalavra info, int* cresceu);
InfoPalavra* buscar_avl(ArvoreAVL raiz, char* palavra);

#endif 