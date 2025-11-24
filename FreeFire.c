#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

enum CriterioOrdenacao {
    POR_NOME = 1,
    POR_TIPO = 2,
    POR_PRIORIDADE = 3
};

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
};

struct Item mochila[MAX_ITENS];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

void limparTela() {
    for(int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void exibirMenu() {
    printf("\n=== SISTEMA DE INVENTARIO - MACHADO OVERLORD - LUCIANO ===\n");
    printf("\n=== Free Fire ===\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar item (busca binaria)\n");
    printf("0. Sair\n");
    if(ordenadaPorNome) {
        printf("[Ordenada por nome]\n");
    }
    printf("Escolha: ");
}

void listarItens() {
    printf("\n=== ITENS NA MOCHILA ===\n");
    if(numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("\n%-5s %-15s %-12s %-10s %-10s\n", "No.", "Nome", "Tipo", "Qtd", "Prior");
    printf("------------------------------------------------------------\n");
    
    for(int i = 0; i < numItens; i++) {
        printf("%-5d %-15s %-12s %-10d %-10d\n", 
               i + 1, 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

void inserirItem() {
    if(numItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    
    printf("\nNome: ");
    scanf("%s", mochila[numItens].nome);
    printf("Tipo: ");
    scanf("%s", mochila[numItens].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);
    printf("Prioridade (1-5): ");
    scanf("%d", &mochila[numItens].prioridade);
    
    numItens++;
    ordenadaPorNome = false;
    printf("\nItem adicionado!\n");
}

void removerItem() {
    char nome[30];
    printf("\nNome do item: ");
    scanf("%s", nome);
    
    int pos = -1;
    for(int i = 0; i < numItens; i++) {
        if(strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }
    
    if(pos == -1) {
        printf("\nItem nao encontrado!\n");
        return;
    }
    
    for(int i = pos; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    numItens--;
    ordenadaPorNome = false;
    printf("\nItem removido!\n");
}

void ordenarPorNome() {
    comparacoes = 0;
    
    for(int i = 1; i < numItens; i++) {
        struct Item temp = mochila[i];
        int j = i - 1;
        
        while(j >= 0 && strcmp(mochila[j].nome, temp.nome) > 0) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        if(j >= 0) comparacoes++;
        mochila[j + 1] = temp;
    }
    
    ordenadaPorNome = true;
    printf("\nOrdenado por nome!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

void ordenarPorTipo() {
    comparacoes = 0;
    
    for(int i = 1; i < numItens; i++) {
        struct Item temp = mochila[i];
        int j = i - 1;
        
        while(j >= 0 && strcmp(mochila[j].tipo, temp.tipo) > 0) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        if(j >= 0) comparacoes++;
        mochila[j + 1] = temp;
    }
    
    ordenadaPorNome = false;
    printf("\nOrdenado por tipo!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

void ordenarPorPrioridade() {
    comparacoes = 0;
    
    for(int i = 1; i < numItens; i++) {
        struct Item temp = mochila[i];
        int j = i - 1;
        
        while(j >= 0 && mochila[j].prioridade < temp.prioridade) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        if(j >= 0) comparacoes++;
        mochila[j + 1] = temp;
    }
    
    ordenadaPorNome = false;
    printf("\nOrdenado por prioridade!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

void menuOrdenacao() {
    int op;
    
    printf("\n=== ORDENAR POR ===\n");
    printf("1. Nome\n");
    printf("2. Tipo\n");
    printf("3. Prioridade\n");
    printf("0. Voltar\n");
    printf("Escolha: ");
    scanf("%d", &op);
    
    limparTela();
    
    if(op == 1) {
        ordenarPorNome();
        listarItens();
    } else if(op == 2) {
        ordenarPorTipo();
        listarItens();
    } else if(op == 3) {
        ordenarPorPrioridade();
        listarItens();
    }
}

void buscaBinaria() {
    if(!ordenadaPorNome) {
        printf("\nPrecisa ordenar por nome primeiro!\n");
        return;
    }
    
    char nome[30];
    printf("\nNome do item: ");
    scanf("%s", nome);
    
    comparacoes = 0;
    int ini = 0;
    int fim = numItens - 1;
    int achou = 0;
    
    while(ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;
        
        int cmp = strcmp(mochila[meio].nome, nome);
        
        if(cmp == 0) {
            achou = 1;
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            printf("Comparacoes: %d\n", comparacoes);
            break;
        } else if(cmp < 0) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    if(!achou) {
        printf("\nItem nao encontrado!\n");
        printf("Comparacoes: %d\n", comparacoes);
    }
}

int main() {
    int op;
    
    do {
        exibirMenu();
        scanf("%d", &op);
        
        limparTela();
        
        if(op == 1) {
            inserirItem();
            listarItens();
        } else if(op == 2) {
            removerItem();
            listarItens();
        } else if(op == 3) {
            listarItens();
        } else if(op == 4) {
            menuOrdenacao();
        } else if(op == 5) {
            buscaBinaria();
        } else if(op == 0) {
            printf("\nSaindo...\n");
        } else {
            printf("\nOpcao invalida!\n");
        }
    } while(op != 0);
    
    return 0;
}