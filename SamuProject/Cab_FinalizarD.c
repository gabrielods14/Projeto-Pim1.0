#include "Cab_FinalizarD.h" // Inclui o Cabecalho com a declaração das funções usuadas

// Variaveis globais
int contadorVendas = 0;
int contadorDias = 1;

// Funcao para finalizar o dia e salvar o contador de dias
void finalizarDia() {
    printf("\n-----------------------------------------------------------\n"); // Finaliza o dia
    printf("*Finalizando o dia %d...", contadorDias);
    printf("\n*Dia %d finalizado com sucesso!", contadorDias);
    printf("\n-----------------------------------------------------------\n");
    contadorDias++;
    salvarContadorDias();
}

// Funcao para salvar o contador de dias em um arquivo
void salvarContadorDias() {
    FILE *arquivo = fopen("contadorDias.txt", "w");
    if (arquivo == NULL) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro ao salvar o contador de dias.");
        printf("\n-----------------------------------------------------------\n");
        return;
    }
    fprintf(arquivo, "%d", contadorDias);
    fclose(arquivo);
}

// Funcao para carregar o contador de dias de um arquivo
void carregarContadorDias() { // Abre o arquivo em modo leitura, identifica o dia
    FILE *arquivo = fopen("contadorDias.txt", "r");
    if (arquivo == NULL) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Nenhum contador de dias encontrado. Iniciando com o dia 1.");
        printf("\n-----------------------------------------------------------\n");
        contadorDias = 1;
        return;
    }
    fscanf(arquivo, "%d", &contadorDias);
    fclose(arquivo);
}

// Funcao para registrar uma venda em um arquivo especifico para o dia
void registrarVenda(const char *nomeProduto, float precoFinal, float quantidadeVendida, int contadorDias) {
    if (precoFinal <= 0 || quantidadeVendida <= 0) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro: Preco ou quantidade invalidos.");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    char arquivoVendas[50];
    sprintf(arquivoVendas, "vendas_dia_%d.txt", contadorDias); // Monta dinamicamente o nome do arquivo com base na variável dia

    FILE *arquivo = fopen(arquivoVendas, "a");
    if (arquivo == NULL) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Erro ao abrir o arquivo de vendas.");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    fprintf(arquivo, "Produto: %s | Preco: R$%.2f | Quantidade vendida: %.2f Kg\n", nomeProduto, precoFinal, quantidadeVendida);
    fclose(arquivo);
}

// Funcao para imprimir uma nota fiscal

void imprimirNotaFiscal(char vendedor[], struct Produto produtos[], int numProdutos, float quantidadeVenda, float pagamento) {

    // Espera o usuário pressionar Enter para continuar (consome o '\n' que fica na entrada do buffer)
    printf("\n-----------------------------------------------------------\n");
    printf("*Gerando Nota Fiscal...\n*Pressione Enter");
    printf("\n-----------------------------------------------------------\n");
    getchar(); // Consumir newline restante
    getchar(); // Aguarda o Enter

    printf("                                                             ===============================================\n");
    printf("                                                            |                    PEDIDO                     |\n");
    printf("                                                            |-----------------------------------------------|\n");
    printf("                                                            |                  HORTIFRUTI                   |\n");
    printf("                                                            |                                               |\n");
    printf("                                                            |-----------------------------------------------|\n");
    printf("                                                            | VENDEDOR :  %-12s                      |\n", vendedor);
    printf("                                                            |===============================================|\n");
    printf("                                                            | ID   NOME            Qtd    R$/Kg      Total  |\n");
    printf("                                                            |===============================================|\n");

    // Laço para listar os produtos
    for (int i = 0; i < numProdutos; i++) {
        float totalProduto = produtos[i].preco * quantidadeVenda;
        printf("                                                            | %-4d %-15s %-6.2f %-10.2f %-6.2f |\n", produtos[i].id, produtos[i].nome, quantidadeVenda, produtos[i].preco, totalProduto);
    }

    printf("                                                            |===============================================|\n");
    printf("                                                            | %02d ITEM(S)                             %.2f   |\n", numProdutos, pagamento);
    printf("                                                            |===============================================|\n");
    printf("                                                            |                   DINHEIRO :           %.2f   |\n", pagamento);
    printf("                                                            |                             ------------------|\n");
    printf("                                                            |                                               |\n");
    printf("                                                            |-----------------------------------------------|\n");
    printf("                                                            | Obrigado pela preferencia.                    |\n");
    printf("                                                             =============================================== \n\n\n");

    }





// Funcao para realizar uma venda com opcoes de pagamento
void realizarVenda(struct Produto produtos[], int numProdutos, int *contador, char vendedor[]) {
    limparTela();

    int idProduto;
    float quantidadeVenda;
    float total = 0.0;

    // Lista tempororia para armazenar os produtos e quantidades vendidas
    struct Produto vendasTemp[MAX_PRODUTOS];
    float quantidadesVendidas[MAX_PRODUTOS]; // Quantidades vendidas de cada produto
    int vendasTempCount = 0; // Contador para vendas temporarias

    printf("Bem vindo ao sistema de PDV!\n");
    printf("Digite o ID do produto (0 para finalizar): ");

    while (1) {
        scanf("%d", &idProduto);

        // Se o ID for 0, finalizar o processo de venda
        if (idProduto == 0) {
            break;
        }

        // Procurar o produto pelo ID
        struct Produto *produto = procurarProduto(produtos, numProdutos, idProduto); // Procura o ID do produto, se ID ou quantidade igual a zero, retorna ao menu.

        if (produto != NULL) {
            printf("Quantidade a vender (Kg): ");
            if (scanf("%f", &quantidadeVenda) != 1) {
                printf("\n-----------------------------------------------------------\n");
                printf("*Entrada invalida para quantidade!");
                printf("\n-----------------------------------------------------------\n\n");
                continue;
            }

            if (quantidadeVenda > 0 && quantidadeVenda <= produto->quantidade) { //Calcula o preço do produto de acordo com a quantidade escolhida
                float precoFinal = produto->preco;
                float valorVenda = precoFinal * quantidadeVenda;
                printf("Preco do produto %s: R$%.2f\n", produto->nome, precoFinal);
                printf("Valor total da venda: R$%.2f\n", valorVenda);
                total += valorVenda;
                produto->quantidade -= quantidadeVenda; // A seta está ligada ao ponteiro *produto, refere-se a variável da struct

                // Registrar a venda temporariamente
                vendasTemp[vendasTempCount] = *produto;
                quantidadesVendidas[vendasTempCount] = quantidadeVenda;
                vendasTempCount++;

                contadorVendas++; // Incrementa a contagem de vendas
                registrarVenda(produto->nome, precoFinal, quantidadeVenda, contadorDias); // Registrar a venda no dia correto

                // Verificar se o estoque zerou e perguntar se deseja atualizar
                if (produto->quantidade == 0) {
                    char resposta;
                    printf("\n-----------------------------------------------------------\n");
                    printf("*O estoque do produto %s acabou. Deseja repor? (s/n): ", produto->nome);
                    scanf(" %c", &resposta);
                    printf("\n-----------------------------------------------------------\n\n");
                    if (resposta == 's' || resposta == 'S') {
                        cadastrarProduto(produtos, contador, 1, produto->id - 1);
                    }
                }
            } else if (quantidadeVenda <= 0) { //Se a quantidade escolhida for menor ou igual a 0, retorna ao menu
                printf("\n-----------------------------------------------------------\n");
                printf("*A quantidade deve ser maior que zero.");
                printf("\n-----------------------------------------------------------\n\n");
                break;
            } else { //Se o estoque do produto estiver zerado
                printf("\n-----------------------------------------------------------\n");
                printf("*Estoque insuficiente para o produto %s.\n\n", produto->nome);
                printf("\n-----------------------------------------------------------\n\n");
            }
        } else { //Se for escolhido um ID de produto não cadastrado
            printf("\n-----------------------------------------------------------\n");
            printf("*Produto com ID %d nao encontrado.\n", idProduto);
            printf("\n-----------------------------------------------------------\n\n");
        }
        printf("\n-----------------------------------------------------------\n");
        printf("Digite o ID do proximo produto (0 para finalizar): ");
    }
    printf("\n-----------------------------------------------------------\n");
    printf("*Total a pagar: R$%.2f\n", total);

    // Verifiço se o total é igual a zero, caso seja = 0, retorna ao menu
    if (total == 0) {
        printf("\n-----------------------------------------------------------\n");
        printf("*O valor total nao pode ser cobrado pois e igual a zero.");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    imprimirNotaFiscal(vendedor, vendasTemp, vendasTempCount, quantidadeVenda, total);

    // Adicionando opcoes de pagamento
    int metodoPagamento;
    printf("Escolha o metodo de pagamento:\n");
    printf(" __________________\n");
    printf("|1-Dinheiro        |\n");
    printf("|2-Cartao          |\n");
    printf("|3-Pix             |\n");
    printf("|__________________|\n\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &metodoPagamento);

    while (metodoPagamento < 1 || metodoPagamento > 3) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Opcao invalida. Tente novamente: ");
        scanf("%d", &metodoPagamento);
    }


    // Variavel para a confirmacao de pagamento
    char pagamentoAprovado;

    if (metodoPagamento == 2) {
        int tipoCartao;
        printf("Escolha o tipo de cartao:\n");
        printf(" __________________\n");
        printf("|1-Credito         |\n");
        printf("|2-Debito          |\n");
        printf("|3-Voucher         |\n");
        printf("|__________________|\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &tipoCartao);

        while (tipoCartao < 1 || tipoCartao > 3) {
        printf("\n-----------------------------------------------------------\n");
        printf("*Opcao invalida. Tente novamente: ");
        scanf("%d", &tipoCartao);
        }

        printf("O pagamento foi aprovado? [S/N]: ");
        scanf(" %c", &pagamentoAprovado);

        if (pagamentoAprovado == 'n' || pagamentoAprovado == 'N') { //Se pagamento reprovado, retorna a quantidade escolhida ao estoque
            printf("\n-----------------------------------------------------------\n");
            printf("*Pagamento nao aprovado. Cancelando a venda.");
            printf("\n-----------------------------------------------------------\n\n");

            // Reverter as vendas
            for (int i = 0; i < vendasTempCount; i++) { //Loop for para retornar produtos ao estoque
                int idProdutoTemp = vendasTemp[i].id;
                struct Produto *produto = procurarProduto(produtos, numProdutos, idProdutoTemp);
                if (produto != NULL) {
                    produto->quantidade += quantidadesVendidas[i]; // Soma aos produtos no estoque a quantidade escolhida na venda
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Produto %s retornado ao estoque.", produto->nome);
                    printf("\n-----------------------------------------------------------\n");
                }
            }
            return;  // Finaliza a funcao, cancelando a venda
        } else {
            printf("\n-----------------------------------------------------------\n");
            printf("*Pagamento aprovado e processado para o tipo de cartao.");
            printf("\n-----------------------------------------------------------\n\n");
        }

    } else if (metodoPagamento == 1) {
        printf("Pagamento em dinheiro selecionado.\n\n");
        printf("O pagamento em dinheiro foi aprovado? [S/N]: ");
        scanf(" %c", &pagamentoAprovado);

        if (pagamentoAprovado == 'n' || pagamentoAprovado == 'N') { //Loop for para retornar produtos ao estoque
            printf("\n-----------------------------------------------------------\n");
            printf("*Pagamento em dinheiro nao aprovado. Cancelando a venda.");
            printf("\n-----------------------------------------------------------\n\n");

            // Reverter as vendas
            for (int i = 0; i < vendasTempCount; i++) {
                int idProdutoTemp = vendasTemp[i].id;
                struct Produto *produto = procurarProduto(produtos, numProdutos, idProdutoTemp);
                if (produto != NULL) {
                    produto->quantidade += quantidadesVendidas[i]; // Soma aos produtos no estoque a quantidade escolhida na venda
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Produto %s retornado ao estoque.", produto->nome);
                    printf("\n-----------------------------------------------------------\n");
                }
            }
        } else {
            printf("\n-----------------------------------------------------------\n");
            printf("*Pagamento em dinheiro realizado com sucesso.");
            printf("\n-----------------------------------------------------------\n");
        }

    } else if (metodoPagamento == 3) {
        printf("Pagamento via Pix selecionado.\n\n");
        printf("O pagamento via Pix foi aprovado? [S/N]: ");
        scanf(" %c", &pagamentoAprovado);

        if (pagamentoAprovado == 'n' || pagamentoAprovado == 'N') { //Loop for para retornar produtos ao estoque
            printf("\n-----------------------------------------------------------\n");
            printf("*Pagamento via Pix nao aprovado. Cancelando a venda.");
            printf("\n-----------------------------------------------------------\n");

            // Reverter as vendas
            for (int i = 0; i < vendasTempCount; i++) {
                int idProdutoTemp = vendasTemp[i].id;
                struct Produto *produto = procurarProduto(produtos, numProdutos, idProdutoTemp);
                if (produto != NULL) {
                    produto->quantidade += quantidadesVendidas[i]; // Soma aos produtos no estoque a quantidade escolhida na venda
                    printf("\n-----------------------------------------------------------\n");
                    printf("*Produto %s retornado ao estoque.", produto->nome);
                    printf("\n-----------------------------------------------------------\n");
                }
            }
            return;
        } else {
            printf("\n-----------------------------------------------------------\n");
            printf("*Pagamento via Pix realizado com sucesso.");
            printf("\n-----------------------------------------------------------\n");
        }
    } else { //Se for escolhido um método inexistente
        printf("\n-----------------------------------------------------------\n");
        printf("*Metodo de pagamento invalido. Tente novamente.");
        printf("\n-----------------------------------------------------------\n");
        return;
    }

    salvarProdutos(produtos, *contador); // Salva o estado atualizado dos produtos

}
