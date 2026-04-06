#ifndef BUSCA_H
#define BUSCA_H

typedef struct morador {
    char cpf[15];
    char nome[100];
    char cep[10];
    struct morador *prox; // Ponteiro para tratar colisões (Encadeamento)
} Morador;

#define TAM_HASH 1001 // Tamanho primo para reduzir colisões

// Prototipagem das funções
unsigned int funcao_hash(const char *cep);
void inicializar_tabela(Morador *tabela[]);
void inserir_hash(Morador *tabela[], const char *cpf, const char *nome, const char *cep);
void buscar_na_hash(Morador *tabela[], const char *cep_alvo);
void liberar_tabela(Morador *tabela[]);

#endif