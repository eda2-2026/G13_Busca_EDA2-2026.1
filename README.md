# Sistema de Busca - Correios

**Número da Lista:** 13 (Busca)<br>
[cite_start]**Conteúdo da Disciplina:** Algoritmos de Busca, Hashing e Estruturas de Dados [cite: 1, 14, 118]<br>

## Alunos
| Matrícula | Aluno |
| -- | -- |
| 23/2005343 | Marcos Filho Pereira Quixabeira |
| 23/2027476 | João Guilherme Capozzi |

## Sobre 
O objetivo deste projeto é implementar um sistema de busca de entregas para os Correios. O programa processa uma base de dados de moradores (`base.txt`) e permite localizar pessoas associadas a um determinado CEP. 

O sistema aplica conceitos de busca sequencial em arquivos de texto e tratamento de strings para normalização de chaves de busca (CEPs com ou sem hífen).

## Screenshots
*(Adicione aqui os links para as imagens após rodar o programa)*
1. [Screenshot do Menu Principal]
2. [Screenshot do Resultado de Busca por CEP]
3. [Screenshot de Validação de CEP Inválido]

## Instalação 
**Linguagem:** C (Padrão C99 ou superior)<br>
**Framework:** Nenhum (Código nativo)<br>

### Pré-requisitos
* Compilador GCC instalado.
* O arquivo `base.txt` deve estar no mesmo diretório do executável.

### Comandos de Execução
1. Compile o código:
   ```bash
   gcc buscaCorreios.c -o buscaCorreios