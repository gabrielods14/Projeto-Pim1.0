#include "HeadVenda_dia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MARGEM 0.2

int contadorDias; // Variável global para o contador de dias

// Função para salvar o contador de dias em um arquivo
void salvarContadorDias() {
    FILE *arquivo = fopen("contadorDias.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar o contador de dias.\n");
        return;
    }
    fprintf(arquivo, "%d", contadorDias);
    fclose(arquivo);
}

// Função para carregar o contador de dias de um arquivo
void carregarContadorDias() {
    FILE *arquivo = fopen("contadorDias.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum contador de dias encontrado. Iniciando com o dia 1.\n");
        contadorDias = 1;
        return;
    }
    fscanf(arquivo, "%d", &contadorDias);
    fclose(arquivo);
}

// Função para registrar uma venda em um arquivo específico para o dia
void registrarVenda(const char *nomeProduto, float precoFinal, float quantidadeVendida, int dia) {
    if (precoFinal <= 0 || quantidadeVendida <= 0) {
        printf("Erro: Preço ou quantidade inválidos.\n");
        return;
    }

    char arquivoVendas[50];
    sprintf(arquivoVendas, "vendas_dia_%d.txt", dia);

    FILE *arquivo = fopen(arquivoVendas, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }

    fprintf(arquivo, "Produto: %s | Preço com margem: R$%.2f | Quantidade vendida: %.2f Kg\n", nomeProduto, precoFinal, quantidadeVendida);
    fclose(arquivo);
}

// Função para finalizar o dia e salvar o contador de dias
void finalizarDia() {
    printf("\nFinalizando o dia %d...\n", contadorDias);
    contadorDias++;
    salvarContadorDias();
}

// Função para imprimir uma nota fiscal
void imprimirNotaFiscal(char vendedor[], struct Produto produtos[], int numProdutos, float pagamento) {
    printf("===============================================\n");
    printf("| PEDIDO - HORTIFRUTI                         |\n");
    printf("|---------------------------------------------|\n");
    printf("| VENDEDOR :  %-12s                     |\n", vendedor);
    printf("|=============================================|\n");
    printf("| ID   NOME            Qtd    R$/Kg      Total|\n");
    printf("|=============================================|\n");

    for (int i = 0; i < numProdutos; i++) {
        printf("| %-4d %-15s %-6.2f %-10.2f %-8.2f |\n", produtos[i].id, produtos[i].nome, produtos[i].quantidade, produtos[i].preco, pagamento);
    }

    printf("|=============================================|\n");
    printf("| %02d ITEM(S)                          %.2f      |\n", numProdutos, pagamento);
    printf("|=============================================|\n");
    printf("|                   DINHEIRO :         %.2f     |\n", pagamento);
    printf("===============================================\n");
    printf("| Obrigado pela preferência!                   |\n");
    printf("===============================================\n\n");
}

// Função para realizar uma venda com opções de pagamento
void realizarVenda(struct Produto produtos[], int numProdutos, int *contador, char vendedor[]) {
    int idProduto;
    float quantidadeVenda, total = 0.0;
    struct Produto vendasTemp[MAX_PRODUTOS];
    float quantidadesVendidas[MAX_PRODUTOS];
    int vendasTempCount = 0;

    printf("Bem vindo ao sistema de PDV!\n");
    printf("Digite o ID do produto (0 para finalizar): ");
    while (1) {
        scanf("%d", &idProduto);
        if (idProduto == 0) break;

        struct Produto *produto = procurarProduto(produtos, numProdutos, idProduto);
        if (produto != NULL) {
            printf("Quantidade a vender (Kg): ");
            if (scanf("%f", &quantidadeVenda) != 1) continue;

            if (quantidadeVenda > 0 && quantidadeVenda <= produto->quantidade) {
                float precoFinal = produto->preco * (1 + MARGEM);
                float valorVenda = precoFinal * quantidadeVenda;
                total += valorVenda;
                produto->quantidade -= quantidadeVenda;

                vendasTemp[vendasTempCount] = *produto;
                quantidadesVendidas[vendasTempCount++] = quantidadeVenda;
                registrarVenda(produto->nome, precoFinal, quantidadeVenda, contadorDias);

                if (produto->quantidade == 0) {
                    printf("Estoque do produto %s acabou.\n", produto->nome);
                    cadastrarProduto(produtos, contador, 1, produto->id - 1);
                }
            }
        } else {
            printf("Produto com ID %d não encontrado.\n", idProduto);
        }
        printf("Digite o ID do próximo produto (0 para finalizar): ");
    }
    imprimirNotaFiscal(vendedor, vendasTemp, vendasTempCount, total);
    salvarProdutos(produtos, *contador);
}