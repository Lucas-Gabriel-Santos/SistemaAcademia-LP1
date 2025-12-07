#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Historico.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();

    for (auto e : exercicios)
        delete e;

    for (auto f : fichas)
        delete f;
}

// ================= CARREGAR DADOS =================

void Sistema::carregarDados() {
    ifstream arq("exercicios.txt");
    string linha;

    while (getline(arq, linha)) {
        stringstream ss(linha);
        vector<string> dados;
        string token;

        while (getline(ss, token, ';'))
            dados.push_back(token);

        int tipo = stoi(dados[0]);
        int id = stoi(dados[1]);
        string nome = dados[2];

        if (tipo == 1) { // Cardio
            int duracao = stoi(dados[3]);
            double calMin = stod(dados[4]);
            bool status = stoi(dados[5]);

            Cardio* c = new Cardio(id, nome, duracao, calMin, status);
            exercicios.push_back(c);

            Exercicio::atualizarProximoId(id);
        }
        else if (tipo == 2) { // Forca
            double carga = stod(dados[3]);
            int series = stoi(dados[4]);
            int reps = stoi(dados[5]);
            int descanso = stoi(dados[6]);
            bool status = stoi(dados[7]);

            Forca* f = new Forca(id, nome, carga, series, reps, descanso, status);
            exercicios.push_back(f);

            Exercicio::atualizarProximoId(id);
        }
    }

    arq.close();

    ifstream arqF("fichas.txt");

    while (getline(arqF, linha)) {
        stringstream ss(linha);
        vector<string> dados;
        string token;

        while (getline(ss, token, ';'))
            dados.push_back(token);

        int idFicha = stoi(dados[0]);
        string nomeFicha = dados[1];
        int total = stoi(dados[2]);

        Ficha* ficha = new Ficha(idFicha, nomeFicha);

        for (int i = 0; i < total; i++) {
            int idEx = stoi(dados[3 + i]);
            Exercicio* e = buscarExercicioPorId(idEx);
            if (e != nullptr)
                ficha->adicionarExercicio(e);
        }

        fichas.push_back(ficha);
        Ficha::atualizarProximoId(idFicha);
    }

    arqF.close();

    historico.carregarDeArquivo();
}

// ================= SALVAR DADOS =================

void Sistema::salvarDados() {
    ofstream arq("exercicios.txt");

    for (auto e : exercicios) {
        if (dynamic_cast<Cardio*>(e)) {
            Cardio* c = dynamic_cast<Cardio*>(e);
            arq << "1;" << c->getId() << ";" << c->getNome() << ";"
                << c->getDuracao() << ";" << c->getCaloriasPorMin()
                << ";" << c->isAtivo() << endl;
        }
        else if (dynamic_cast<Forca*>(e)) {
            Forca* f = dynamic_cast<Forca*>(e);
            arq << "2;" << f->getId() << ";" << f->getNome() << ";"
                << f->getCarga() << ";" << f->getSeries() << ";"
                << f->getRepeticoes() << ";" << f->getDescanso()
                << ";" << f->isAtivo() << endl;
        }
    }

    arq.close();

    ofstream arqF("fichas.txt");

    for (auto f : fichas)
        f->salvarEmArquivo(arqF);

    arqF.close();

    historico.salvarEmArquivo();
}

// ================= BUSCAS =================

Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (auto e : exercicios)
        if (e->getId() == id)
            return e;

    return nullptr;
}

Ficha* Sistema::buscarFichaPorId(int id) {
    for (auto f : fichas)
        if (f->getId() == id)
            return f;

    return nullptr;
}

// ================= CADASTRO =================

void Sistema::cadastrarExercicio() {
    int tipo;
    cout << "1 - Cardio | 2 - Forca: ";
    cin >> tipo;

    string nome;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);

    if (tipo == 1) {
        int duracao;
        double calMin;

        cout << "Duracao: ";
        cin >> duracao;

        cout << "Calorias por minuto: ";
        cin >> calMin;

        exercicios.push_back(new Cardio(nome, duracao, calMin));
    }
    else {
        double carga;
        int series, reps, descanso;

        cout << "Carga: ";
        cin >> carga;

        cout << "Series: ";
        cin >> series;

        cout << "Repeticoes: ";
        cin >> reps;

        cout << "Descanso: ";
        cin >> descanso;

        exercicios.push_back(new Forca(nome, carga, series, reps, descanso));
    }

    cout << "Exercicio cadastrado!\n";
}

// ================= LISTAGENS =================

void Sistema::listarExercicios() {
    for (auto e : exercicios)
        if (e->isAtivo())
            e->exibirDetalhes();
}

void Sistema::excluirExercicio() {
    int id;
    cout << "ID: ";
    cin >> id;

    Exercicio* e = buscarExercicioPorId(id);

    if (e != nullptr) {
        e->desativar();
        cout << "Exercicio desativado!\n";
    }
    else {
        cout << "Nao encontrado.\n";
    }
}

// ================= FICHAS =================

void Sistema::criarFicha() {
    string nome;

    cout << "Nome da ficha: ";
    cin.ignore();
    getline(cin, nome);

    Ficha* f = new Ficha(nome);
    fichas.push_back(f);

    cout << "Ficha criada!\n";
}

void Sistema::adicionarExercicioFicha() {
    int idFicha, idEx;

    cout << "ID da ficha: ";
    cin >> idFicha;

    cout << "ID do exercicio: ";
    cin >> idEx;

    Ficha* f = buscarFichaPorId(idFicha);
    Exercicio* e = buscarExercicioPorId(idEx);

    if (f && e) {
        f->adicionarExercicio(e);
        cout << "Exercicio adicionado!\n";
    }
    else {
        cout << "Erro ao adicionar.\n";
    }
}

void Sistema::listarFichas() {
    for (auto f : fichas)
        f->exibirFicha();
}

// ================= HISTORICO =================

void Sistema::registrarTreino() {
    int idFicha;

    cout << "ID da ficha: ";
    cin >> idFicha;

    Ficha* f = buscarFichaPorId(idFicha);

    if (!f) {
        cout << "Ficha nao encontrada!\n";
        return;
    }

    double tempo = f->calcularTempoTotal();
    double calorias = f->calcularCaloriasTotais();

    historico.adicionarRegistro(f->getId(), f->getNome(), tempo, calorias);

    cout << "Treino registrado!\n";
}

// void Sistema::exibirHistorico() {
//     Historico::exibirHistorico();
// }
