#ifndef CAB_PRODUTO_H_INCLUDED
#define CAB_PRODUTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define ARQUIVO "produtos.txt"

// Estrutura de dados para produtos
struct Produto {
    int id;               // ID do produto (posi��o no estoque)
    char nome[50];        // Nome do produto
    float preco;          // Pre�o do produto
    float quantidade;     // Quantidade em Kg no estoque
};

// Fun��es para manipula��o de produtos
void salvarProdutos(struct Produto produtos[], int contador);
int carregarProdutos(struct Produto produtos[]);
void cadastrarProduto(struct Produto produtos[], int *contador, int modoAtualizacao, int idProdutoAtualizar);
void listarProdutos(struct Produto produtos[], int contador);
struct Produto* procurarProduto(struct Produto produtos[], int numProdutos, int id);

#endif // CAB_PRODUTO_H_INCLUDED
