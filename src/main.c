#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Tipos.h"
#include "utils/utils.h"
#include "vetor_binario/vetor_binario.h"
#include "arvore_bst/arvore_bst.h"
#include "arvore_avl/arvore_avl.h"
#include "arvore_avl_frequencia/arvore_avl_frequencia.h"

void exibir_menu();
void imprimir_resultado(InfoPalavra* info);
void processar_carregamento_de_arquivo(InfoPalavra** p_vetor, int* p_tamanho_vetor, ArvoreBST* p_raiz_bst, ArvoreAVL* p_raiz_avl);
void processar_busca_de_palavra(InfoPalavra* vetor, int tamanho_vetor, ArvoreBST raiz_bst, ArvoreAVL raiz_avl);
void processar_busca_por_frequencia(InfoPalavra* vetor, int tamanho_vetor);


int main() {
    InfoPalavra* vetor_palavras = NULL;
    int tamanho_vetor = 0;
    ArvoreBST arvore_bst = criar_arvore_bst();
    ArvoreAVL arvore_avl = criar_arvore_avl();

    int opcao;

    do {
        exibir_menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                processar_carregamento_de_arquivo(&vetor_palavras, &tamanho_vetor, &arvore_bst, &arvore_avl);
                break;
            case 2:
                processar_busca_de_palavra(vetor_palavras, tamanho_vetor, arvore_bst, arvore_avl);
                break;
            case 3:
                processar_busca_por_frequencia(vetor_palavras, tamanho_vetor);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Por favor, tente novamente.\n");
        }
    } while (opcao != 0);

    printf("Liberando toda a memória alocada...\n");
    free(vetor_palavras);
    liberar_arvore_bst(arvore_bst);
    liberar_arvore_avl(arvore_avl);
    printf("Memória liberada. Programa encerrado.\n");

    return 0;
}









void exibir_menu() {
    printf("\n--------------------------------------\n");
    printf("    Repositório de Músicas - AED2\n");
    printf("--------------------------------------\n");
    printf("1. Carregar um arquivo de música\n");
    printf("2. Buscar por palavra\n");
    printf("3. Buscar por frequência\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

// Imprime as informações de uma palavra encontrada
void imprimir_resultado(InfoPalavra* info) {
    if (info == NULL) {
        printf("Palavra não encontrada.\n");
        return;
    }
    printf("  | Palavra: %s\n", info->palavra);
    printf("  | Frequência Total: %d\n", info->frequencia_total);
    printf("  | Música com maior ocorrência: '%s'\n", info->nome_musica);
    printf("  | Compositor: %s\n", info->nome_compositor);
    printf("  | Frequência nesta música: %d\n", info->frequencia_na_musica);
    printf("  | Estrofe: \"%.100s...\"\n", info->estrofe);
}

// Processa o item A do projeto: carregar dados de um arquivo nas 3 estruturas
void processar_carregamento_de_arquivo(InfoPalavra** p_vetor, int* p_tamanho_vetor, ArvoreBST* p_raiz_bst, ArvoreAVL* p_raiz_avl) {
    
    char nome_arquivo[100];
    printf("Digite o nome do arquivo de música para carregar (ex: LetrasMusicas/arquivo.txt): ");
    scanf("%99s", nome_arquivo);
    getchar(); 

    // PASSO 1: Processar o arquivo uma única vez para obter os dados brutos.
    printf("\nProcessando arquivo '%s'...\n", nome_arquivo);
    MusicaProcessada dados_musica = processar_arquivo(nome_arquivo);

    if (dados_musica.palavras == NULL) {
        printf("Não foi possível processar o arquivo. Verifique o nome e tente novamente.\n");
        return;
    }

    printf("Arquivo processado. Carregando dados nas estruturas...\n\n");

    clock_t inicio, fim;
    double tempo_gasto;

    // Medir o tempo de carregamento para cada estrutura
    
    // VETOR ---
    inicio = clock();
    carregar_dados_no_vetor(p_vetor, p_tamanho_vetor, &dados_musica);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio));
    printf("VETOR - Tempo de carregamento: %f\n", tempo_gasto);

    // BST ---
    inicio = clock();
    carregar_dados_na_bst(p_raiz_bst, &dados_musica);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio));
    printf("BST - Tempo de carregamento: %f\n", tempo_gasto);
    
    // AVL ---
    inicio = clock();
    carregar_dados_na_avl(p_raiz_avl, &dados_musica);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio));
    printf("AVL - Tempo de carregamento: %f\n", tempo_gasto);

    
    free(dados_musica.palavras);
    printf("\nCarga de dados concluída.\n");
}

// Processa o item B do projeto: buscar uma palavra nas 3 estruturas
void processar_busca_de_palavra(InfoPalavra* vetor, int tamanho_vetor, ArvoreBST raiz_bst, ArvoreAVL raiz_avl) {
    char palavra_a_ser_buscada[50];
    printf("\nDigite a palavra que deseja buscar: ");
    scanf("%49s", palavra_a_ser_buscada);
    getchar(); 

    string_para_minusculo(palavra_a_ser_buscada);

    printf("\n--- Realizando busca pela palavra '%s' ---\n\n", palavra_a_ser_buscada);

    InfoPalavra* resultado_encontrado = NULL;
    clock_t inicio, fim;
    double tempo_gasto;

  
    printf("--- Vetor Ordenado ---\n");
    inicio = clock();
    int indice_vetor = busca_binaria(vetor, tamanho_vetor, palavra_a_ser_buscada);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio));
    printf("Tempo de busca: %f\n", tempo_gasto);

    if (indice_vetor != -1) {
        // A busca no vetor retorna um índice, então passamos o endereço do elemento.
        imprimir_resultado(&vetor[indice_vetor]);
    } else {
        printf("Palavra não encontrada.\n");
    }

  
    printf("\n--- Árvore BST ---\n");
    inicio = clock();
    resultado_encontrado = buscar_bst(raiz_bst, palavra_a_ser_buscada);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio));
    printf("Tempo de busca: %f\n", tempo_gasto);
    imprimir_resultado(resultado_encontrado); 


    printf("\n--- Árvore AVL ---\n");
    inicio = clock();
    resultado_encontrado = buscar_avl(raiz_avl, palavra_a_ser_buscada);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio));
    printf("Tempo de busca: %f\n", tempo_gasto);
    imprimir_resultado(resultado_encontrado);
}

void processar_busca_por_frequencia(InfoPalavra* vetor, int tamanho_vetor) {
    printf("\nBuscar por frequência: \n");

    if (vetor == NULL || tamanho_vetor == 0) {
        printf("Nenhum dado carregado. Por favor, carregue um arquivo primeiro (opção 1).\n");
        return;
    }

    // uma nova árvore AVL para as frequencias 
    ArvoreAVL_Freq arvore_frequencia = criar_arvore_avl_freq();

    // Iterar sobre o vetor e popular a nova árvore
    printf("Construindo índice de frequências...\n");
    clock_t inicio_build, fim_build;
    inicio_build = clock();

    for (int i = 0; i < tamanho_vetor; i++) {
        int cresceu = 0; 
        inserir_avl_freq(&arvore_frequencia, &vetor[i], &cresceu);
    }

    fim_build = clock();
    double tempo_build = ((double)(fim_build - inicio_build)) / CLOCKS_PER_SEC;
    printf("Índice de frequências construído em %f segundos.\n", tempo_build);

    // Pedir ao usuário a frequência desejada.
    int freq_desejada;
    printf("\nDigite a frequência total que deseja buscar: ");
    scanf("%d", &freq_desejada);
    getchar(); 

    // Realizar a busca por frequência 
    printf("Buscando por palavras com frequência exata de %d...\n", freq_desejada);
    No_AVL_Freq* no_resultado = buscar_avl_freq(arvore_frequencia, freq_desejada);

    if (no_resultado != NULL) {
        printf("Palavras encontradas:\n");
        ListaPalavras* atual = no_resultado->palavras;
        int contador = 0;
        while (atual != NULL) {
            printf(" - %s\n", atual->palavra);
            atual = atual->prox;
            contador++;
        }
        printf("(Total: %d palavras com esta frequência)\n", contador);
    } else {
        printf("Nenhuma palavra foi encontrada com essa frequência no repositório.\n");
    }

    liberar_arvore_avl_freq(arvore_frequencia);
}

