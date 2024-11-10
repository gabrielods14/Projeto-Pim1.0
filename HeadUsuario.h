#ifndef HEADUSUARIO_H
#define HEADUSUARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define ARQUIVO "produtos.txt"
#define MARGEM 0.20

// Declarações de variáveis globais
int contadorVendas;
int contadorDias;

// Estrutura de dados
struct Usuario { 
    char nomeUs[50]; 
    char senha[50]; 
    char funcionario; 
};

// Funções utilitárias
void limparTela();
int senhaExistente(char *senha);
void cadastrarUsuario();
int verificarUsuario(char *nome, char *senha);
int fazerLogin(char *nomeUsuario);
int verificarPermissao(char *nomeUsuario);

#endif // 