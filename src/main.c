#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "busca.h"
#include "arquivo.h"

// --- SEÇÃO DE PORTABILIDADE (LINUX / WINDOWS) ---
#ifdef _WIN32
    #include <conio.h> // Nativo do Windows para getch()
    #define CLEAR_SCREEN "cls"
#else
    #include <termios.h> // Necessário para emular getch() no Linux
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"

    // Implementação do getch para sistemas POSIX (Linux/MacOS)
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
#endif
// ------------------------------------------------

// Função auxiliar para tratar e validar o CEP digitado
int tratar_cep(const char *entrada, char *cep_formatado) {
    char apenas_numeros[10];
    int count = 0;

    for (int i = 0; entrada[i] != '\0'; i++) {
        if (isdigit(entrada[i])) {
            if (count < 8) {
                apenas_numeros[count] = entrada[i];
            }
            count++;
        }
    }

    if (count != 8) {
        return 0; 
    }

    sprintf(cep_formatado, "%c%c%c%c%c-%c%c%c", 
            apenas_numeros[0], apenas_numeros[1], apenas_numeros[2], apenas_numeros[3], apenas_numeros[4], 
            apenas_numeros[5], apenas_numeros[6], apenas_numeros[7]);

    return 1;
}

int main() {
    // Declaração e inicialização da Tabela Hash em memória
    Morador *tabela[TAM_HASH];
    inicializar_tabela(tabela);

    // Carregamento inicial: Lê o ficheiro base.txt uma única vez
    printf("Carregando base de dados, por favor aguarde...\n");
    carregar_base(tabela);

    char opcao;
    char entrada_cep[20];
    char cep_busca[10];

    do {
        system(CLEAR_SCREEN);
        printf("=================================\n");
        printf("     SISTEMA CORREIOS (G13)      \n");
        printf("=================================\n");
        printf("[1] Buscar pessoas por CEP (Hash)\n");
        printf("[2] Abrir ficheiro base.txt\n");
        printf("[0] Sair\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");

        opcao = getch();

        if (opcao == '1') {
            printf("1\n\n");
            
            while (1) {
                printf("Digite o CEP para a rota de entrega: ");
                scanf("%19s", entrada_cep);
                
                while (getchar() != '\n'); // Limpa buffer do teclado

                if (tratar_cep(entrada_cep, cep_busca)) {
                    break; 
                } else {
                    printf("\n[Erro] CEP invalido! Digite os 8 numeros.\n\n");
                }
            }
            
            // Realiza a busca otimizada na Tabela Hash (O(1) médio)
            buscar_na_hash(tabela, cep_busca);
            
            printf("\nPressione qualquer tecla para voltar ao menu...");
            getch();
        } 
        else if (opcao == '2') {
            printf("2\n\nAbrindo base.txt...\n");
            #ifdef _WIN32
                system("start data/base.txt"); 
            #else
                system("xdg-open data/base.txt"); 
            #endif
            
            printf("\nPressione qualquer tecla para voltar ao menu...");
            getch();
        }

    } while (opcao != '0');

    // Liberta a memória alocada antes de encerrar
    liberar_tabela(tabela);

    system(CLEAR_SCREEN);
    printf("Saindo do sistema...\n");
    return 0;
}