#ifndef HISTORICO_H
#define HISTORICO_H

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Registro {
    string dataHora; 
    int idFicha;
    string nomeFicha;
    double tempoTotal;
    double caloriasTotal;
};

class Historico {
private:
    vector<Registro> registros;

public:
    // assinatura que o Sistema.cpp espera:
    void adicionarRegistro(int idFicha, const string &nomeFicha, double tempo, double calorias);

    void exibirHistorico();
    vector<Registro> getRegistros() const;
    void carregarDeArquivo();
    void salvarEmArquivo();
};

#endif

