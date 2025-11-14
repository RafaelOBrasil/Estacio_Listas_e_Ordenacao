#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct básica, do jeitão clássico.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções principais
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n=== SISTEMA DE INVENTÁRIO ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {
            case 1: inserirItem(mochila, &total); break;
            case 2: removerItem(mochila, &total); break;
            case 3: listarItens(mochila, total); break;
            case 4: buscarItem(mochila, total); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}

void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia! Não cabe mais nada.\n");
        return;
    }

    Item novo;

    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*total] = novo;
    (*total)++;

    printf("Item inserido com sucesso!\n");
    listarItens(mochila, *total);
}

void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item a remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int i, encontrado = -1;

    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item não encontrado.\n");
        return;
    }

    for (i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;
    printf("Item removido!\n");
    listarItens(mochila, *total);
}

void listarItens(Item mochila[], int total) {
    printf("\n=== ITENS NA MOCHILA ===\n");

    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
            i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    printf("Nome do item a buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n",
                mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("Item não encontrado.\n");
}
