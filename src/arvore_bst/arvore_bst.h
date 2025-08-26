#ifndef ARVORE_BST_H
#define ARVORE_BST_H

#include "../Tipos.h"

// Struct do nó da Árvore Binária de Busca
typedef struct No_BST {
    InfoPalavra info;           
    struct No_BST* esq;         
    struct No_BST* dir;         
} No_BST;

// A arvore é um ponteiro para o nó raiz.
typedef No_BST* ArvoreBST;


ArvoreBST criar_arvore_bst();
void liberar_arvore_bst(ArvoreBST raiz);
int inserir_bst(ArvoreBST* raiz, InfoPalavra info);
InfoPalavra* buscar_bst(ArvoreBST raiz, char* palavra);
void carregar_dados_na_bst(ArvoreBST* p_raiz, MusicaProcessada* dados_musica);

#endif