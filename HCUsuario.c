#include "HeadUsuario.h"

// Variáveis globais
int contadorVendas = 0;
int contadorDias = 1;

// Função para limpar a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Verifica se uma senha já existe no sistema
int senhaExistente(char *senha) {
    FILE *arquivo = fopen("Usuario.txt", "r");
    if (arquivo == NULL) {
        return 0; // Arquivo não encontrado
    }

    struct Usuario usuario;
    while (fscanf(arquivo, "%s %s %c", usuario.nomeUs, usuario.senha, &usuario.funcionario) != EOF) {
        if (strcmp(usuario.senha, senha) == 0) {
            fclose(arquivo);
            return 1; // Senha já existe
        }
    }
    fclose(arquivo);
    return 0;
}

// Cadastra um novo usuário
void cadastrarUsuario() {    
    limparTela();
    int j = 0;
    char cr;
    FILE *arquivo = fopen("Usuario.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    struct Usuario usuario;
    printf("Digite o nome do usuario: ");
    scanf("%49s", usuario.nomeUs);
    
    do {   
        printf("Digite a senha do usuario: ");
    
        while ((cr = getch()) != '\r') {
            if (cr == '\b' && j > 0) {
                j--;
                printf("\b \b");
            } else if (j < 49) {
                usuario.senha[j++] = cr;
                printf("*");
            }
        }
        usuario.senha[j] = '\0';

        if (senhaExistente(usuario.senha)) {
            printf("\nSenha ja existente! Digite uma senha diferente.\n");                
        } else {
            break;
        }
    } while (1);

    printf("\nO usuario é administrador? [S/N] ");
    scanf(" %c", &usuario.funcionario);
    limparTela();

    fprintf(arquivo, "%s %s %c\n", usuario.nomeUs, usuario.senha, usuario.funcionario); 
    fclose(arquivo);
    printf("Cadastro salvo com sucesso!\n");
}

// Verifica se o usuário existe no sistema
int verificarUsuario(char *nome, char *senha) {
    FILE *arquivo = fopen("Usuario.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return -1;
    }

    struct Usuario usuario;
    while (fscanf(arquivo, "%s %s %c", usuario.nomeUs, usuario.senha, &usuario.funcionario) != EOF) {
        if (strcmp(usuario.nomeUs, nome) == 0 && strcmp(usuario.senha, senha) == 0) {
            fclose(arquivo);
            return 1; 
        }
    }
    fclose(arquivo);
    return 0;
}

// Faz o login do usuário
int fazerLogin(char *nomeUsuario) {
    char senhaUsuario[50];
    int i = 0;
    char ch;
    printf("Digite a senha do usuario: ");

    while ((ch = getch()) != '\r') {
        if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        } else if (i < 49) {
            senhaUsuario[i++] = ch;
            printf("*");
        }
    }
    senhaUsuario[i] = '\0';
    limparTela();

    if ((strcmp(nomeUsuario, "admin") == 0 && strcmp(senhaUsuario, "admin") == 0) || 
        verificarUsuario(nomeUsuario, senhaUsuario)) {
        return 1;
    } else {
        printf("Acesso Negado. Nome ou senha incorretos.\n");
        return 0;
    }
}

// Verifica a permissão do usuário (admin ou funcionário)
int verificarPermissao(char *nomeUsuario) {
    if (strcmp(nomeUsuario, "admin") == 0) {
        printf("Bem-vindo admin!\n");
        return 1;
    }

    FILE *arquivo = fopen("Usuario.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    struct Usuario usuario;
    while (fscanf(arquivo, "%s %s %c", usuario.nomeUs, usuario.senha, &usuario.funcionario) != EOF) {
        if (strcmp(usuario.nomeUs, nomeUsuario) == 0) {
            fclose(arquivo);
            if (usuario.funcionario == 'S' || usuario.funcionario == 's') {
                printf("Bem-vindo admin!\n");
                return 1;
            } else {
                printf("Bem-vindo!\n");
                return 2;
            }
        }
    }
    fclose(arquivo);
    return 0;
}