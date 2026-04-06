#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"

unsigned int funcao_hash(const char *cep) {
    unsigned int hash = 0;
    while (*cep) {
        hash = (hash * 31) + *cep++;
    }
    return hash % TAM_HASH;
}

void inicializar_tabela(Morador *tabela[]) {
    for (int i = 0; i < TAM_HASH; i++) tabela[i] = NULL;
}

void inserir_hash(Morador *tabela[], const char *cpf, const char *nome, const char *cep) {
    unsigned int indice = funcao_hash(cep);
    Morador *novo = (Morador *)malloc(sizeof(Morador));
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome, nome);
    strcpy(novo->cep, cep);
    
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

void buscar_na_hash(Morador *tabela[], const char *cep_alvo) {
    unsigned int indice = funcao_hash(cep_alvo);
    Morador *atual = tabela[indice];
    int encontrados = 0;

    printf("\n=== Moradores do CEP: %s ===\n", cep_alvo);
    while (atual != NULL) {
        if (strcmp(atual->cep, cep_alvo) == 0) {
            printf("Nome: %-20s | CPF: %-14s\n", atual->nome, atual->cpf);
            encontrados++;
        }
        atual = atual->prox;
    }

    if (encontrados == 0) printf("Nenhum morador encontrado.\n");
    else printf("---------------------------------\nTotal: %d\n", encontrados);
}

void liberar_tabela(Morador *tabela[]) {
    for (int i = 0; i < TAM_HASH; i++) {
        Morador *atual = tabela[i];
        while (atual != NULL) {
            Morador *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}