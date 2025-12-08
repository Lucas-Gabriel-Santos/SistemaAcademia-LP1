#include "Cardio.h"
#include <iostream>
#include <iomanip>


Cardio::Cardio(std::string nome, int duracao, double caloriasPorMinuto) : Exercicio(nome) {
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
    std::cout << "Novo Cardio criado (ID: " << getId() << ") ==" << std::endl;
}

Cardio::Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo) {
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
}

void Cardio::exibirDetalhes() const {
    std::cout << "    [CARDIO] - ID: " << getId() << " | Nome: " << getNome() << std::endl;
    std::cout << "    Status: " << (isAtivo() ? "Ativo" : "Inativo") << std::endl;
    std::cout << "    Duração: " << duracao << " min" << std::endl;
    std::cout << "    Calorias/Minuto: " << std::fixed << std::setprecision(2) << caloriasPorMinuto << " kcal/min" << std::endl;
    std::cout << "    >> Tempo Estimado: " << std::fixed << std::setprecision(2) << calcularTempoEstimado() << " min" << std::endl;
    std::cout << "    >> Calorias Gastas: " << std::fixed << std::setprecision(2) << calcularCaloriasGastas() << " kcal" << std::endl;
}


double Cardio::calcularTempoEstimado() const {
    return (double)duracao;
}

double Cardio::calcularCaloriasGastas() const {
    return duracao * caloriasPorMinuto;
}

int Cardio::getTipo() const {
    return 1;
}

int Cardio::getDuracao() const {
    return duracao;
}

double Cardio::getCaloriasPorMinuto() const {
    return caloriasPorMinuto;
}