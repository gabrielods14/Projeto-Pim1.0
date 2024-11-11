#include "HeadProduto.h"

// Função para salvar os produtos no arquivo
void salvarProdutos(struct Produto produtos[], int contador) {
    FILE *arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        fprintf(arquivo, "ID:%d | Nome:%s | Preco por Kg: R$%.2f | Quantidade: %.2f Kg\n",
                produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }

    fclose(arquivo);
}

// Função para carregar os produtos do arquivo
int carregarProdutos(struct Produto produtos[]) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum Produto Cadastrado.\n");
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

// Função para cadastrar ou atualizar um produto
void cadastrarProduto(struct Produto produtos[], int *contador, int modoAtualizacao, int idProdutoAtualizar) {
    limparTela();
    if (modoAtualizacao == 0 && *contador >= MAX_PRODUTOS) {
        printf("Limite de produtos cadastrados atingido.\n");
        return;
    }

    struct Produto novoProduto;
    if (modoAtualizacao == 1) {
        novoProduto = produtos[idProdutoAtualizar];
        printf("Atualizando quantidade do produto %s (ID %d)\n", novoProduto.nome, novoProduto.id);
    } else {
        novoProduto.id = *contador + 1;
        printf("Nome do produto: ");
        getchar();
        fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
        novoProduto.nome[strcspn(novoProduto.nome, "\n")] = 0;

        printf("Preco do produto por Kg: ");
        if (scanf("%f", &novoProduto.preco) != 1) {
            printf("Entrada invalida para preco!\n");
            return;
        }
    }

    printf("Quantidade no estoque (Kg): ");
    if (scanf("%f", &novoProduto.quantidade) != 1) {
        printf("Entrada invalida para quantidade!\n");
        return;
    }

    if (modoAtualizacao == 1) {
        produtos[idProdutoAtualizar].quantidade += novoProduto.quantidade;
    } else {
        produtos[*contador] = novoProduto;
        (*contador)++;
    }

    printf("Produto atualizado com sucesso!\n");
    salvarProdutos(produtos, *contador);
}

// Função para listar todos os produtos
void listarProdutos(struct Produto produtos[], int contador) {
    limparTela();
    if (contador == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Lista de produtos cadastrados:\n");
    for (int i = 0; i < contador; i++) {
        printf("ID: %d | Nome: %s | Preco por Kg: R$ %.2f | Quantidade: %.2f Kg\n",
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

// Função para procurar um produto pelo ID
struct Produto* procurarProduto(struct Produto produtos[], int numProdutos, int id) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].id == id) {
            return &produtos[i];
        }
    }
    return NULL;
}
