#include <iostream>
#include <fstream>

using namespace std;

struct Candidato {
    string nome;
    int numero;
};

struct Eleitor {
    string nome;
    int titulo;
    int idade;
};

struct Voto {
    int numeroCandidato;
    Voto* proximo;
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
ListaEleitores* filaVotos = nullptr;
Voto* votos = nullptr;

void inserirCandidato(string nome, int numero) {
    ListaCandidatos* novoCandidato = new ListaCandidatos;
    novoCandidato->candidato.nome = nome;
    novoCandidato->candidato.numero = numero;
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
}

void removerCandidato(int numero) {
    ListaCandidatos* anterior = nullptr;
    ListaCandidatos* atual = listaCandidatos;

    while (atual != nullptr && atual->candidato.numero != numero) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "Candidato nao encontrado." << endl;
        return;
    }

    if (anterior == nullptr) {
        listaCandidatos = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual;
}

void listarCandidatos() {
    ListaCandidatos* temp = listaCandidatos;
    while (temp != nullptr) {
        cout << "Nome: " << temp->candidato.nome << ", Numero: " << temp->candidato.numero << endl;
        temp = temp->proximo;
    }
}

void inserirEleitor(string nome, int titulo, int idade) {
    ListaEleitores* novoEleitor = new ListaEleitores;
    novoEleitor->eleitor.nome = nome;
    novoEleitor->eleitor.titulo = titulo;
    novoEleitor->eleitor.idade = idade;
    novoEleitor->proximo = nullptr;

    if (idade < 18) {
        delete novoEleitor;
        cout << "Eleitor nao apto para votar." << endl;
        return;
    }

    if (listaEleitores == nullptr) {
        listaEleitores = novoEleitor;
    } else {
        ListaEleitores* temp = listaEleitores;
        while (temp->proximo != nullptr) {
            temp = temp->proximo;
        }
        temp->proximo = novoEleitor;
    }
}

void removerEleitor(int titulo) {
    ListaEleitores* anterior = nullptr;
    ListaEleitores* atual = listaEleitores;

    while (atual != nullptr && atual->eleitor.titulo != titulo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "Eleitor nao encontrado." << endl;
        return;
    }

    if (anterior == nullptr) {
        listaEleitores = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual;
}

void listarEleitores() {
    ListaEleitores* temp = listaEleitores;
    while (temp != nullptr) {
        cout << "Nome: " << temp->eleitor.nome << ", Titulo: " << temp->eleitor.titulo << ", Idade: " << temp->eleitor.idade << endl;
        temp = temp->proximo;
    }
}

bool verificarEleitorApto(int idade) {
    return idade >= 18;
}

void registrarVoto(int numeroCandidato) {
    Voto* novoVoto = new Voto;
    novoVoto->numeroCandidato = numeroCandidato;
    novoVoto->proximo = nullptr;

    if (filaVotos == nullptr) {
        filaVotos = new ListaEleitores;
        filaVotos->eleitor = listaEleitores->eleitor;
        filaVotos->proximo = nullptr;
        votos = novoVoto;
    } else {
        ListaEleitores* temp = filaVotos;
        while (temp->proximo != nullptr) {
            temp = temp->proximo;
        }
        temp->proximo = new ListaEleitores;
        temp->proximo->eleitor = listaEleitores->eleitor;
        temp->proximo->proximo = nullptr;

        Voto* tempVotos = votos;
        while (tempVotos->proximo != nullptr) {
            tempVotos = tempVotos->proximo;
        }
        tempVotos->proximo = novoVoto;
    }
}

void gerarRelatorios() {
    ofstream arquivo("relatorio.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo de relatorio." << endl;
        return;
    }

    ListaCandidatos* tempCandidatos = listaCandidatos;
    int* votosCandidatos = new int[100];
    for (int i = 0; i < 100; i++) {
        votosCandidatos[i] = 0;
    }

    Voto* tempVotos = votos;
    int totalVotos = 0;
    while (tempVotos != nullptr) {
        votosCandidatos[tempVotos->numeroCandidato]++;
        totalVotos++;
        tempVotos = tempVotos->proximo;
    }

    arquivo << "Relatorio de Votos\n" << endl;

    arquivo << "Quantidade de votos por candidato:" << endl;
    while (tempCandidatos != nullptr) {
        arquivo << "Candidato: " << tempCandidatos->candidato.nome << ", Numero: " << tempCandidatos->candidato.numero << ", Votos: " << votosCandidatos[tempCandidatos->candidato.numero] << endl;
        tempCandidatos = tempCandidatos->proximo;
    }

    arquivo << "\nTotal de votos registrados: " << totalVotos << endl;

    int eleitoresFaltantes = 0;
    ListaEleitores* tempEleitores = listaEleitores;
    while (tempEleitores != nullptr) {
        eleitoresFaltantes++;
        tempEleitores = tempEleitores->proximo;
    }
    arquivo << "Quantidade de eleitores faltantes: " << eleitoresFaltantes << endl;

    arquivo.close();
    cout << "Relatorios gerados com sucesso." << endl;
}

void salvarDados() {
    ofstream arquivo("dados.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo de dados." << endl;
        return;
    }

    ListaCandidatos* tempCandidatos = listaCandidatos;
    while (tempCandidatos != nullptr) {
        arquivo << tempCandidatos->candidato.nome << " " << tempCandidatos->candidato.numero << endl;
        tempCandidatos = tempCandidatos->proximo;
    }
    arquivo << "-1" << endl;

    ListaEleitores* tempEleitores = listaEleitores;
    while (tempEleitores != nullptr) {
        arquivo << tempEleitores->eleitor.nome << " " << tempEleitores->eleitor.titulo << " " << tempEleitores->eleitor.idade << endl;
        tempEleitores = tempEleitores->proximo;
    }
    arquivo << "-1" << endl;

    Voto* tempVotos = votos;
    while (tempVotos != nullptr) {
        arquivo << tempVotos->numeroCandidato << endl;
        tempVotos = tempVotos->proximo;
    }
    arquivo << "-1" << endl;

    arquivo.close();
    cout << "Dados salvos com sucesso." << endl;
}

void carregarDados() {
    ifstream arquivo("dados.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo de dados." << endl;
        return;
    }

    string linha;
    getline(arquivo, linha);

    while (linha != "-1") {
        string nome = linha.substr(0, linha.find(' '));
        int numero = stoi(linha.substr(linha.find(' ') + 1));
        inserirCandidato(nome, numero);
        getline(arquivo, linha);
    }

    getline(arquivo, linha);
    while (linha != "-1") {
        string nome = linha.substr(0, linha.find(' '));
        linha = linha.substr(linha.find(' ') + 1);
        int titulo = stoi(linha.substr(0, linha.find(' ')));
        linha = linha.substr(linha.find(' ') + 1);
        int idade = stoi(linha);
        inserirEleitor(nome, titulo, idade);
        getline(arquivo, linha);
    }

    getline(arquivo, linha);
    while (linha != "-1") {
        int numeroCandidato = stoi(linha);
        registrarVoto(numeroCandidato);
        getline(arquivo, linha);
    }

    arquivo.close();
    cout << "Dados carregados com sucesso." << endl;
}

void exibirMenu() {
    cout << "=== Simulador de Eleicao ===" << endl;
    cout << "1. Cadastrar candidato" << endl;
    cout << "2. Remover candidato" << endl;
    cout << "3. Listar candidatos" << endl;
    cout << "4. Cadastrar eleitor" << endl;
    cout << "5. Remover eleitor" << endl;
    cout << "6. Listar eleitores" << endl;
    cout << "7. Registrar voto" << endl;
    cout << "8. Gerar relatorios" << endl;
    cout << "9. Salvar dados" << endl;
    cout << "10. Carregar dados" << endl;
    cout << "11. Sair" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    int opcao;
    string nome;
    int numero;
    int titulo;
    int idade;

    do {
        exibirMenu();
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Digite o nome do candidato: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Digite o numero do candidato: ";
                cin >> numero;
                inserirCandidato(nome, numero);
                break;
            case 2:
                cout << "Digite o numero do candidato a ser removido: ";
                cin >> numero;
                removerCandidato(numero);
                break;
            case 3:
                listarCandidatos();
                break;
            case 4:
                cout << "Digite o nome do eleitor: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Digite o titulo do eleitor: ";
                cin >> titulo;
                cout << "Digite a idade do eleitor: ";
                cin >> idade;
                inserirEleitor(nome, titulo, idade);
                break;
            case 5:
                cout << "Digite o titulo do eleitor a ser removido: ";
                cin >> titulo;
                removerEleitor(titulo);
                break;
            case 6:
                listarEleitores();
                break;
            case 7:
                if (listaEleitores == nullptr) {
                    cout << "Nenhum eleitor cadastrado." << endl;
                    break;
                }
                cout << "Digite o titulo do eleitor: ";
                cin >> titulo;
                cout << "Digite o numero do candidato escolhido: ";
                cin >> numero;
                registrarVoto(numero);
                break;
            case 8:
                gerarRelatorios();
                break;
            case 9:
                salvarDados();
                break;
            case 10:
                carregarDados();
                break;
            case 11:
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opcao invalida." << endl;
                break;
        }

        cout << endl;
    } while (opcao != 11);

    return 0;
}
