#include <stdio.h> // Biblioteca de funcoes basicas de C como printf e scanf
#include <stdlib.h> // Biblioteca de funcoes envolventes de memoria
#include <string.h> // Biblioteca propriamente de strings
#include "Cab_Usuario.h" // Cabecalho de funcoes de cadastro, verificacao, login e outras de usuario
#include "Cab_Produto.h" // Cabecalho de funcoes de cadastro, listagem, verificacao e outras de produto
#include "Cab_FinalizarD.h" // Cabecalho de funcoes de venda de produtos e finalizacao de dias


int main()
{
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
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro ao abrir o arquivo. Encerrando o programa.");
        printf("\n-----------------------------------------------------------\n");
        return 1;
    } else if (permissao == 0) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro: Usuario nao encontrado.\n");
        printf("\n-----------------------------------------------------------\n");
        return 1;
    } // permissao

    struct Produto produtos[MAX_PRODUTOS];
    int contador = carregarProdutos(produtos); // Carrega os produtos ao iniciar
    int opcao; // variavel para a opcao de cadastro

    // Loop para mostrar o menu ate que o usuario escolha sair
    while (1) {
        // Menu de opcoes
        printf("\nEscolha uma das opcoes: \n");
        printf(" __________________________\n");
        if (permissao == 1) { // Menu para administradores
            printf("|1-Cadastrar usuario       |\n");
            printf("|2-Cadastrar novo produto  |\n");
            printf("|3-Listar Produtos         |\n");
            printf("|4-Venda                   |\n");
            printf("|5-Finalizar dia           |\n");
            printf("|6-Sair                    |\n");
        } else if (permissao == 2) { // Menu para funcionarios
            printf("|1-Listar produtos         |\n");
            printf("|2-Venda                   |\n");
            printf("|3-Finalizar dia           |\n");
            printf("|4-Sair                    |\n");
        }
        printf("|__________________________|\n\n");
        scanf("%d", &opcao); // Le a opcao do usuario

        // Estrutura switch para opcoes
        switch (opcao) {
            case 1:
                if (permissao == 1) {
                    cadastrarUsuario(); //chama a funcao de cadastro de usuario do tipo void
                } else {
                    listarProdutos(produtos, contador); // Chama a funcao de listar produtos
                }
                break; // Termina o looping e retorna ao menu
            case 2:
                if (permissao == 1) {
                    cadastrarProduto(produtos, &contador, 0, 0); // Chama a funcao de cadastro de produto
                } else {
                    realizarVenda(produtos, contador, &contador, nomeUsuario); // Chama a funcao de venda
                }
                break;
            case 3:
                if (permissao == 1) {
                    listarProdutos(produtos, contador);
                } else {
                    finalizarDia(); // Chama a funcao de finalizar o dia
                }
                break;
            case 4:
                if (permissao == 1) {
                    realizarVenda(produtos, contador, &contador, nomeUsuario);
                } else {
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Saindo do sistema...");
                    printf("\n-----------------------------------------------------------\n");
                    return 0; // Encerra o programa  por opcao do usuario
                }
                break;
            case 5:
                if (permissao == 1) {
                    finalizarDia();
                } else {
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Opcao invalida. Tente novamente.");
                    printf("\n-----------------------------------------------------------\n");
                }
                break;
            case 6:
                if (permissao == 1) {
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Saindo do sistema...");
                    printf("\n-----------------------------------------------------------\n");
                return 0;
                } else {
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Opcao invalida. Tente novamente.");
                    printf("\n-----------------------------------------------------------\n");
                }
                break;
            default:
                printf("\n-----------------------------------------------------------\n");
                printf("*Opcao invalida. Tente novamente.");
                printf("\n-----------------------------------------------------------\n");
                break;
        }
        printf("\nPressione Enter para continuar...");
        getchar(); // Consumir newline restante
        getchar(); // Aguarda o Enter
        limparTela(); // Funcao para limpar tela que auxilia na orientacao do usuario
    }
    return 0;
}
