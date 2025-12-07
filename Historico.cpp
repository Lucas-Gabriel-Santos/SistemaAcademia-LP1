#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Adicionar registro ao histórico
void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);
    std::cout << "Registro de treino para a ficha '" 
              << registro.nomeFicha << "' (" << registro.dataHora << ") adicionado." << std::endl;
}

// Exibir histórico completo
void Historico::exibirHistorico() const {
    std::cout << "\n=================================================" << std::endl;
    std::cout << "             HISTÓRICO DE TREINO             " << std::endl;
    std::cout << "=================================================" << std::endl;

    if (registros.empty()) {
        std::cout << "Histórico sem registros." << std::endl;
        return;
    }

    // Garante que os números de ponto flutuante sejam exibidos corretamente
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& registro : registros) {
        std::cout << "Data/Hora: " << registro.dataHora << std::endl;
        std::cout << "Ficha ID:  " << registro.idFicha << std::endl;
        std::cout << "Nome Ficha: " << registro.nomeFicha << std::endl;
        std::cout << "Tempo Total: " << registro.tempoTotal << " min" << std::endl;
        std::cout << "Calorias Totais: " << registro.caloriasTotal << " kcal" << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
    }
}

// Getter de registros
const std::vector<RegistroTreino>& Historico::getRegistros() const {
    static std::vector<RegistroTreino> registros; 
    return registros;
}

// Carregar histórico do arquivo
void Historico::carregarDeArquivo() {
    std::ifstream arquivo("historico.txt");
    registros.clear(); // Limpando registros

    if (!arquivo.is_open()) {
        std::cout << "Arquivo historico.txt não encontrado. Começando com histórico vazio." << std::endl;
        return;
    }

    std::string linha;
    int linhasLidas = 0;
    
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string segmento;
        RegistroTreino novoRegistro;
        
        try {
            // 1. dataHora
            std::getline(ss, novoRegistro.dataHora, ',');

            // 2. idFicha
            std::getline(ss, segmento, ',');
            novoRegistro.idFicha = std::stoi(segmento);

            // 3. nomeFicha
            std::getline(ss, novoRegistro.nomeFicha, ',');

            // 4. tempoTotal
            std::getline(ss, segmento, ',');
            novoRegistro.tempoTotal = std::stod(segmento);

            // 5. caloriasTotal 
            std::getline(ss, segmento, '\n'); 
            novoRegistro.caloriasTotal = std::stod(segmento);
            
            registros.push_back(novoRegistro);
            linhasLidas++;

        } catch (const std::exception& e) {
            std::cerr << "Aviso: Linha mal formatada ou tipo de dado incorreto no arquivo, pulando." << std::endl;
        }
    }

    arquivo.close();
    std::cout << linhasLidas << " Registros carregados do arquivo." << std::endl;
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const {
    std::ofstream arquivo("historico.txt"); 
    
    if (!arquivo.is_open()) {
        std::cerr << "ERRO: Não foi possível abrir o arquivo historico.txt para salvar." << std::endl;
        return;
    }

    arquivo << std::fixed << std::setprecision(2); 

    for (const auto& registro : registros) {
        arquivo << registro.dataHora << ","
                << registro.idFicha << ","
                << registro.nomeFicha << "," 
                << registro.tempoTotal << ","
                << registro.caloriasTotal << "\n";
    }

    arquivo.close();
    std::cout << "Histórico salvo com sucesso em historico.txt." << std::endl;
}
