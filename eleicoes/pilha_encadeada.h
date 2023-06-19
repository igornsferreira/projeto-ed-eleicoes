#include <iostream>
#include <cstdlib>
using namespace std;

typedef int elem;

typedef struct bloco {
    elem info;
    struct bloco *prox = NULL;
} no;

typedef struct {
    no *topo = NULL;
    int total;
} Pilha;

void Create_Stack(Pilha *P);
void Push(Pilha *P, elem *X, bool *erro);
void Pop(Pilha *P, elem* X, bool *erro);
bool IsEmpty_Stack(Pilha *P);
void Print_Stack(Pilha *P);

void Create_Stack(Pilha *P) {
    P->topo = NULL;
    P->total = 0;
}

void Push(Pilha *P, elem *X, bool *erro) {
    no *novo_no = (no*)malloc(sizeof(no));
    if (novo_no == NULL) {
        *erro = true;
    } else {
        *erro = false;
        novo_no->info = *X;
        novo_no->prox = P->topo;
        P->topo = novo_no;
        P->total++;
    }
}

void Pop(Pilha *P, elem* X, bool *erro) {
    if (!IsEmpty_Stack(P)) {
        no *aux = P->topo;
        *X = aux->info;
        P->topo = aux->prox;
        free(aux);
        P->total--;
        *erro = false;
    } else {
        *erro = true;
        *X = -1;  // Valor inválido para indicar erro
    }
}

bool IsEmpty_Stack(Pilha *P) {
    return (P->topo == NULL);
}

void Print_Stack(Pilha *P) {
    no *aux = P->topo;
    cout << "Elementos da Pilha (do topo até a base):" << endl;
    while (aux != NULL) {
        cout << aux->info << endl;
        aux = aux->prox;
    }
}

