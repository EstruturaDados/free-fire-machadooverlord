#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

struct Item mochila[MAX_ITENS];
int numItens = 0;

void limparTela() {
    for(int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void exibirMenu() {
    printf("\n=== SISTEMA DE INVENTARIO ===\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void inserirItem() {
    if(numItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    
    printf("\nNome do item: ");
    scanf("%s", mochila[numItens].nome);
    printf("Tipo do item: ");
    scanf("%s", mochila[numItens].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);
    
    numItens++;
    printf("\nItem adicionado com sucesso!\n");
}

void removerItem() {
    char nomeBusca[30];
    printf("\nNome do item a remover: ");
    scanf("%s", nomeBusca);
    
    bool encontrado = false;
    int posicao = -1;
    
    for(int i = 0; i < numItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = true;
            posicao = i;
            break;
        }
    }
    
    if(!encontrado) {
        printf("\nItem nao encontrado!\n");
        return;
    }
    
    for(int i = posicao; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    numItens--;
    printf("\nItem removido com sucesso!\n");
}

void listarItens() {
    printf("\n=== ITENS NA MOCHILA ===\n");
    if(numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("\n%-5s %-20s %-15s %-10s\n", "No.", "Nome", "Tipo", "Quantidade");
    printf("-----------------------------------------------------------\n");
    
    for(int i = 0; i < numItens; i++) {
        printf("%-5d %-20s %-15s %-10d\n", 
               i + 1, 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
}

int main() {
    int opcao;
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        
        limparTela();
        
        switch(opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}