#ifndef FORCA_H
#define FORCA_H

#include "Exercicio.h"

class Forca : public Exercicio {
private:
    double carga;
    int series;
    int repeticoes;
    int tempoDescanso; 

public:
    Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso);
    Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso);

    void exibirDetalhes() const override;
    double calcularTempoEstimado() const override;
    double calcularCaloriasGastas() const override;
    int getTipo() const override;

    double getCarga() const;
    int getSeries() const;
    int getRepeticoes() const;
    int getTempoDescanso() const;
};

#endif