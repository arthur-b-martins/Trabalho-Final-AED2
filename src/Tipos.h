#ifndef DADOS_H
#define DADOS_H

#define TAMANHO_ESTROFE 101 // 100 caracteres + 1 para o '\0'

typedef struct {
    char palavra[50];
    
    // Dados da música com a maior frequência para esta palavra
    char nome_musica[100];
    char nome_compositor[100];
    char estrofe[TAMANHO_ESTROFE];
    int frequencia_na_musica;

    // Contagem geral da palavra em todas as músicas
    int frequencia_total;
} InfoPalavra;

typedef struct {
    char palavra[50];
    char estrofe_primeira_ocorrencia[101];
    int freq_na_musica;
} TempPalavra;

// Struct para o retorno da função genérica
typedef struct {
    TempPalavra* palavras;
    int tamanho;
    char nome_musica[100];
    char nome_compositor[100];
} MusicaProcessada;


#endif