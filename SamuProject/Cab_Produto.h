#ifndef CAB_PRODUTO_H_INCLUDED
#define CAB_PRODUTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100 // Define o maximo de produtos cadastrados constantemente
#define ARQUIVO "produtos.txt" // A declaracao de ARQUIVO reflete no arq de produtos.txt constantemente

// Estrutura de dados para Produtos
struct Produto {
    int id;               // ID do produto (posicao no estoque)
    char nome[50];        // Nome do produto
    float preco;          // Preco do produto
    float quantidade;     // Quantidade em Kg no estoque
};

// Funções para manipulação de produtos
void salvarProdutos(struct Produto produtos[], int contador);
int carregarProdutos(struct Produto produtos[]);
void cadastrarProduto(struct Produto produtos[], int *contador, int modoAtualizacao, int idProdutoAtualizar);
void listarProdutos(struct Produto produtos[], int contador);
struct Produto* procurarProduto(struct Produto produtos[], int numProdutos, int id);

#endif // CAB_PRODUTO_H_INCLUDED
