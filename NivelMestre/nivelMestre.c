#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

int ordenadoPorNome = 0; // <<< CONTROLE GLOBAL

// ---------------------------------------------
// ADICIONAR ITEM
// ---------------------------------------------
void adicionarItem(Item mochila[], int *total) {
    if (*total >= MAX) {
        printf("\nMochila cheia! Não dá pra colocar mais nada.\n");
        return;
    }

    Item novo;

    printf("\nNome do Componente: ");
    scanf("%s", novo.nome);

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &novo.prioridade);

    mochila[*total] = novo;
    (*total)++;

    ordenadoPorNome = 0; // <<< INSERIU = PERDE A ORDEM

    printf("\nComponente '%s' adicionado!\n", novo.nome);
}

// ---------------------------------------------
// DESCARTAR ITEM
// ---------------------------------------------
void descartarItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nNenhum item na mochila para descartar.\n");
        return;
    }

    char nomeBuscado[30];
    printf("\nNome do Componente a descartar: ");
    scanf("%s", nomeBuscado);

    int encontrado = 0;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBuscado) == 0) {
            encontrado = 1;

            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*total)--;

            ordenadoPorNome = 0; // <<< REMOVER TAMBÉM DESORDENA

            printf("\nComponente '%s' descartado!\n", nomeBuscado);
            break;
        }
    }

    if (!encontrado)
        printf("\nComponente não encontrado!\n");
}

// ---------------------------------------------
// LISTAR ITENS
// ---------------------------------------------
void listarItens(Item mochila[], int total) {
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", total, MAX);
    printf("--------------------------------------------------------------\n");
    printf(" NOME         | TIPO         | QUANTIDADE | PRIORIDADE\n");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf(" %-12s | %-12s | %-10d | %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

// ---------------------------------------------
// ORDENAR ITENS (3 CRITÉRIOS)
// ---------------------------------------------
void ordenarItens(Item mochila[], int total) {
    if (total < 2) {
        printf("\nPoucos itens para ordenar.\n");
        return;
    }

    int opcao;

    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabetica)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 0) {
        printf("\nOrdenacao cancelada.\n");
        return;
    }

    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {

            int trocar = 0;

            if (opcao == 1) { // Ordenar por nome
                if (strcmp(mochila[i].nome, mochila[j].nome) > 0) trocar = 1;
            }
            else if (opcao == 2) { // Ordenar por tipo
                if (strcmp(mochila[i].tipo, mochila[j].tipo) > 0) trocar = 1;
            }
            else if (opcao == 3) { // Ordenar por prioridade
                if (mochila[i].prioridade > mochila[j].prioridade) trocar = 1;
            }

            if (trocar) {
                Item aux = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = aux;
            }
        }
    }

    if (opcao == 1)
        ordenadoPorNome = 1;  // <<< AGORA ESTÁ ORDENADO
    else
        ordenadoPorNome = 0;  // <<< OUTRO TIPO DE ORDEM NÃO SERVE PARA BINÁRIA

    printf("\nComponentes organizados com sucesso!\n");
}

// ---------------------------------------------
// BUSCA BINÁRIA (MOSTRA ALERTA SE NÃO ORDENADO)
// ---------------------------------------------
int buscaBinaria(Item mochila[], int total, char alvo[]) {
    int esquerda = 0, direita = total - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;

        int cmp = strcmp(alvo, mochila[meio].nome);

        if (cmp == 0) return meio;
        else if (cmp > 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

// ---------------------------------------------
// BUSCAR ITEM (BINÁRIA COM ALERTA)
// ---------------------------------------------
void buscarItem(Item mochila[], int total) {
    if (!ordenadoPorNome) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a opcao 4 para organizar a mochila primeiro.\n");
        return;
    }

    char nomeBuscado[30];
    printf("\nBuscar componente pelo nome: ");
    scanf("%s", nomeBuscado);

    int pos = buscaBinaria(mochila, total, nomeBuscado);

    if (pos == -1)
        printf("\nNada encontrado com esse nome.\n");
    else {
        printf("\nComponente encontrado!\n");
        printf("Nome: %s\n", mochila[pos].nome);
        printf("Tipo: %s\n", mochila[pos].tipo);
        printf("Quantidade: %d\n", mochila[pos].quantidade);
        printf("Prioridade: %d\n", mochila[pos].prioridade);
    }
}

// ---------------------------------------------
// MAIN
// ---------------------------------------------
int main() {
    Item mochila[MAX];
    int total = 0;
    int opcao;

    do {
        printf("\n\n=============================\n");
        printf(" PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf(" Itens na Mochila: %d/%d\n", total, MAX);
        printf(" Status da Ordenacao por Nome: %s\n",
               ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("=============================\n");

        printf("\n1 - Adicionar Componente\n");
        printf("2 - Descartar Componente\n");
        printf("3 - Listar Componentes (Inventario)\n");
        printf("4 - Organizar Componentes (Ordenar)\n");
        printf("5 - Buscar Componente-Chave (Busca Binaria)\n");
        printf("6 - ATIVAR TORRE DE FUGA (Sair)\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarItem(mochila, &total); break;
            case 2: descartarItem(mochila, &total); break;
            case 3: listarItens(mochila, total); break;
            case 4: ordenarItens(mochila, total); break;
            case 5: buscarItem(mochila, total); break;
            case 6: printf("\nTorre ativada. Boa sorte na fuga!\n"); break;
            default: printf("\nOpcao invalida.\n");
        }

    } while (opcao != 6);

    return 0;
}
