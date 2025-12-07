#include "Ficha.h"
#include <iostream>
#include <iomanip>

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome) {
    this -> proximoId++;
    std::cout << "Ficha criada com ID: " << this->id << " para " << this->nome << std::endl;
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome) : id(id), nome(nome) {
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    exercicios.clear();
    std::cout << "Ficha ID " << id << " destruída." << std::endl;
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    if(exercicio != nullptr){
        exercicios.push_back(exercicio);
        std::cout << "Exercício adicionado à ficha ID " << id << "." << std::endl;
    }
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "FICHA DE TREINO ID: " << std::setw(3) << std::setfill('0') << id << std::endl;
    std::cout << "Aluno(a): " << nome << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    if (exercicios.empty()) {
        std::cout << "Nenhum exercício cadastrado nesta ficha." << std::endl;
    } else {
        std::cout << "\n--- EXERCÍCIOS ---" << std::endl;
        for (const auto& exercicio : exercicios) {
            // Presumindo um método exibirDetalhes() na classe Exercicio
            exercicio->exibirDetalhes(); 
        }
        std::cout << "\n--- TOTAIS DA FICHA ---" << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Tempo Total (min): " << calcularTempoTotal() << std::endl;
        std::cout << "Calorias Totais (kcal): " << calcularCaloriasTotais() << std::endl;
    }
    std::cout << "--------------------------------------------------" << std::endl;
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    for(const auto& exercicio : exercicios){
        total += exercicio->calcularTempoEstimado();
    }
    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    for(const auto& exercicio : exercicios){
        total += exercicio->calcularCaloriasGastas();
    }
    return total;
}

// Getters
int Ficha::getId() const { 
    return id;
}

std::string Ficha::getNome() const { 
    return nome;
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    return exercicios; 
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
        std::cout << "Proximo ID atualizado para: " << proximoId << std::endl;
    }
}
