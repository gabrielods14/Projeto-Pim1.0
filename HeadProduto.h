#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PRODUTOS 100
#define ARQUIVO "produtos.txt"

// Estrutura de dados para produtos
struct Produto { 
    int id;               // ID do produto (posição no estoque)
    char nome[50];        // Nome do produto
    float preco;          // Preço do produto
    float quantidade;     // Quantidade em Kg no estoque
};

// Funções para manipulação de produtos
void salvarProdutos(struct Produto produtos[], int contador);
int carregarProdutos(struct Produto produtos[]);
void cadastrarProduto(struct Produto produtos[], int *contador, int modoAtualizacao, int idProdutoAtualizar);
void listarProdutos(struct Produto produtos[], int contador);
struct Produto* procurarProduto(struct Produto produtos[], int numProdutos, int id);

#endif // PRODUTO_H