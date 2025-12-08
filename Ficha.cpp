#include "Ficha.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

int Ficha::proximoId = 1;

Ficha::Ficha(std::string nome) {
    this->nome = nome;
    this->id = proximoId++; 
}

Ficha::Ficha(int id, std::string nome) {
    this->id = id;
    this->nome = nome;
  
    if (id >= proximoId) {
        proximoId = id + 1;
    }
}


Ficha::~Ficha() {
    exercicios.clear(); 
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    if (exercicio != nullptr) {
        exercicios.push_back(exercicio);
    }
}

void Ficha::exibirFicha() const {
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "FICHA ID: " << id << " | Nome: " << nome << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    
    if (exercicios.empty()) {
        std::cout << "Nenhum exercício cadastrado na ficha." << std::endl;
    } else {
        std::cout << "EXERCÍCIOS ATIVOS:" << std::endl;
        for (size_t i = 0; i < exercicios.size(); ++i) {
            if (exercicios[i]->isAtivo()) {
                std::cout << "  " << i + 1 << ". ";
                exercicios[i]->exibirDetalhes(); 
            }
        }
    }

    std::cout << "\nRESUMO TOTAL DA FICHA (Apenas exercícios Ativos):" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Tempo Total Estimado: " << calcularTempoTotal() << " minutos" << std::endl;
    std::cout << "Calorias Totais Estimadas: " << calcularCaloriasTotais() << " kcal" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    for (const auto& exec : exercicios) {
        if (exec->isAtivo()) {
             total += exec->calcularTempoEstimado();
        }
    }
    return total;
}

double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    for (const auto& exec : exercicios) {
        if (exec->isAtivo()) {
            total += exec->calcularCaloriasGastas();
        }
    }
    return total;
}

int Ficha::getId() const { 
    return id; 
}

std::string Ficha::getNome() const { 
    return nome; 
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    return exercicios; 
}

void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}