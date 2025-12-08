#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);
    std::cout << "Registro de treino adicionado: " << registro.nomeFicha << " em " << registro.dataHora << std::endl;
}

void Historico::exibirHistorico() const {
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "HISTÓRICO DE TREINOS (" << registros.size() << " Registros)" << std::endl;
    
    if (registros.empty()) {
        std::cout << "Nenhum Registro Cncontrado." << std::endl;
    } else {
        for (const auto& reg : registros) {
            std::cout << "Data/Hora: " << reg.dataHora << std::endl;
            std::cout << "Ficha ID: " << reg.idFicha << " | Nome: " << reg.nomeFicha << std::endl;
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Tempo Total: " << reg.tempoTotal << " min | Calorias Total: " << reg.caloriasTotal << " kcal" << std::endl;
        }
    }
    std::cout << "----------------------------------------" << std::endl;
}

const std::vector<RegistroTreino>& Historico::getRegistros() const {
    return registros;
}

void Historico::carregarDeArquivo() {
    std::ifstream arquivo("historico.txt");
    if (!arquivo.is_open()) {
        std::cerr << "AVISO: Não foi possível abrir o arquivo historico.txt para leitura." << std::endl;
        return;
    }

    registros.clear(); 
    std::string linha;
    std::string campo;
    
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;
        
        RegistroTreino reg;
        std::stringstream ss(linha);
        
        try {
            std::getline(ss, reg.dataHora, ';'); 

            std::getline(ss, campo, ';'); 
            reg.idFicha = std::stoi(campo);
 
            std::getline(ss, reg.nomeFicha, ';'); 

            std::getline(ss, campo, ';');
           
            reg.tempoTotal = std::stod(campo); 
            
            std::getline(ss, campo, ';');
            reg.caloriasTotal = std::stod(campo);
            
            registros.push_back(reg);

        } catch (const std::exception& e) {
            std::cerr << "Erro ao processar linha do histórico: " << linha << " (" << e.what() << ")" << std::endl;
        }
    }
    arquivo.close();
    std::cout << registros.size() << "Registros carregados do historico.txt." << std::endl;
}

void Historico::salvarEmArquivo() const {
    std::ofstream arquivo("historico.txt");
    if (!arquivo.is_open()) {
        std::cerr << "ERRO: Não foi possível abrir o arquivo historico.txt para escrita." << std::endl;
        return;
    }

    for (const auto& reg : registros) {
        arquivo << std::fixed << std::setprecision(2)
                << reg.dataHora << ";"
                << reg.idFicha << ";"
                << reg.nomeFicha << ";"
                << reg.tempoTotal << ";"
                << reg.caloriasTotal << "\n";
    }

    arquivo.close();
    std::cout << registros.size() << "Registros salvos no historico.txt." << std::endl;
}