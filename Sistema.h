#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include "Exercicio.h"
#include "Ficha.h"
#include "Historico.h"

class Sistema {
private:
    std::vector<Exercicio*> exercicios;
    std::vector<Ficha*> fichas;
    Historico historico;

    Exercicio* buscarExercicioPorId(int id);
    Ficha* buscarFichaPorId(int id);

public:
    Sistema();
    ~Sistema();

    void carregarDados();
    void salvarDados();

    void cadastrarExercicio();
    void listarExercicios();
    void excluirExercicio(); 

    void criarFicha();
    void adicionarExercicioFicha();
    void listarFichas();

    void registrarTreino();
    void exibirHistorico();
};

#endif