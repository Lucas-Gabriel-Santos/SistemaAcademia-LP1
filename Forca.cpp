#include "Forca.h"
#include <iostream>

// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome), carga(carga), series(series), repeticoes(repeticoes), tempoDescanso(tempoDescanso) {
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo), carga(carga), series(series), repeticoes(repeticoes), tempoDescanso(tempoDescanso) {
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    std::cout << "Tipo: Força" << std::endl;
    std::cout << "Nome: " << getNome() << std::endl;
    std::cout << "ID: " << getId() << std::endl;
    std::cout << "Status: " << (isAtivo() ? "Ativo" : "Inativo") << std::endl;
    std::cout << "Carga: " << carga << " kg" << std::endl;
    std::cout << "Séries: " << series << std::endl;
    std::cout << "Repetições: " << repeticoes << std::endl;
    std::cout << "Tempo de Descanso: " << tempoDescanso << " segundos" << std::endl;
}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const {
    double tempoSegundos = (series * repeticoes * 3) + (series * tempoDescanso);
    return tempoSegundos / 60.0; // Serve para converter para minutos
}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    return series * repeticoes * carga * 0.15;
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 2;
}

// Getters
double Forca::getCarga() const { 
    return carga;
}

int Forca::getSeries() const { 
    return series;
}

int Forca::getRepeticoes() const { 
    return repeticoes;
}

int Forca::getTempoDescanso() const { 
    return tempoDescanso;
}