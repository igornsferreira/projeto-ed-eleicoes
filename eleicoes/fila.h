#include <iostream>
#define TAM_FILA 5

using namespace std;
typedef int elem;

typedef struct {
    int inicio, fim, total;
    elem itens[TAM_FILA];
} Fila;

void Create(Fila *F) {
    F->inicio = 0;
    F->fim = 0;
    F->total = 0;
}

void Empty(Fila *F) {
    F->inicio = 0;
    F->fim = 0;
    F->total = 0;
}

bool IsEmpty(Fila *F) {
    return (F->total == 0);
}

bool IsFull(Fila *F) {
    return (F->total == TAM_FILA);
}

void Enter(Fila *F, elem *X, bool *erro) {
    if (!IsFull(F)) {
        *erro = false;
        F->itens[F->fim] = *X;
        F->fim = (F->fim + 1) % TAM_FILA;
        F->total++;
    } else {
        *erro = true;
    }
}

elem Out(Fila *F, bool *erro) {
    if (!IsEmpty(F)) {
        *erro = false;
        elem X = F->itens[F->inicio];
        F->inicio = (F->inicio + 1) % TAM_FILA;
        F->total--;
        return X;
    } else {
        *erro = true;
        return -1;  // Valor inválido para indicar erro
    }
}

void Print(Fila *F) {
    if (IsEmpty(F)) {
        cout << "Ninguém na fila." << endl;
    } else {
        int pos = F->inicio;
        for (int i = 0; i < F->total; i++) {
            cout << F->itens[pos] << "\t";
            pos = (pos + 1) % TAM_FILA;
        }
        cout << endl;
    }
}
