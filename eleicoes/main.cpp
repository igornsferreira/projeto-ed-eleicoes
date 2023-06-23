#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Candidato {
    string nome;
    int numero;
    int votos;
};

struct Eleitor {
    string nome;
    int titulo;
    int idade;
    bool votou;
};

struct ListaCandidatos {
    Candidato candidato;
    ListaCandidatos* proximo;
};

struct ListaEleitores {
    Eleitor eleitor;
    ListaEleitores* proximo;
};

ListaCandidatos* listaCandidatos = nullptr;
ListaEleitores* listaEleitores = nullptr;

void inserirCandidato(string nome, int numero) {
    ListaCandidatos* novoCandidato = new ListaCandidatos;
    novoCandidato->candidato.nome = nome;
    novoCandidato->candidato.numero = numero;
    novoCandidato->candidato.votos = 0;
    novoCandidato->proximo = nullptr;

    if (listaCandidatos == nullptr) {
        listaCandidatos = novoCandidato;
    } else {
        ListaCandidatos* temp = listaCandidatos;
        while (temp->proximo != nullptr) {
            temp = temp->proximo;
        }
        temp->proximo = novoCandidato;
    }

    cout << "Candidato inserido com sucesso." << endl;
}

void removerCandidato(int numero) {
    if (listaCandidatos == nullptr) {
        cout << "Nao ha candidatos cadastrados." << endl;
        return;
    }

    if (listaCandidatos->candidato.numero == numero) {
        ListaCandidatos* candidatoRemovido = listaCandidatos;
        listaCandidatos = listaCandidatos->proximo;
        delete candidatoRemovido;
        cout << "Candidato removido com sucesso." << endl;
        return;
    }

    ListaCandidatos* temp = listaCandidatos->proximo;
    ListaCandidatos* tempAnterior = listaCandidatos;
    while (temp != nullptr) {
        if (temp->candidato.numero == numero) {
            tempAnterior->proximo = temp->proximo;
            delete temp;
            cout << "Candidato removido com sucesso." << endl;
            return;
        }
        tempAnterior = temp;
        temp = temp->proximo;
    }

    cout << "Nao foi encontrado um candidato com o numero fornecido." << endl;
}

void listarCandidatos() {
    if (listaCandidatos == nullptr) {
        cout << "Nao ha candidatos cadastrados." << endl;
        return;
    }

    ListaCandidatos* temp = listaCandidatos;
    cout << "---- Candidatos Cadastrados ----" << endl;
    while (temp != nullptr) {
        cout << "Nome: " << temp->candidato.nome << endl;
        cout << "Numero: " << temp->candidato.numero << endl;
        cout << "Votos: " << temp->candidato.votos << endl;
        cout << "-----------------------------" << endl;
        temp = temp->proximo;
    }
}

void inserirEleitor(string nome, int titulo, int idade) {
    ListaEleitores* novoEleitor = new ListaEleitores;
    novoEleitor->eleitor.nome = nome;
    novoEleitor->eleitor.titulo = titulo;
    novoEleitor->eleitor.idade = idade;
    novoEleitor->eleitor.votou = false;
    novoEleitor->proximo = nullptr;

    if (listaEleitores == nullptr) {
        listaEleitores = novoEleitor;
    } else {
        ListaEleitores* temp = listaEleitores;
        while (temp->proximo != nullptr) {
            temp = temp->proximo;
        }
        temp->proximo = novoEleitor;
    }

    cout << "Eleitor inserido com sucesso." << endl;
}

void removerEleitor(int titulo) {
    if (listaEleitores == nullptr) {
        cout << "Nao ha eleitores cadastrados." << endl;
        return;
    }

    if (listaEleitores->eleitor.titulo == titulo) {
        ListaEleitores* eleitorRemovido = listaEleitores;
        listaEleitores = listaEleitores->proximo;
        delete eleitorRemovido;
        cout << "Eleitor removido com sucesso." << endl;
        return;
    }

    ListaEleitores* temp = listaEleitores->proximo;
    ListaEleitores* tempAnterior = listaEleitores;
    while (temp != nullptr) {
        if (temp->eleitor.titulo == titulo) {
            tempAnterior->proximo = temp->proximo;
            delete temp;
            cout << "Eleitor removido com sucesso." << endl;
            return;
        }
        tempAnterior = temp;
        temp = temp->proximo;
    }

    cout << "Nao foi encontrado um eleitor com o titulo fornecido." << endl;
}

void listarEleitores() {
    if (listaEleitores == nullptr) {
        cout << "Nao ha eleitores cadastrados." << endl;
        return;
    }

    ListaEleitores* temp = listaEleitores;
    cout << "---- Eleitores Cadastrados ----" << endl;
    while (temp != nullptr) {
        cout << "Nome: " << temp->eleitor.nome << endl;
        cout << "Titulo: " << temp->eleitor.titulo << endl;
        cout << "Idade: " << temp->eleitor.idade << endl;
        cout << "Votou: " << (temp->eleitor.votou ? "Sim" : "Nao") << endl;
        cout << "-----------------------------" << endl;
        temp = temp->proximo;
    }
}

void votar(int titulo, int numero) {
    ListaEleitores* tempEleitor = listaEleitores;
    while (tempEleitor != nullptr) {
        if (tempEleitor->eleitor.titulo == titulo) {
            if (tempEleitor->eleitor.votou) {
                cout << "Este eleitor ja votou." << endl;
                return;
            }
            tempEleitor->eleitor.votou = true;
            break;
        }
        tempEleitor = tempEleitor->proximo;
    }

    ListaCandidatos* tempCandidato = listaCandidatos;
    while (tempCandidato != nullptr) {
        if (tempCandidato->candidato.numero == numero) {
            tempCandidato->candidato.votos++;
            cout << "Voto registrado com sucesso." << endl;
            return;
        }
        tempCandidato = tempCandidato->proximo;
    }

    cout << "Nao foi encontrado um candidato com o numero fornecido." << endl;
}

void gerarRelatorio() {
    ofstream arquivo;
    arquivo.open("relatorio.txt");

    // Classificação dos candidatos
    arquivo << "---- Classificacao dos Candidatos ----" << endl;
    ListaCandidatos* tempCandidato = listaCandidatos;
    while (tempCandidato != nullptr) {
        arquivo << "Nome: " << tempCandidato->candidato.nome << endl;
        arquivo << "Numero: " << tempCandidato->candidato.numero << endl;
        arquivo << "Votos: " << tempCandidato->candidato.votos << endl;
        arquivo << "-----------------------------" << endl;
        tempCandidato = tempCandidato->proximo;
    }

    // Quantos votos cada candidato obteve
    arquivo << endl;
    arquivo << "---- Votos por Candidato ----" << endl;
    tempCandidato = listaCandidatos;
    while (tempCandidato != nullptr) {
        arquivo << "Nome: " << tempCandidato->candidato.nome << endl;
        arquivo << "Numero: " << tempCandidato->candidato.numero << endl;
        arquivo << "Votos: " << tempCandidato->candidato.votos << endl;
        arquivo << "-----------------------------" << endl;
        tempCandidato = tempCandidato->proximo;
    }

    // Quantos eleitores faltaram na eleição
    int eleitoresFaltantes = 0;
    ListaEleitores* tempEleitor = listaEleitores;
    while (tempEleitor != nullptr) {
        if (!tempEleitor->eleitor.votou) {
            eleitoresFaltantes++;
        }
        tempEleitor = tempEleitor->proximo;
    }

    arquivo << endl;
    arquivo << "---- Eleitores que Faltaram ----" << endl;
    arquivo << "Quantidade: " << eleitoresFaltantes << endl;

    arquivo.close();

    cout << "Relatorio gerado com sucesso." << endl;
}

int main() {
    int opcao;

    do {
        cout << "---- Sistema de Votacao ----" << endl;
        cout << "1 - Inserir candidato" << endl;
        cout << "2 - Remover candidato" << endl;
        cout << "3 - Listar candidatos" << endl;
        cout << "4 - Inserir eleitor" << endl;
        cout << "5 - Remover eleitor" << endl;
        cout << "6 - Listar eleitores" << endl;
        cout << "7 - Votar" << endl;
        cout << "8 - Gerar relatorio" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 1: {
                string nome;
                int numero;
                cout << "Digite o nome do candidato: ";
                cin >> nome;
                cout << "Digite o numero do candidato: ";
                cin >> numero;
                inserirCandidato(nome, numero);
                break;
            }
            case 2: {
                int numero;
                cout << "Digite o numero do candidato a ser removido: ";
                cin >> numero;
                removerCandidato(numero);
                break;
            }
            case 3: {
                listarCandidatos();
                break;
            }
            case 4: {
                string nome;
                int titulo, idade;
                cout << "Digite o nome do eleitor: ";
                cin >> nome;
                cout << "Digite o titulo do eleitor: ";
                cin >> titulo;
                cout << "Digite a idade do eleitor: ";
                cin >> idade;
                inserirEleitor(nome, titulo, idade);
                break;
            }
            case 5: {
                int titulo;
                cout << "Digite o titulo do eleitor a ser removido: ";
                cin >> titulo;
                removerEleitor(titulo);
                break;
            }
            case 6: {
                listarEleitores();
                break;
            }
            case 7: {
                int titulo, numero;
                cout << "Digite o titulo do eleitor: ";
                cin >> titulo;
                cout << "Digite o numero do candidato: ";
                cin >> numero;
                votar(titulo, numero);
                break;
            }
            case 8: {
                gerarRelatorio();
                break;
            }
            case 0: {
                cout << "Saindo..." << endl;
                break;
            }
            default: {
                cout << "Opcao invalida. Digite novamente." << endl;
                break;
            }
        }

        cout << endl;
    } while (opcao != 0);

    return 0;
}
