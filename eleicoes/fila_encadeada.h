#include <iostream>
#include <cstdlib>
using namespace std;

typedef int elem;

typedef struct bloco {
    elem info;
    struct bloco *prox = NULL;
} no;

typedef struct {
    no *inicio, *fim;
    int total;
} Fila;

void Create_Queue(Fila *F);
void Enter_Queue(Fila *F, elem* X, bool *erro);
elem Out_Queue(Fila *F, bool *erro);
bool IsEmpty_Queue(Fila *F);
void Print_Queue(Fila *F);
void Search_Queue(Fila *F, elem x);

void Create_Queue(Fila *F) {
    F->inicio = NULL;
    F->fim = NULL;
    F->total = 0;
}

void Enter_Queue(Fila *F, elem *X, bool *erro) {
    no *novo_no;
    novo_no = (no*)malloc(sizeof(no));
    if (novo_no == NULL) {
        *erro = true;
    } else {
        *erro = false;
        novo_no->info = *X;
        novo_no->prox = NULL;
        if (F->inicio == NULL) {  // se for o primeiro a entrar na fila
            F->inicio = novo_no;
            F->fim = novo_no;
            F->total++;
        } else {  // se já tiver alguém na fila
            F->fim->prox = novo_no;
            F->fim = novo_no;
            F->total++;
        }
    }
}

elem Out_Queue(Fila *F, bool *erro) {
    if (!IsEmpty_Queue(F)) {
        *erro = false;
        elem X = F->inicio->info;
        no *aux = F->inicio;
        F->inicio = F->inicio->prox;
        free(aux);
        F->total--;
        if (F->inicio == NULL) {
            F->fim = NULL;
        }
        return X;
    } else {
        *erro = true;
        return -1;  // Valor inválido para indicar erro
    }
}

bool IsEmpty_Queue(Fila *F) {
    return (F->inicio == NULL);
}

void Print_Queue(Fila *F) {
    no *aux = F->inicio;
    cout << "Elementos da Fila (do inicio ao fim): ";
    while (aux != NULL) {
        cout << aux->info << " ";
        aux = aux->prox;
    }
    cout << endl;
}

void Search_Queue(Fila *F, elem x) {
    no *aux = F->inicio;
    while (aux != NULL) {
        if (aux->info == x) {
            cout << "Elemento " << x << " foi encontrado." << endl;
            return;
        }
        aux = aux->prox;
    }
    cout << "Elemento " << x << " não foi encontrado." << endl;
}