#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HeadUsuario.h"
#include "HeadProduto.h"
#include "HeadVenda_dia.h"

#define MAX_PRODUTOS 100

int main() {
    char nomeUsuario[50];

    carregarContadorDias();

    printf("Digite o nome do usuario: ");
    scanf("%49s", nomeUsuario);
    while (getchar() != '\n');  // Limpa o buffer

    // Tentar fazer login 
    if (!fazerLogin(nomeUsuario)) {
        return 0; // Encerra o programa se o login falhar
    }

    int permissao = verificarPermissao(nomeUsuario);
    if (permissao == -1) {
        printf("Erro ao abrir o arquivo. Encerrando o programa.\n");
        return 1;
    } else if (permissao == 0) {
        printf("Erro: Usuario nao encontrado.\n");
        return 1;
    } // permissao 

    struct Produto produtos[MAX_PRODUTOS];
    int contador = carregarProdutos(produtos); // Carrega os produtos ao iniciar
    int opcao; // variável para a opção de cadastro

    // Loop para mostrar o menu até que o usuário escolha sair
    while (1) {
        // Menu de opções
        printf("Escolha uma das opcoes: \n");
        printf(" __________________________\n");
        if (permissao == 1) { // Menu para administradores
            printf("|1-Cadastrar usuario       |\n");
            printf("|2-Cadastrar novo produto  |\n");
            printf("|3-Listar Produtos         |\n");
            printf("|4-Venda                   |\n");
            printf("|5-Finalizar dia           |\n");
            printf("|6-Sair                    |\n");
        } else if (permissao == 2) { // Menu para funcionários
            printf("|1-Listar produtos         |\n");
            printf("|2-Venda                   |\n");
            printf("|3-Finalizar dia           |\n");
            printf("|4-Sair                    |\n");
        }
        printf("|__________________________|\n\n");
        scanf("%d", &opcao); // Lê a opção do usuário

        // Estrutura switch para opções
        switch (opcao) {
            case 1:
                if (permissao == 1) {
                    cadastrarUsuario(); //chama a função de cadastro de usuario, tipo void
                } else {
                    listarProdutos(produtos, contador);
                }
                break;
            case 2:
                if (permissao == 1) {
                    cadastrarProduto(produtos, &contador, 0, 0); // Cadastro de produto
                } else {
                    realizarVenda(produtos, contador, &contador, nomeUsuario); // Chama a funcao de venda
                }
                break;
            case 3:
                if (permissao == 1) {
                    listarProdutos(produtos, contador);
                } else {
                    finalizarDia(); // Chama a função de finalizar o dia
                }     
                break;
            case 4:
                if (permissao == 1) {
                    realizarVenda(produtos, contador, &contador, nomeUsuario); // Chama a funcao de venda
                } else {
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Saindo do sistema...");
                    printf("\n-----------------------------------------------------------\n\n");
                    return 0;
                }
                break;
            case 5:
                if (permissao == 1) {
                    finalizarDia(); // Chama a função de finalizar o dia
                } else {
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Opcao invalida. Tente novamente.");
                    printf("\n-----------------------------------------------------------\n\n");
                }
                break;
            case 6:
                if (permissao == 1) {
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Saindo do sistema...");
                    printf("\n-----------------------------------------------------------\n\n");
                return 0;
                } else {
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Opcao invalida. Tente novamente.");
                    printf("\n-----------------------------------------------------------\n\n");
                }
                break;
            default:
                printf("\n-----------------------------------------------------------\n");
                printf("*Opcao invalida. Tente novamente.");
                printf("\n-----------------------------------------------------------\n\n");
                break;
        }
        printf("\nPressione Enter para continuar...");
        getchar(); // Consumir newline restante
        getchar(); // Aguarda o Enter
        limparTela();
    }
    return 0;
}