#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

#define TAM_LINHA 256

// Função para ler teclado sem apertar Enter (Nativa do Linux)
char getch(void) {
    char buf = 0;
    struct termios old = {0};
    tcgetattr(0, &old);
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &old);
    read(0, &buf, 1);
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    tcsetattr(0, TCSADRAIN, &old);
    return buf;
}

// Trata a entrada: extrai só números, valida se tem 8 dígitos e insere o traço
int tratar_cep(const char *entrada, char *cep_formatado) {
    char apenas_numeros[10];
    int count = 0;

    // Filtra apenas os números da entrada
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (isdigit(entrada[i])) {
            if (count < 8) {
                apenas_numeros[count] = entrada[i];
            }
            count++;
        }
    }

    // Se não tiver exatamente 8 números, é inválido
    if (count != 8) {
        return 0; 
    }

    // Formata o array destino colocando o traço XXXXX-XXX
    sprintf(cep_formatado, "%c%c%c%c%c-%c%c%c", 
            apenas_numeros[0], apenas_numeros[1], apenas_numeros[2], apenas_numeros[3], apenas_numeros[4], 
            apenas_numeros[5], apenas_numeros[6], apenas_numeros[7]);

    return 1;
}

void buscar_por_cep(const char *cep_alvo) {
    FILE *arquivo = fopen("base.txt", "r");
    if (!arquivo) {
        printf("Erro: Arquivo 'base.txt' nao encontrado.\n");
        return;
    }

    char linha[TAM_LINHA];
    char cpf[15], nome[100], cep[10];
    int encontrados = 0;

    printf("\n=== Moradores do CEP: %s ===\n", cep_alvo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0; 
        
        char *token = strtok(linha, ";");
        if (token) strcpy(cpf, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(nome, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(cep, token);

        if (strcmp(cep, cep_alvo) == 0) {
            printf("Nome: %-20s | CPF: %-14s\n", nome, cpf);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum morador encontrado.\n");
    } else {
        printf("---------------------------------\n");
        printf("Total de entregas no local: %d\n", encontrados);
    }

    fclose(arquivo);
}

int main() {
    char opcao;
    char entrada_cep[20];
    char cep_busca[10];

    do {
        system("clear");
        printf("=================================\n");
        printf("        SISTEMA CORREIOS         \n");
        printf("=================================\n");
        printf("[1] Buscar pessoas para entrega no CEP\n");
        printf("[2] Abrir base.txt\n");
        printf("[0] Sair\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");

        opcao = getch();

        if (opcao == '1') {
            printf("1\n\n");
            
            // Loop de validação do CEP
            while (1) {
                printf("Digite o CEP para a rota de entrega (com ou sem traco): ");
                scanf("%19s", entrada_cep);
                
                // Limpa o '\n' do buffer
                while (getchar() != '\n'); 

                if (tratar_cep(entrada_cep, cep_busca)) {
                    break; // Sai do loop se o CEP for válido
                } else {
                    printf("\n[Erro] CEP invalido! O CEP deve conter exatamente 8 numeros.\n\n");
                }
            }
            
            buscar_por_cep(cep_busca);
            
            printf("\nPressione qualquer tecla para voltar ao menu...");
            getch();
        } 
        else if (opcao == '2') {
            printf("2\n\nAbrindo base.txt no editor padrao...\n");
            system("xdg-open base.txt"); 
            
            printf("\nPressione qualquer tecla para voltar ao menu...");
            getch();
        }

    } while (opcao != '0');

    system("clear");
    printf("Saindo do sistema...\n");
    return 0;
}
