#ifndef FORCA_H
#define FORCA_H

#include "Exercicio.h"
#include <string>

class Forca : public Exercicio {
private:
    double carga;
    int series;
    int repeticoes;
    int descanso; // em segundos

public:
    // Construtor para novo cadastro
    Forca(const std::string &nome, double carga, int series, int repeticoes, int descanso);

    // Construtor para leitura do arquivo
    Forca(int id, const std::string &nome, double carga, int series, int repeticoes, int descanso, bool ativo);

    ~Forca() override = default;

    // ✅ TODOS COM CONST (IGUAL AO EXERCICIO.H)
    void exibirDetalhes() const override;
    double calcularTempoEstimado() const override;
    double calcularCaloriasGastas() const override;
    int getTipo() const override;

    // ✅ GETTERS QUE O SISTEMA.CPP USA
    double getCarga() const;
    int getSeries() const;
    int getRepeticoes() const;
    int getDescanso() const;   // ✅ AGORA EXISTE DE VERDADE
};

#endif
