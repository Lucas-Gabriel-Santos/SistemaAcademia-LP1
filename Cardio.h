#ifndef CARDIO_H
#define CARDIO_H

#include "Exercicio.h"

class Cardio : public Exercicio {
private:
    int duracao; 
    double caloriasPorMinuto;

public:
    Cardio(std::string nome, int duracao, double caloriasPorMinuto);

    Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto);

    void exibirDetalhes() const override;
    double calcularTempoEstimado() const override;
    double calcularCaloriasGastas() const override;
    int getTipo() const override;
    int getDuracao() const;
    double getCaloriasPorMinuto() const;
};

#endif