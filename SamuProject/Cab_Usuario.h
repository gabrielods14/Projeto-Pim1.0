#ifndef CAB_USUARIO_H_INCLUDED
#define CAB_USUARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados do Usuario
struct Usuario {
    char nomeUs[50]; // nome do usuario
    char senha[50]; // senha do usuario
    char funcionario; // tipo do usuario, administrador ou funcionario
};

// Funções utilitárias e de usuario
void limparTela();
int senhaExistente(char *senha);
void cadastrarUsuario();
int verificarUsuario(char *nome, char *senha);
int fazerLogin(char *nomeUsuario);
int verificarPermissao(char *nomeUsuario);


#endif // CAB_USUARIO_H_INCLUDED
