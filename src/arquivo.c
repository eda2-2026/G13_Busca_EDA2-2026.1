#include <stdio.h>
#include <string.h>
#include "busca.h"
#include "arquivo.h"

// A implementação real da função
void carregar_base(Morador *tabela[]) {
    FILE *arquivo = fopen("data/base.txt", "r");
    if (!arquivo) {
        printf("Aviso: Arquivo base.txt não encontrado.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0; // Remove a quebra de linha
        char *cpf = strtok(linha, ";");
        char *nome = strtok(NULL, ";");
        char *cep = strtok(NULL, ";");
        
        if (cpf && nome && cep) {
            inserir_hash(tabela, cpf, nome, cep);
        }
    }
    fclose(arquivo);
}