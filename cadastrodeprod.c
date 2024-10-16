#include <stdio.h> // para usar printf e scanf
#include <stdlib.h> // funções utilitárias, como alocação de memória
#include <string.h> // para manipulação de strings, como comparação

#define MAXprducts 99

typedef struct {
    char nome[50];
    float precoKg;
    float totalKg;
} Produto;

Produto produtos[MAXprducts];
int totalProdutos = 0;


void produtoarq(Produto p){
    FILE *arq2 = fopen("produtos.txt", "a");
    if (arq2 == NULL){
        printf("erro ao abrir arquivo\n");
    }

    fprintf(arq2, " %s | %fR$ | %fKg \n", p.nome, p.precoKg, p.totalKg);

    fclose(arq2);
}

void cadastrarProduto() {
    if (totalProdutos >= MAXprducts) { //condição satisfeita com qnt MAX de produto
        printf("Limite de produtos atingido.\n");
        return;
    }

    Produto p;

    printf("Digite o nome do produto: ");
    scanf(" %49[^\n]", p.nome); // Limita a leitura a 49 caracteres

    printf("Digite o Preco/Kg: ");
    scanf("%f", &p.precoKg);

    printf("Digite o Peso total do produto: ");
    scanf("%f", &p.totalKg);

    produtos[totalProdutos] = p; // Armazena produto na lista/array
    totalProdutos++; //incremento de 0 ao MAX

    produtoarq(p);

    printf("\nProduto cadastrado com sucesso!\n\n");
}

/*void exibirProdutos() {
    printf("\nLista de Produtos Cadastrados:\n");
    for (int i = 0; i < totalProdutos; i++) {
        Produto p = produtos[i];
        printf("Nome: %s\nPreco/Kg: R$ %.2f\nTotal do Produto/Kg: %.2f\n\n",p.nome, p.precoKg, p.TotalKg);

    }
}*/

/*void calcularMargem() {
    for (int i = 0; i < totalProdutos; i++) {
        Produto p = produtos[i];
        float margem = ((p.precoVenda - p.precoCusto) / p.precoCusto) * 100;
        printf("Produto: %s | Margem: %.2f%%\n", p.nome, margem);
    }
}*/

void limparTela(){
    printf("\e[1;1H\e[2J");
}


int main(){
    int opcao;

    do {

        printf("\n--- Menu Hortifruti ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                limparTela();
                cadastrarProduto();
                break;
            case 2:
                limparTela();
                printf("Saindo do sistema...\n");
                break;
            default:
                limparTela();
                printf("Opcao invalida\n");
        }
    } while (opcao != 2);

    return 0;
}