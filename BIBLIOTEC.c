/* 
PROJETO - SISTEMA DE BIBLIOTECA 

Objetivo: 
--> Implementacao de cadastro e listagem de livros usando um array estatico.
--> Foco em structs, entrada/saida de dados e organizacao basica
*/

// Incluir bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes Globais
#define MAX_LIVROS 50
#define TAM_STRING 100

// Definicao da Estrutura (Struct)
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editor[TAM_STRING];
    int edicao;
};

// Limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao Principal
int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    do {
        // Exibe o menu
        printf("==================================\n");
        printf("     BIBLIOTECA - PARTE 1\n");
        printf("==================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opcao: ");

        // Leitura segura da opcao
        if (scanf("%d", &opcao) != 1) {    
            limparBufferEntrada();
            opcao = -1;  // Opcao invalida
        } else {
            limparBufferEntrada();
        }

        // Processa opcao
        switch(opcao) {
            case 1: // Cadastro de livro
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

                    totalLivros++;
                    printf("\nLivro cadastrado com sucesso!\n\n");

                } else {
                    printf("\nBiblioteca cheia! Nao e possivel cadastrar mais livros.\n\n");
                }
                break;

            case 2: // Listar livros
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
                printf("\nPressione Enter para continuar...");
                getchar(); // pausa
                break;

            case 0: // Sair
                printf("\nSaindo do sistema...\n");
                break;

            default: // Opcao invalida
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }

    } while(opcao != 0);

    return 0;
}
