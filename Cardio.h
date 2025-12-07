#ifndef CARDIO_H
#define CARDIO_H

#include "Exercicio.h"
#include <string>

class Cardio : public Exercicio {
private:
    int duracao;              
    double caloriasPorMin;    

public:
    // Novo cadastro
    Cardio(const std::string &nome, int duracao, double caloriasPorMin);

    // Leitura de arquivo
    Cardio(int id, const std::string &nome, int duracao, double caloriasPorMin, bool ativo);

    ~Cardio() override = default;

    // ✅ AGORA COM CONST (IGUAL AO EXERCICIO.H)
    void exibirDetalhes() const override;
    double calcularTempoEstimado() const override;
    double calcularCaloriasGastas() const override;
    int getTipo() const override;

    // Getters usados no Sistema
    int getDuracao() const;
    double getCaloriasPorMin() const;
};

#endif

