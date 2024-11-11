#include "Cab_Produto.h"

// Fun��o para salvar os produtos no arquivo
void salvarProdutos(struct Produto produtos[], int contador) {
    FILE *arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro ao abrir o arquivo para escrita.");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        fprintf(arquivo, "ID:%d | Nome:%s | Preco por Kg: R$%.2f | Quantidade: %.2f Kg\n",
                produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }

    fclose(arquivo);
}

// Fun��o para carregar os produtos do arquivo
int carregarProdutos(struct Produto produtos[]) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Nenhum Produto Cadastrado.");
        printf("\n-----------------------------------------------------------\n");
        return 0;
    }

    int contador = 0;
    while (fscanf(arquivo, "ID:%d | Nome:%s | Preco por Kg: R$%f | Quantidade: %f Kg\n",
                  &produtos[contador].id, produtos[contador].nome,
                  &produtos[contador].preco, &produtos[contador].quantidade) == 4) {
        contador++;
    }

    fclose(arquivo);
    return contador;
}

// Fun��o para cadastrar ou atualizar um produto
void cadastrarProduto(struct Produto produtos[], int *contador, int modoAtualizacao, int idProdutoAtualizar) {
    limparTela();
    if (modoAtualizacao == 0 && *contador >= MAX_PRODUTOS) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Limite de produtos cadastrados atingido.");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    struct Produto novoProduto;
    if (modoAtualizacao == 1) {
        novoProduto = produtos[idProdutoAtualizar];
        printf("\n-----------------------------------------------------------\n");
        printf("*Atualizando quantidade do produto %s (ID %d).", novoProduto.nome, novoProduto.id);
        printf("\n-----------------------------------------------------------\n");
    } else {
        novoProduto.id = *contador + 1;
        printf("Nome do produto: ");
        getchar();
        fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
        novoProduto.nome[strcspn(novoProduto.nome, "\n")] = 0;

        printf("Preco do produto por Kg: ");
        if (scanf("%f", &novoProduto.preco) != 1) {
            printf("\n-----------------------------------------------------------\n");
            printf("*Entrada invalida para preco!");
            printf("\n-----------------------------------------------------------\n");
            return;
        }
    }

    printf("Quantidade no estoque (Kg): ");
    if (scanf("%f", &novoProduto.quantidade) != 1) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Entrada invalida para quantidade!");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    if (modoAtualizacao == 1) {
        produtos[idProdutoAtualizar].quantidade += novoProduto.quantidade;
    } else {
        produtos[*contador] = novoProduto;
        (*contador)++;
    }

    printf("\n-----------------------------------------------------------\n");
    printf("*Produto atualizado com sucesso!");
    printf("\n-----------------------------------------------------------\n");
    salvarProdutos(produtos, *contador);
}

// Fun��o para listar todos os produtos
void listarProdutos(struct Produto produtos[], int contador) {
    limparTela();
    if (contador == 0) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Nenhum produto cadastrado.");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    printf("Lista de produtos cadastrados:\n");
    for (int i = 0; i < contador; i++) {
        printf("\n-------------------------------------------------------------------------------\n");
        printf("ID: %d | Nome: %s | Preco por Kg: R$ %.2f | Quantidade: %.2f Kg", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
        printf("\n-------------------------------------------------------------------------------\n");

    }
}

// Fun��o para procurar um produto pelo ID
struct Produto* procurarProduto(struct Produto produtos[], int numProdutos, int id) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].id == id) {
            return &produtos[i];
        }
    }
    return NULL;
}
