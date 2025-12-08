#include "Forca.h"
#include <iostream>
#include <iomanip>

Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome) {
    this->carga = carga;
    this->series = series;
    this->repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
    std::cout << "== Novo Força criado (ID: " << getId() << ") ==" << std::endl;
}

Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo) {
    this->carga = carga;
    this->series = series;
    this->repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

void Forca::exibirDetalhes() const {
    std::cout << "    [FORÇA] - ID: " << getId() << " | Nome: " << getNome() << std::endl;
    std::cout << "    Status: " << (isAtivo() ? "Ativo" : "Inativo") << std::endl;
    std::cout << "    Carga: " << std::fixed << std::setprecision(2) << carga << " kg" << std::endl;
    std::cout << "    Séries: " << series << " | Repetições: " << repeticoes << std::endl;
    std::cout << "    Descanso entre Séries: " << tempoDescanso << " segundos" << std::endl;
    std::cout << "    Tempo Estimado: " << std::fixed << std::setprecision(2) << calcularTempoEstimado() << " min" << std::endl;
    std::cout << "    Calorias Gastas: " << std::fixed << std::setprecision(2) << calcularCaloriasGastas() << " kcal" << std::endl;
}

double Forca::calcularTempoEstimado() const {
    double tempoExecucao = (double)series * repeticoes * 3.0;
    double tempoDescansoTotal = (double)series * tempoDescanso;
    double tempoTotalSegundos = tempoExecucao + tempoDescansoTotal;
    return tempoTotalSegundos / 60.0;
}

double Forca::calcularCaloriasGastas() const {
    return (double)series * repeticoes * carga * 0.15;
}

int Forca::getTipo() const {
    return 2;
}

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