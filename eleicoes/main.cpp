#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Candidato {
    std::string nome;
    int numero;
    int votos;
};

struct Eleitor {
    std::string nome;
    int titulo;
    int idade;
};

void carregarCandidatos(std::vector<Candidato>& candidatos) {
    std::ifstream arquivo("candidatos.txt");
    if (!arquivo) {
        std::cout << "Erro ao abrir o arquivo de candidatos." << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            Candidato candidato;
            std::getline(arquivo, candidato.nome);
            arquivo >> candidato.numero;
            arquivo.ignore();
            candidato.votos = 0;
            candidatos.push_back(candidato);
        }
    }

    arquivo.close();
}

void carregarEleitores(std::vector<Eleitor>& eleitores) {
    std::ifstream arquivo("eleitores.txt");
    if (!arquivo) {
        std::cout << "Erro ao abrir o arquivo de eleitores." << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            Eleitor eleitor;
            std::getline(arquivo, eleitor.nome);
            arquivo >> eleitor.titulo;
            arquivo >> eleitor.idade;
            arquivo.ignore();
            eleitores.push_back(eleitor);
        }
    }

    arquivo.close();
}

void salvarCandidatos(const std::vector<Candidato>& candidatos) {
    std::ofstream arquivo("candidatos.txt");
    if (!arquivo) {
        std::cout << "Erro ao abrir o arquivo de candidatos." << std::endl;
        return;
    }

    for (const auto& candidato : candidatos) {
        arquivo << "Candidato: " << candidato.nome << std::endl;
        arquivo << "Numero: " << candidato.numero << std::endl;
    }

    arquivo.close();
}

void salvarEleitores(const std::vector<Eleitor>& eleitores) {
    std::ofstream arquivo("eleitores.txt");
    if (!arquivo) {
        std::cout << "Erro ao abrir o arquivo de eleitores." << std::endl;
        return;
    }

    for (const auto& eleitor : eleitores) {
        arquivo << "Eleitor: " << eleitor.nome << std::endl;
        arquivo << "Titulo: " << eleitor.titulo << std::endl;
        arquivo << "Idade: " << eleitor.idade << std::endl;
    }

    arquivo.close();
}

void inserirCandidato(std::vector<Candidato>& candidatos, const std::string& nome, int numero) {
    candidatos.push_back({nome, numero, 0});
}

void removerCandidato(std::vector<Candidato>& candidatos, int numero) {
    for (auto it = candidatos.begin(); it != candidatos.end(); ++it) {
        if (it->numero == numero) {
            candidatos.erase(it);
            return;
        }
    }
    std::cout << "Candidato não encontrado." << std::endl;
}

void listarCandidatos(const std::vector<Candidato>& candidatos) {
    std::cout << "========== Lista de Candidatos ==========" << std::endl;
    for (const auto& candidato : candidatos) {
        std::cout << "Nome: " << candidato.nome << std::endl;
        std::cout << "Número: " << candidato.numero << std::endl;
        std::cout << "Votos: " << candidato.votos << std::endl;
        std::cout << "=========================================" << std::endl;
    }
}

void inserirEleitor(std::vector<Eleitor>& eleitores, const std::string& nome, int titulo, int idade) {
    eleitores.push_back({nome, titulo, idade});
}

void removerEleitor(std::vector<Eleitor>& eleitores, int titulo) {
    for (auto it = eleitores.begin(); it != eleitores.end(); ++it) {
        if (it->titulo == titulo) {
            eleitores.erase(it);
            return;
        }
    }
    std::cout << "Eleitor não encontrado." << std::endl;
}

void listarEleitores(const std::vector<Eleitor>& eleitores) {
    std::cout << "========== Lista de Eleitores ==========" << std::endl;
    for (const auto& eleitor : eleitores) {
        std::cout << "Nome: " << eleitor.nome << std::endl;
        std::cout << "Título: " << eleitor.titulo << std::endl;
        std::cout << "Idade: " << eleitor.idade << std::endl;
        std::cout << "========================================" << std::endl;
    }
}

bool verificarAptidaoEleitor(int idade) {
    return idade >= 18;
}

void registrarVoto(const std::vector<Candidato>& candidatos, std::vector<int>& votos) {
    int numero;
    std::cout << "Digite o número do candidato: ";
    std::cin >> numero;

    auto it = std::find_if(candidatos.begin(), candidatos.end(), [numero](const Candidato& candidato) {
        return candidato.numero == numero;
    });

    if (it != candidatos.end()) {
        votos.push_back(numero);
        std::cout << "Voto registrado com sucesso." << std::endl;
    } else {
        std::cout << "Candidato não encontrado." << std::endl;
    }
}

void gerarRelatorio(const std::vector<Candidato>& candidatos, const std::vector<int>& votos) {
    std::ofstream arquivo("relatorio.txt");
    if (!arquivo) {
        std::cout << "Erro ao criar o arquivo de relatório." << std::endl;
        return;
    }

    arquivo << "========== Relatório de Eleição ==========" << std::endl;
    arquivo << "Total de votos registrados: " << votos.size() << std::endl;

    arquivo << "Total de votos por candidato:" << std::endl;
    for (const auto& candidato : candidatos) {
        arquivo << "Candidato: " << candidato.nome << std::endl;
        arquivo << "Número: " << candidato.numero << std::endl;
        arquivo << "Votos: " << candidato.votos << std::endl;
        arquivo << "------------------------------------------" << std::endl;
    }

    arquivo << "Total de eleitores faltosos: " << candidatos.size() - votos.size() << std::endl;

    arquivo.close();

    std::cout << "Relatório gerado com sucesso." << std::endl;
}

int main() {
    std::vector<Candidato> candidatos;
    std::vector<Eleitor> eleitores;
    std::vector<int> votos;

    carregarCandidatos(candidatos);
    carregarEleitores(eleitores);

    int opcao;
    do {
        std::cout << "===== Sistema de Eleições =====" << std::endl;
        std::cout << "1. Inserir candidato" << std::endl;
        std::cout << "2. Remover candidato" << std::endl;
        std::cout << "3. Listar candidatos" << std::endl;
        std::cout << "4. Inserir eleitor" << std::endl;
        std::cout << "5. Remover eleitor" << std::endl;
        std::cout << "6. Listar eleitores" << std::endl;
        std::cout << "7. Registrar voto" << std::endl;
        std::cout << "8. Gerar relatório" << std::endl;
        std::cout << "9. Sair" << std::endl;
        std::cout << "Digite a opção desejada: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                std::string nome;
                int numero;
                std::cout << "Digite o nome do candidato: ";
                std::cin.ignore();
                std::getline(std::cin, nome);
                std::cout << "Digite o número do candidato: ";
                std::cin >> numero;
                inserirCandidato(candidatos, nome, numero);
                break;
            }
            case 2: {
                int numero;
                std::cout << "Digite o número do candidato a ser removido: ";
                std::cin >> numero;
                removerCandidato(candidatos, numero);
                break;
            }
            case 3: {
                listarCandidatos(candidatos);
                break;
            }
            case 4: {
                std::string nome;
                int titulo, idade;
                std::cout << "Digite o nome do eleitor: ";
                std::cin.ignore();
                std::getline(std::cin, nome);
                std::cout << "Digite o número de título do eleitor: ";
                std::cin >> titulo;
                std::cout << "Digite a idade do eleitor: ";
                std::cin >> idade;
                inserirEleitor(eleitores, nome, titulo, idade);
                break;
            }
            case 5: {
                int titulo;
                std::cout << "Digite o número de título do eleitor a ser removido: ";
                std::cin >> titulo;
                removerEleitor(eleitores, titulo);
                break;
            }
            case 6: {
                listarEleitores(eleitores);
                break;
            }
            case 7: {
                int idade;
                std::cout << "Digite a idade do eleitor: ";
                std::cin >> idade;
                if (verificarAptidaoEleitor(idade)) {
                    registrarVoto(candidatos, votos);
                } else {
                    std::cout << "Eleitor não está apto para votar." << std::endl;
                }
                break;
            }
            case 8: {
                gerarRelatorio(candidatos, votos);
                break;
            }
            case 9: {
                salvarCandidatos(candidatos);
                salvarEleitores(eleitores);
                break;
            }
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
                break;
        }
    } while (opcao != 9);

    return 0;
}
