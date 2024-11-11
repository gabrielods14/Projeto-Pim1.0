#ifndef CAB_USUARIO_H_INCLUDED
#define CAB_USUARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


#endif // CAB_USUARIO_H_INCLUDED
