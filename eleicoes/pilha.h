#include <iostream>
#define TAM_PILHA 10

using namespace std;
typedef int elem;

typedef struct {
    int topo;
    elem itens[TAM_PILHA];
} Pilha;

void Create(Pilha *P) {
    P->topo = -1;
}

bool IsFull(Pilha *P) {
    return (P->topo == TAM_PILHA - 1);
}

bool IsEmpty(Pilha *P) {
    return (P->topo == -1);
}

void Push(Pilha *P, elem *X, bool *erro) {
    if (!IsFull(P)) {
        P->topo++;
        P->itens[P->topo] = *X;
        *erro = false;
    } else {
        *erro = true;
    }
}

void Empty(Pilha *P) {
    for (; P->topo >= 0; P->topo--) {
        P->itens[P->topo] = 0;
    }
    // ou faz da seguinte forma:
    // P->topo = -1;
}

elem Pop(Pilha *P, bool *erro) {
    if (!IsEmpty(P)) {
        elem X = P->itens[P->topo];
        P->topo--;
        *erro = false;
        return X;
    } else {
        *erro = true;
        return -1;  // Valor inválido para indicar erro
    }
}
