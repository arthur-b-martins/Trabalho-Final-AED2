#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

// item A do projeto: carregar dados de um arquivo nas 3 estruturas
void processar_carregamento_de_arquivo(InfoPalavra** p_vetor, int* p_tamanho_vetor, ArvoreBST* p_raiz_bst, ArvoreAVL* p_raiz_avl) {
    
    char nome_arquivo[100];
    printf("Digite o nome do arquivo de música para carregar (ex: LetrasMusicas/arquivo.txt): ");
    scanf("%99s", nome_arquivo);
    getchar(); 

    printf("\nProcessando arquivo '%s'...\n", nome_arquivo);
    MusicaProcessada dados_musica = processar_arquivo(nome_arquivo);

    if (dados_musica.palavras == NULL) {
        printf("Não foi possível processar o arquivo. Verifique o nome e tente novamente.\n");
        return;
    }

    printf("Arquivo processado. Carregando dados nas estruturas...\n\n");

    // --- Variáveis para a medição de alta precisão ---
    LARGE_INTEGER frequencia;
    LARGE_INTEGER inicio, fim;
    double tempo_gasto;

    // frequência do contador
    QueryPerformanceFrequency(&frequencia);

    // --- VETOR ---
    QueryPerformanceCounter(&inicio); 
    carregar_dados_no_vetor(p_vetor, p_tamanho_vetor, &dados_musica);
    QueryPerformanceCounter(&fim);  
    tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("VETOR - Tempo de carregamento (alta precisão): %.10f segundos\n", tempo_gasto);

    // --- BST ---
    QueryPerformanceCounter(&inicio);
    carregar_dados_na_bst(p_raiz_bst, &dados_musica);
    QueryPerformanceCounter(&fim);
    tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("BST   - Tempo de carregamento (alta precisão): %.10f segundos\n", tempo_gasto);
    
    // --- AVL ---
    QueryPerformanceCounter(&inicio);
    carregar_dados_na_avl(p_raiz_avl, &dados_musica);
    QueryPerformanceCounter(&fim);
    tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("AVL   - Tempo de carregamento (alta precisão): %.10f segundos\n", tempo_gasto);

    
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

    LARGE_INTEGER frequencia;
    LARGE_INTEGER inicio, fim;
    double tempo_gasto;

    QueryPerformanceFrequency(&frequencia);

    printf("--- Vetor Ordenado ---\n");
    QueryPerformanceCounter(&inicio);
    int indice_vetor = busca_binaria(vetor, tamanho_vetor, palavra_a_ser_buscada);
    QueryPerformanceCounter(&fim);
    tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("Tempo de busca: %.10f segundos\n", tempo_gasto);

    if (indice_vetor != -1) {
        imprimir_resultado(&vetor[indice_vetor]);
    } else {
        printf("Palavra não encontrada.\n");
    }

    printf("\n--- Árvore BST ---\n");
    QueryPerformanceCounter(&inicio);
    InfoPalavra* resultado_encontrado_bst = buscar_bst(raiz_bst, palavra_a_ser_buscada);
    QueryPerformanceCounter(&fim);
    tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("Tempo de busca: %.10f segundos\n", tempo_gasto);
    imprimir_resultado(resultado_encontrado_bst); 

    printf("\n--- Árvore AVL ---\n");
    QueryPerformanceCounter(&inicio);
    InfoPalavra* resultado_encontrado_avl = buscar_avl(raiz_avl, palavra_a_ser_buscada);
    QueryPerformanceCounter(&fim);
    tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("Tempo de busca: %.10f segundos\n", tempo_gasto);
    imprimir_resultado(resultado_encontrado_avl);
}


void processar_busca_por_frequencia(InfoPalavra* vetor, int tamanho_vetor) {
    printf("\n[TAREFA 3: BUSCAR POR FREQUÊNCIA]\n");

    if (vetor == NULL || tamanho_vetor == 0) {
        printf("Nenhum dado carregado. Por favor, carregue um arquivo primeiro (opção 1).\n");
        return;
    }

    LARGE_INTEGER frequencia;
    LARGE_INTEGER inicio, fim;
    double tempo_gasto;

    QueryPerformanceFrequency(&frequencia);

    //Criar e popular a nova arvore medindo o tempo.
    ArvoreAVL_Freq arvore_frequencia = criar_arvore_avl_freq();
    printf("Construindo índice de frequências...\n");

    QueryPerformanceCounter(&inicio);
    for (int i = 0; i < tamanho_vetor; i++) {
        int cresceu = 0;
        inserir_avl_freq(&arvore_frequencia, &vetor[i], &cresceu);
    }
    QueryPerformanceCounter(&fim);

    tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("Índice de frequências construído em %.10f segundos.\n", tempo_gasto);

    // Pedir ao usuário a frequência desejada.
    int freq_desejada;
    printf("\nDigite a frequência total que deseja buscar: ");
    scanf("%d", &freq_desejada);
    getchar(); 

    // Realizar a busca
    printf("Buscando por palavras com frequência exata de %d...\n", freq_desejada);
    
    QueryPerformanceCounter(&inicio);
    No_AVL_Freq* no_resultado = buscar_avl_freq(arvore_frequencia, freq_desejada);
    QueryPerformanceCounter(&fim);   

    tempo_gasto = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("Tempo de busca no índice: %.10f segundos.\n", tempo_gasto);

    // 4. Exibir os resultados.
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