#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct igual ao nível novato
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista (apenas para a segunda mochila)
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Contadores
int compSeq = 0;
int compBin = 0;

// ------------------------------------------------------------
// FUNÇÕES DO VETOR — MESMA CARA DO NÍVEL NOVATO
// ------------------------------------------------------------

void inserirItemVetor(Item vet[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;

    printf("Nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    vet[*total] = novo;
    (*total)++;

    printf("Item inserido!\n");
}

void listarItensVetor(Item vet[], int total) {
    printf("\n--- Itens (vetor) ---\n");
    if (total == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d) %s | %s | %d\n", i+1, vet[i].nome, vet[i].tipo, vet[i].quantidade);
    }
}

void removerItemVetor(Item vet[], int *total) {
    if (*total == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(vet[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                vet[j] = vet[j+1];
            }
            (*total)--;
            printf("Item removido!\n");
            return;
        }
    }

    printf("Não encontrado.\n");
}

int buscarSequencialVetor(Item vet[], int total, char nome[]) {
    compSeq = 0;

    for (int i = 0; i < total; i++) {
        compSeq++;
        if (strcmp(vet[i].nome, nome) == 0) return i;
    }

    return -1;
}

void ordenarVetor(Item vet[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (strcmp(vet[j].nome, vet[j+1].nome) > 0) {
                Item temp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
            }
        }
    }
    printf("Itens ordenados!\n");
}

int buscarBinariaVetor(Item vet[], int total, char nome[]) {
    compBin = 0;
    int ini = 0, fim = total - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        compBin++;

        int cmp = strcmp(nome, vet[meio].nome);

        if (cmp == 0) return meio;
        if (cmp > 0) ini = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// ------------------------------------------------------------
// FUNÇÕES DA LISTA — MESMA SIMPLICIDADE DO NOVATO
// ------------------------------------------------------------

void inserirItemLista(No **lista) {
    No *novo = malloc(sizeof(No));

    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *lista;
    *lista = novo;

    printf("Item inserido!\n");
}

void listarItensLista(No *lista) {
    printf("\n--- Itens (lista encadeada) ---\n");
    if (lista == NULL) {
        printf("Mochila vazia!\n");
        return;
    }

    No *aux = lista;
    while (aux != NULL) {
        printf("%s | %s | %d\n", aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

void removerItemLista(No **lista) {
    if (*lista == NULL) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *aux = *lista, *ant = NULL;

    while (aux != NULL) {
        if (strcmp(aux->dados.nome, nome) == 0) {
            if (ant == NULL)
                *lista = aux->proximo;
            else
                ant->proximo = aux->proximo;

            free(aux);
            printf("Item removido!\n");
            return;
        }
        ant = aux;
        aux = aux->proximo;
    }

    printf("Não encontrado.\n");
}

int buscarSequencialLista(No *lista, char nome[]) {
    compSeq = 0;

    No *aux = lista;
    while (aux != NULL) {
        compSeq++;
        if (strcmp(aux->dados.nome, nome) == 0) return 1;
        aux = aux->proximo;
    }

    return 0;
}

// ------------------------------------------------------------
// MENU — IGUAL AO NÍVEL NOVATO, SÓ COM DOIS SISTEMAS
// ------------------------------------------------------------

int main() {
    Item mochilaVet[MAX_ITENS];
    int totalVet = 0;

    No *mochilaLista = NULL;

    int opc, modo;

    do {
        printf("\n=== Escolha o tipo de mochila ===\n");
        printf("1 - Mochila com Vetor\n");
        printf("2 - Mochila com Lista Encadeada\n");
        printf("0 - Sair\n");
        scanf("%d", &modo);
        getchar();

        if (modo == 1) {
            do {
                printf("\n--- Mochila (VETOR) ---\n");
                printf("1 - Inserir\n");
                printf("2 - Remover\n");
                printf("3 - Listar\n");
                printf("4 - Buscar sequencial\n");
                printf("5 - Ordenar\n");
                printf("6 - Buscar binária\n");
                printf("0 - Voltar\n");
                scanf("%d", &opc);
                getchar();

                if (opc == 1) inserirItemVetor(mochilaVet, &totalVet);
                else if (opc == 2) removerItemVetor(mochilaVet, &totalVet);
                else if (opc == 3) listarItensVetor(mochilaVet, totalVet);
                else if (opc == 4) {
                    char nome[30];
                    printf("Nome: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    int pos = buscarSequencialVetor(mochilaVet, totalVet, nome);

                    if (pos != -1) printf("Encontrado! Comparações: %d\n", compSeq);
                    else printf("Não encontrado! Comparações: %d\n", compSeq);
                }
                else if (opc == 5) ordenarVetor(mochilaVet, totalVet);
                else if (opc == 6) {
                    char nome[30];
                    printf("Nome: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    int pos = buscarBinariaVetor(mochilaVet, totalVet, nome);

                    if (pos != -1) printf("Encontrado! Comparações: %d\n", compBin);
                    else printf("Não encontrado! Comparações: %d\n", compBin);
                }

            } while (opc != 0);
        }

        else if (modo == 2) {
            do {
                printf("\n--- Mochila (LISTA) ---\n");
                printf("1 - Inserir\n");
                printf("2 - Remover\n");
                printf("3 - Listar\n");
                printf("4 - Buscar sequencial\n");
                printf("0 - Voltar\n");
                scanf("%d", &opc);
                getchar();

                if (opc == 1) inserirItemLista(&mochilaLista);
                else if (opc == 2) removerItemLista(&mochilaLista);
                else if (opc == 3) listarItensLista(mochilaLista);
                else if (opc == 4) {
                    char nome[30];
                    printf("Nome: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    int achou = buscarSequencialLista(mochilaLista, nome);

                    if (achou) printf("Encontrado! Comparações: %d\n", compSeq);
                    else printf("Não encontrado! Comparações: %d\n", compSeq);
                }

            } while (opc != 0);
        }

    } while (modo != 0);

    return 0;
}
