#include "Cab_Usuario.h" // Inclui o Cabecalho com a declaração da struct Usuario e funções

// Funcao para limpar a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Verifica se uma senha ja existe no sistema
int senhaExistente(char *senha) {
    FILE *arquivo = fopen("Usuario.txt", "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) { // Verifica se nao ha conteudo no arq
        return 0; // Arquivo nao encontrado
    }

    struct Usuario usuario;
    while (fscanf(arquivo, "%s %s %c", usuario.nomeUs, usuario.senha, &usuario.funcionario) != EOF) { // Le o arq ate seu fim
        if (strcmp(usuario.senha, senha) == 0) { // Compara alguma senha de um usuario cadastrado com a digitada no login
            fclose(arquivo);
            return 1; // Senha ja existe
        }
    }
    fclose(arquivo);
    return 0;
}

// Cadastra um novo usuario
void cadastrarUsuario() {
    limparTela();

    FILE *arquivo = fopen("Usuario.txt", "a"); // Abre o arq para escrita, adiciona mais dados ao final dele
    if (arquivo == NULL) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro ao abrir o arquivo!");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    struct Usuario usuario; // Declaracao da struct Uauario como var 'usuario'
    printf("Digite o nome do usuario: ");
    scanf("%49s", usuario.nomeUs);

    do { // Loop da senha de cadastro de usuario
        printf("Digite a senha do usuario: ");
        scanf("%49s", usuario.senha);

        if (senhaExistente(usuario.senha)) { // Chama a funcao para verificar se senha ja eh existente
            printf("\n-----------------------------------------------------------\n");
            printf("*Senha ja existente!!! Digite uma senha diferente.");
            printf("\n-----------------------------------------------------------\n\n");
        } else {
            break; // Termina loop da senha
        }
    } while (1);

    printf("\nO usuario e administrador? [S/N]: ");
    scanf(" %c", &usuario.funcionario);
    limparTela();

    if (usuario.funcionario == 'S' || usuario.funcionario == 's' ) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Cadastro de usuario do tipo administrador concluido.");
        printf("\n-----------------------------------------------------------\n\n");
    } else if (usuario.funcionario == 'N' || usuario.funcionario == 'n') {
        printf("\n-----------------------------------------------------------\n");
        printf("*Cadastro de usuario do tipo funcionario concluido.");
        printf("\n-----------------------------------------------------------\n\n");
    } else {
        printf("\n-----------------------------------------------------------\n");
        printf("*Opcao invalida!");
        printf("\n-----------------------------------------------------------\n\n");
        fclose(arquivo);
        return;
    }

    fprintf(arquivo, "%s %s %c\n", usuario.nomeUs, usuario.senha, usuario.funcionario); // Imprime no arquivo os dados do usuario cadastrado
    fclose(arquivo);
    printf("\n-----------------------------------------------------------\n");
    printf("*Cadastro salvo com sucesso!");
    printf("\n-----------------------------------------------------------\n\n");
}

// Verifica se o usuario existe no sistema
int verificarUsuario(char *nome, char *senha) {
    FILE *arquivo = fopen("Usuario.txt", "r");
    if (arquivo == NULL) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro ao abrir o arquivo!");
        printf("\n-----------------------------------------------------------\n");
        return -1;
    }

    struct Usuario usuario;
    while (fscanf(arquivo, "%s %s %c", usuario.nomeUs, usuario.senha, &usuario.funcionario) != EOF) {
        if (strcmp(usuario.nomeUs, nome) == 0 && strcmp(usuario.senha, senha) == 0) { // Compara nome e senha digitados com as cadastradas do arq
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

// Faz o login do usuario
int fazerLogin(char *nomeUsuario) {
    char senhaUsuario[50];
    int i = 0;
    char ch;
    printf("Digite a senha do usuario: ");

    while ((ch = getch()) != '\r') { // Enter pressionado '\r'
        if (ch == '\b' && i > 0) { // Backspace pressionado '\b'
            i--;
            printf("\b \b"); // Apaga o último caractere exibido
        } else if (i < 49) { // Evita estouro de buffer
            senhaUsuario[i++] = ch; // Armazena o caractere
            printf("*"); // Exibe um asterisco
        }
    }
    senhaUsuario[i] = '\0'; // Finaliza a string
    limparTela();

    if ((strcmp(nomeUsuario, "admin") == 0 && strcmp(senhaUsuario, "admin") == 0) ||
        verificarUsuario(nomeUsuario, senhaUsuario)) { // Compara se o nome e a senha sao iguais ao usuario cadastrado ou ao admin de primeiro acesso
        return 1;
    } else {
        printf("\n-----------------------------------------------------------\n");
        printf("*Acesso Negado. Nome ou senha de usuario incorretos.");
        printf("\n-----------------------------------------------------------\n\n");
        return 0;
    }
}

// Verifica a permissao do usuario (admin ou funcionario)
int verificarPermissao(char *nomeUsuario) {
    if (strcmp(nomeUsuario, "admin") == 0) {
        printf("Bem-vindo admin!\n");
        return 1;
    }

    FILE *arquivo = fopen("Usuario.txt", "r");
    if (arquivo == NULL) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro ao abrir o arquivo!");
        printf("\n-----------------------------------------------------------\n");
        return 0;
    }

    struct Usuario usuario;
    while (fscanf(arquivo, "%s %s %c", usuario.nomeUs, usuario.senha, &usuario.funcionario) != EOF) {
        if (strcmp(usuario.nomeUs, nomeUsuario) == 0) { // Compara o nome do usuario cadastrado com o do login
            fclose(arquivo);
            if (usuario.funcionario == 'S' || usuario.funcionario == 's') {
                printf("Bem-vindo admin!\n");
                return 1; // Retorna 1 para acesso do admin ao menu total
            } else {
                printf("Bem-vindo funcionario!\n");
                return 2; // Retorna 2 para acesso do funcionario ao menu limitado
            }
        }
    }
    fclose(arquivo);
    return 0;
}
