/*
SISTEMA DE BIBLIOTECA - PARTE 3

OBJETIVOS:
- Modularizar o código com funções especializadas
- Passagem por valor (exibição) e por referência (modificação)
- Funções para cada funcionalidade principal
- main() como orquestrador
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

// Struct Livro
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editor[TAM_STRING];
    int edicao;
    int disponivel;
};

// Struct Empréstimo
struct Emprestimo {
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

// Protótipos
void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int totalLivros);
void realizarEmprestimo(struct Livro *biblioteca, int totalLivros,
                        struct Emprestimo *emprestimos, int *totalEmprestimos);
void listarEmprestimos(const struct Livro *biblioteca,
                       const struct Emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos);

// Função principal
int main() {
    struct Livro *biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    struct Emprestimo *emprestimos = (struct Emprestimo *) calloc(MAX_EMPRESTIMOS, sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarLivro(biblioteca, &totalLivros);
                break;
            case 2:
                listarLivros(biblioteca, totalLivros);
                break;
            case 3:
                realizarEmprestimo(biblioteca, totalLivros, emprestimos, &totalEmprestimos);
                break;
            case 4:
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    liberarMemoria(biblioteca, emprestimos);
    return 0;
}

// ================= FUNÇÕES =================

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("\n==================================\n");
    printf("        SISTEMA DE BIBLIOTECA\n");
    printf("==================================\n");
    printf("1 - Cadastrar novo livro\n");
    printf("2 - Listar livros\n");
    printf("3 - Realizar emprestimo\n");
    printf("4 - Listar emprestimos\n");
    printf("0 - Sair\n");
    printf("----------------------------------\n");
    printf("Escolha uma opcao: ");
}

void cadastrarLivro(struct Livro *biblioteca, int *totalLivros) {
    if (*totalLivros >= MAX_LIVROS) {
        printf("Biblioteca cheia!\n");
        return;
    }

    printf("\n--- Cadastro de Livro ---\n");

    printf("Nome do livro: ");
    fgets(biblioteca[*totalLivros].nome, TAM_STRING, stdin);
    biblioteca[*totalLivros].nome[strcspn(biblioteca[*totalLivros].nome, "\n")] = '\0';

    printf("Autor: ");
    fgets(biblioteca[*totalLivros].autor, TAM_STRING, stdin);
    biblioteca[*totalLivros].autor[strcspn(biblioteca[*totalLivros].autor, "\n")] = '\0';

    printf("Editor: ");
    fgets(biblioteca[*totalLivros].editor, TAM_STRING, stdin);
    biblioteca[*totalLivros].editor[strcspn(biblioteca[*totalLivros].editor, "\n")] = '\0';

    printf("Edicao: ");
    scanf("%d", &biblioteca[*totalLivros].edicao);
    limparBufferEntrada();

    biblioteca[*totalLivros].disponivel = 1;
    (*totalLivros)++;

    printf("Livro cadastrado com sucesso!\n");
}

void listarLivros(const struct Livro *biblioteca, int totalLivros) {
    printf("\n--- Lista de Livros ---\n");

    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalLivros; i++) {
        printf("\nLivro %d\n", i + 1);
        printf("Nome: %s\n", biblioteca[i].nome);
        printf("Autor: %s\n", biblioteca[i].autor);
        printf("Editor: %s\n", biblioteca[i].editor);
        printf("Edicao: %d\n", biblioteca[i].edicao);
        printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
    }
}

void realizarEmprestimo(struct Livro *biblioteca, int totalLivros,
                        struct Emprestimo *emprestimos, int *totalEmprestimos) {
    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido.\n");
        return;
    }

    int disponiveis = 0;
    printf("\n--- Livros Disponiveis ---\n");

    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].disponivel) {
            printf("%d - %s\n", i + 1, biblioteca[i].nome);
            disponiveis++;
        }
    }

    if (disponiveis == 0) {
        printf("Nenhum livro disponivel.\n");
        return;
    }

    int escolha;
    printf("Escolha o numero do livro: ");
    scanf("%d", &escolha);
    limparBufferEntrada();

    int indice = escolha - 1;

    if (indice < 0 || indice >= totalLivros || !biblioteca[indice].disponivel) {
        printf("Livro invalido.\n");
        return;
    }

    printf("Nome do usuario: ");
    fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
    emprestimos[*totalEmprestimos].nomeUsuario[
        strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")
    ] = '\0';

    emprestimos[*totalEmprestimos].indiceLivro = indice;
    biblioteca[indice].disponivel = 0;
    (*totalEmprestimos)++;

    printf("Emprestimo realizado com sucesso!\n");
}

void listarEmprestimos(const struct Livro *biblioteca,
                       const struct Emprestimo *emprestimos, int totalEmprestimos) {
    printf("\n--- Lista de Emprestimos ---\n");

    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo realizado.\n");
        return;
    }

    for (int i = 0; i < totalEmprestimos; i++) {
        printf("\nEmprestimo %d\n", i + 1);
        printf("Livro: %s\n", biblioteca[emprestimos[i].indiceLivro].nome);
        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
    }
}

void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos) {
    free(biblioteca);
    free(emprestimos);
}
