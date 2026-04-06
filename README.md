# Sistema de Busca - Correios

**Número da Lista:** 13 (Busca)<br>
**Conteúdo da Disciplina:** Algoritmos de Busca, Hashing e Estruturas de Dados<br>

## Alunos
| Matrícula | Aluno |
| -- | -- |
| 23/2005343 | Marcos Filho Pereira Quixabeira |
| 23/2027476 | João Guilherme Capozzi |

## Sobre 
O objetivo deste projeto é implementar um sistema de busca otimizado para entregas dos Correios. O programa processa uma base de dados de moradores (`base.txt`) e permite localizar pessoas associadas a um determinado CEP. O sistema aceita CEPs em múltiplos formatos (ex: `72444000` ou `72444-000`), realizando a limpeza e validação da entrada antes da consulta.

### ⚡ Análise de Complexidade (Evolução Técnica)
Inicialmente, o sistema utilizava **Busca Sequencial** diretamente no arquivo de texto, o que resultava numa complexidade de tempo $\mathcal{O}(n)$, sendo ineficiente para bases de dados grandes. 

Para atingir os requisitos de eficiência da disciplina, o projeto foi refatorado para utilizar uma **Tabela Hash com Encadeamento Aberto**. 
* **Carregamento:** Ao iniciar, o sistema lê o arquivo uma única vez e aloca os dados na Tabela Hash em memória.
* **Busca:** Após o carregamento, as consultas de CEP possuem complexidade de tempo média **$\mathcal{O}(1)$**, tornando a resposta virtualmente instantânea, independentemente do volume de moradores.

## Screenshots
*(Adicione aqui os links para as imagens do sistema a funcionar. Exemplo: `![Menu](caminho/para/imagem.png)`)*
1. **[Screenshot 1 - Menu Principal e Carregamento]**: Mostrando a inicialização da Tabela Hash e as opções do sistema.
2. **[Screenshot 2 - Busca com Sucesso]**: Exibindo os moradores localizados e a contagem total para um CEP válido.
3. **[Screenshot 3 - Validação de Erro]**: Mostrando a mensagem de segurança quando o utilizador digita um CEP inválido (ex: letras ou tamanho errado).

## Instalação 
**Linguagem:** C (Padrão C99 ou superior)<br>
**Framework:** Nenhum (Código nativo modularizado)<br>

### Pré-requisitos
* Compilador GCC instalado.
* Ambiente Linux, macOS ou Windows.
* A base de dados `base.txt` deve estar dentro de uma pasta chamada `data/` na raiz do projeto.

### Comandos de Execução
O projeto foi modularizado, pelo que a compilação requer a interligação dos ficheiros. Utilize o `Makefile` incluído para compilar e executar rapidamente:

1. Compile o código:
   ```bash
   make