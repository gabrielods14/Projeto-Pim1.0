#ifndef HEADVENDA_DIA_H
#define HEADVENDA_DIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HeadProduto.h"

// Funções para gerenciar o contador de dias
void salvarContadorDias();
void carregarContadorDias();
void finalizarDia();

// Funções para registro e processamento de vendas
void registrarVenda(const char *nomeProduto, float precoFinal, float quantidadeVendida, int dia);
void imprimirNotaFiscal(char vendedor[], struct Produto produtos[], int numProdutos, float pagamento);
void realizarVenda(struct Produto produtos[], int numProdutos, int *contador, char vendedor[]);

#endif // 
