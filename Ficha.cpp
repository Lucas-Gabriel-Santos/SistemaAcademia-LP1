#include "Forca.h"
#include <iostream>
#include <iomanip>

using namespace std;

Forca::Forca(const string &nome, double carga, int series, int repeticoes, int descanso)
    : Exercicio(nome), carga(carga), series(series), repeticoes(repeticoes), descanso(descanso) {}

Forca::Forca(int id, const string &nome, double carga, int series, int repeticoes, int descanso, bool ativo)
    : Exercicio(id, nome, ativo), carga(carga), series(series), repeticoes(repeticoes), descanso(descanso) {}

void Forca::exibirDetalhes() const {
    cout << fixed << setprecision(2);
    cout << "ID: " << getId()
         << " | Nome: " << getNome()
         << " | Tipo: Forca"
         << " | Carga: " << carga << " kg"
         << " | Series: " << series
         << " | Repeticoes: " << repeticoes
         << " | Descanso: " << descanso << "s"
         << " | Status: " << (isAtivo() ? "Ativo" : "Inativo")
         << endl;
}

double Forca::calcularTempoEstimado() const {
    double segundos = (static_cast<double>(series) * repeticoes * 3.0)
                     + (static_cast<double>(series) * descanso);
    return segundos / 60.0;
}

double Forca::calcularCaloriasGastas() const {
    return static_cast<double>(series) * repeticoes * carga * 0.15;
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

int Forca::getDescanso() const {
    return descanso;
}
