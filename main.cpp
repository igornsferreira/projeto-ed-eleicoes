#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Candidato {
    std::string nome;
    int numero;
};

struct Eleitor {
    std::string nome;
    int titulo;
};

struct Voto {
    int numeroCandidato;
};

void cadastrarCandidatos(std::vector<Candidato>& candidatos) {
    std::ifstream arquivo("candidatos.txt");
    std::string linha;

    while (std::getline(arquivo, linha)) {
        if (linha.find("Candidato: ") != std::string::npos) {
            Candidato candidato;
            candidato.nome = linha.substr(11);
            
            std::getline(arquivo, linha);
            candidato.numero = std::stoi(linha.substr(8));
            
            candidatos.push_back(candidato);
        }
    }
    
    arquivo.close();
}

void listarCandidatos(const std::vector<Candidato>& candidatos) {
    for (const auto& candidato : candidatos) {
        std::cout << "Nome: " << candidato.nome << ", Número: " << candidato.numero << std::endl;
    }
}

void cadastrarEleitores(std::vector<Eleitor>& eleitores) {
    int quantidadeEleitores;
    std::cout << "Quantos eleitores deseja cadastrar? ";
    std::cin >> quantidadeEleitores;
    
    for (int i = 0; i < quantidadeEleitores; ++i) {
        Eleitor eleitor;
        std::cout << "Digite o nome do eleitor: ";
        std::cin.ignore();
        std::getline(std::cin, eleitor.nome);
        std::cout << "Digite o número de título do eleitor: ";
        std::cin >> eleitor.titulo;
        
        eleitores.push_back(eleitor);
    }
}

bool verificarAptidaoEleitor(int idade) {
    return idade >= 18;
}

void registrarVoto(const std::vector<Candidato>& candidatos, const std::vector<Eleitor>& eleitores, std::vector<Voto>& votos) {
    int numeroTitulo;
    std::cout << "Digite o número de título do eleitor: ";
    std::cin >> numeroTitulo;
    
    bool eleitorEncontrado = false;
    for (const auto& eleitor : eleitores) {
        if (eleitor.titulo == numeroTitulo) {
            eleitorEncontrado = true;
            
            if (verificarAptidaoEleitor(18)) {
                std::cout << "Os candidatos disponíveis são:" << std::endl;
                listarCandidatos(candidatos);
                
                int numeroCandidato;
                std::cout << "Digite o número do candidato escolhido: ";
                std::cin >> numeroCandidato;
                
                bool candidatoEncontrado = false;
                for (const auto& candidato : candidatos) {
                    if (candidato.numero == numeroCandidato) {
                        candidatoEncontrado = true;
                        
                        Voto voto;
                        voto.numeroCandidato = numeroCandidato;
                        votos.push_back(voto);
                        
                        std::cout << "Voto registrado com sucesso!" << std::endl;
                        break;
                    }
                }
                
                if (!candidatoEncontrado) {
                    std::cout << "Candidato não encontrado." << std::endl;
                }
            } else {
                std::cout << "Eleitor não está apto para votar." << std::endl;
            }
            
            break;
        }
    }
    
    if (!eleitorEncontrado) {
        std::cout << "Eleitor não encontrado." << std::endl;
    }
}

void gerarRelatorios(const std::vector<Candidato>& candidatos, const std::vector<Voto>& votos, const std::vector<Eleitor>& eleitores) {
    std::ofstream arquivo("relatorio.txt");
    arquivo << "Relatório de votos:" << std::endl;
    
    for (const auto& candidato : candidatos) {
        int votosCandidato = 0;
        for (const auto& voto : votos) {
            if (voto.numeroCandidato == candidato.numero) {
                votosCandidato++;
            }
        }
        
        arquivo << "Candidato: " << candidato.nome << ", Número: " << candidato.numero << ", Votos: " << votosCandidato << std::endl;
    }
    
    arquivo << "Total de votos registrados: " << votos.size() << std::endl;
    arquivo << "Total de eleitores que faltaram: " << eleitores.size() - votos.size() << std::endl;
    
    arquivo.close();
}

int main() {
    std::vector<Candidato> candidatos;
    cadastrarCandidatos(candidatos);
    
    std::vector<Eleitor> eleitores;
    cadastrarEleitores(eleitores);
    
    std::vector<Voto> votos;
    
    while (true) {
        std::cout << "==== MENU ====" << std::endl;
        std::cout << "1. Listar candidatos" << std::endl;
        std::cout << "2. Registrar voto" << std::endl;
        std::cout << "3. Gerar relatórios" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "===============" << std::endl;
        
        int opcao;
        std::cout << "Digite a opção desejada: ";
        std::cin >> opcao;
        
        switch (opcao) {
            case 1:
                listarCandidatos(candidatos);
                break;
            case 2:
                registrarVoto(candidatos, eleitores, votos);
                break;
            case 3:
                gerarRelatorios(candidatos, votos, eleitores);
                break;
            case 0:
                return 0;
            default:
                std::cout << "Opção inválida." << std::endl;
                break;
        }
    }
    
    return 0;
}
