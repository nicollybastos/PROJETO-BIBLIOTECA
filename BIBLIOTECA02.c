/* 
PROJETO - SISTEMA DE BIBLIOTECA 02
*/

// Incluir bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes Globais
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

// Definicao da Estrutura (Struct)
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editor[TAM_STRING];
    int edicao;
    int disponivel;
};

// Armazernar Info de Emprestimo
struct Emprestimo {
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

// Limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao Principal
int main() {
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    emprestimos = (struct Emprestimo *) calloc(MAX_EMPRESTIMOS, sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL){
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        printf("==================================\n");
        printf("     BIBLIOTECA - PARTE 1\n");
        printf("==================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar emprestimo\n");
        printf("4 - Listar emprestimo\n");
        printf("0 - Sair\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {

            case 1:
                printf("\n--- Cadastro de Novo Livro ---\n\n");
                if (totalLivros < MAX_LIVROS) {

                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);
                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';

                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';

                    printf("Digite o editor: ");
                    fgets(biblioteca[totalLivros].editor, TAM_STRING, stdin);
                    biblioteca[totalLivros].editor[strcspn(biblioteca[totalLivros].editor, "\n")] = '\0';

                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();

                    biblioteca[totalLivros].disponivel = 1;

                    totalLivros++;
                    printf("\nLivro cadastrado com sucesso!\n\n");

                } else {
                    printf("\nBiblioteca cheia!\n\n");
                }
                break;

            case 2:
                printf("\n--- Lista de Livros Cadastrados ---\n\n");
                if (totalLivros == 0) {
                    printf("Nenhum livro foi cadastrado.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("---------------------------\n");
                        printf("Livro %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editor: %s\n", biblioteca[i].editor);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                    }
                    printf("---------------------------\n");
                }
                getchar();
                break;

            case 3:
                printf("--- Realizar Emprestimo ---\n");

                if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de emprestimos atingido!\n");
                } else {
                    int disponiveis = 0;

                    for (int i = 0; i < totalLivros; i++){
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("Nenhum livro disponível para empréstimo.\n");
                    } else {
                        int numLivro;
                        printf("Digite o numero do livro: ");
                        scanf("%d", &numLivro);
                        limparBufferEntrada();

                        int indice = numLivro - 1;

                        if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {

                            printf("Digite o nome do usuario: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalEmprestimos].nomeUsuario[
                                strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")
                            ] = '\0';

                            emprestimos[totalEmprestimos].indiceLivro = indice;
                            biblioteca[indice].disponivel = 0;
                            totalEmprestimos++;

                            printf("Emprestimo realizado com sucesso!\n");
                        } else {
                            printf("Livro invalido ou indisponível.\n");
                        }
                    }
                }
                break;

            case 4:
                printf("--- Lista de Emprestimos ---\n");

                if (totalEmprestimos == 0) {
                    printf("Nenhum emprestimo realizado.\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("-----------------------------\n");
                        printf("Emprestimo %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                    }
                    printf("-----------------------------\n");
                }
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    free(biblioteca);
    free(emprestimos);

    return 0;
}
