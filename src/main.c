#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Tipos.h"
#include "utils/utils.h"
#include "vetor_binario/vetor_binario.h"
#include "arvore_bst/arvore_bst.h"
#include "arvore_avl/arvore_avl.h"

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

    // PASSO 2: Medir o tempo de carregamento para cada estrutura.
    
    // --- VETOR ---
    inicio = clock();
    // carregar_dados_no_vetor(p_vetor, p_tamanho_vetor, &dados_musica);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("[VETOR] Tempo de carregamento: %f segundos\n", tempo_gasto);

    // --- BST ---
    inicio = clock();
    carregar_dados_na_bst(p_raiz_bst, &dados_musica);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("[BST]   Tempo de carregamento: %f segundos\n", tempo_gasto);
    
    // --- AVL ---
    inicio = clock();
    carregar_dados_na_avl(p_raiz_avl, &dados_musica);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("[AVL]   Tempo de carregamento: %f segundos\n", tempo_gasto);

    
    free(dados_musica.palavras);
    printf("\nCarga de dados concluída.\n");
}

// Processa o item B do projeto: buscar uma palavra nas 3 estruturas
void processar_busca_de_palavra(InfoPalavra* vetor, int tamanho_vetor, ArvoreBST raiz_bst, ArvoreAVL raiz_avl) {
    printf("\n[TAREFA 2: BUSCAR PALAVRA]\n");
    // ALUNO: Implementar esta função.
    // 1. Pedir ao usuário a palavra que deseja buscar.
    // 2. Medir o tempo da busca em cada uma das 3 estruturas.
    //    - Chamar busca_binaria() para o vetor.
    //    - Chamar buscar_bst() para a BST.
    //    - Chamar buscar_avl() para a AVL.
    // 3. Para cada estrutura, imprimir o tempo de busca e o resultado encontrado usando a função 'imprimir_resultado()'.
    printf(">> Funcionalidade ainda não implementada.\n");
}

// Processa o item C do projeto: buscar por frequência
void processar_busca_por_frequencia(InfoPalavra* vetor, int tamanho_vetor) {
    printf("\n[TAREFA 3: BUSCAR POR FREQUÊNCIA]\n");
    // ALUNO: Implementar esta função (etapa mais avançada).
    // 1. Criar uma nova árvore AVL (ArvoreAVL_Freq).
    // 2. Iterar sobre o vetor de InfoPalavra e inserir cada elemento na nova árvore,
    //    mas usando 'frequencia_total' como chave de comparação.
    // 3. Pedir ao usuário a frequência desejada.
    // 4. Realizar a busca por frequência na nova árvore e exibir os resultados.
    // 5. Liberar a memória da ArvoreAVL_Freq no final.
    printf(">> Funcionalidade ainda não implementada.\n");
}

