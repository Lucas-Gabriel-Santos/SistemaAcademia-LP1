#include "Cardio.h"
#include <iostream>
#include <iomanip>

using namespace std;

Cardio::Cardio(const string &nome, int duracao, double caloriasPorMin)
    : Exercicio(nome), duracao(duracao), caloriasPorMin(caloriasPorMin) {}

Cardio::Cardio(int id, const string &nome, int duracao, double caloriasPorMin, bool ativo)
    : Exercicio(id, nome, ativo), duracao(duracao), caloriasPorMin(caloriasPorMin) {}

void Cardio::exibirDetalhes() const {
    cout << fixed << setprecision(2);
    cout << "ID: " << getId()
         << " | Nome: " << getNome()
         << " | Tipo: Cardio"
         << " | Duracao: " << duracao << " min"
         << " | Calorias/min: " << caloriasPorMin
         << " | Status: " << (isAtivo() ? "Ativo" : "Inativo")
         << endl;
}

double Cardio::calcularTempoEstimado() const {
    return static_cast<double>(duracao);
}

double Cardio::calcularCaloriasGastas() const {
    return duracao * caloriasPorMin;
}

int Cardio::getTipo() const {   // ✅ AGORA IGUAL AO .h
    return 1;
}

int Cardio::getDuracao() const {
    return duracao;
}

double Cardio::getCaloriasPorMin() const {
    return caloriasPorMin;
}
