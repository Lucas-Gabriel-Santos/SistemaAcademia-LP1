#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h" 
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <algorithm>

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();
    for (Exercicio* e : exercicios) delete e;
    exercicios.clear();
    for (Ficha* f : fichas) delete f;
    fichas.clear();
}

void Sistema::carregarDados() {
    std::ifstream arqExercicio("exercicios.txt");
    if (arqExercicio.is_open()) {
        std::string linha;
        int maiorId = 0;
        while (std::getline(arqExercicio, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string campo;
            
            int tipo, id, duracao, series, repeticoes, tempoDescanso;
            std::string nome;
            bool ativo;
            double caloriasPorMinuto, carga;

            try {
                std::getline(ss, campo, ';'); tipo = std::stoi(campo);
                std::getline(ss, campo, ';'); id = std::stoi(campo);
                std::getline(ss, nome, ';');

                if (id > maiorId) maiorId = id;

                if (tipo == 1) { 
                    std::getline(ss, campo, ';'); duracao = std::stoi(campo);
                    std::getline(ss, campo, ';'); caloriasPorMinuto = std::stod(campo);
                    
                    std::getline(ss, campo, ';'); ativo = (campo == "1");

                    exercicios.push_back(new Cardio(id, nome, ativo, duracao, caloriasPorMinuto));

                } else if (tipo == 2) { // Força
                    std::getline(ss, campo, ';'); carga = std::stod(campo);
                    std::getline(ss, campo, ';'); series = std::stoi(campo);
                    std::getline(ss, campo, ';'); repeticoes = std::stoi(campo);
                    std::getline(ss, campo, ';'); tempoDescanso = std::stoi(campo);
                    
                    std::getline(ss, campo, ';'); ativo = (campo == "1");

                    exercicios.push_back(new Forca(id, nome, ativo, carga, series, repeticoes, tempoDescanso));
                }
            } catch (const std::exception& e) {
                std::cerr << "Erro ao ler a linha: " << linha << std::endl;
            }
        }
        arqExercicio.close();
        Exercicio::atualizarProximoId(maiorId);
    }

    std::ifstream arqFicha("fichas.txt");
    if (arqFicha.is_open()) {
        std::string linha;
        int maiorId = 0;
        while (std::getline(arqFicha, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string campo;
            
            int idFicha, totalExercicios;
            std::string nomeFicha;

            try {
                std::getline(ss, campo, ';'); idFicha = std::stoi(campo);
                std::getline(ss, nomeFicha, ';');
                std::getline(ss, campo, ';'); totalExercicios = std::stoi(campo);

                if (idFicha > maiorId) maiorId = idFicha;
                
                Ficha* novaFicha = new Ficha(idFicha, nomeFicha);
                
                for (int i = 0; i < totalExercicios; ++i) {
                    std::getline(ss, campo, ';'); 
                    int idExercicio = std::stoi(campo);
                    
                    Exercicio* ex = buscarExercicioPorId(idExercicio);
                    if (ex) {
                        novaFicha->adicionarExercicio(ex);
                    }
                }
                fichas.push_back(novaFicha);

            } catch (...) {}
        }
        arqFicha.close();
        Ficha::atualizarProximoId(maiorId);
    }
    
    historico.carregarDeArquivo();
}

void Sistema::salvarDados() {
    std::ofstream arqExercicio("exercicios.txt");
    if (arqExercicio.is_open()) {
        for (const auto& e : exercicios) {

            arqExercicio << e->getTipo() << ";"
                         << e->getId() << ";"
                         << e->getNome() << ";";

            if (e->getTipo() == 1) { // Cardio
                Cardio* c = dynamic_cast<Cardio*>(e);
                if (c) {
                    arqExercicio << c->getDuracao() << ";"
                                 << c->getCaloriasPorMinuto() << ";";
                }
            } else if (e->getTipo() == 2) { // Força
                Forca* f = dynamic_cast<Forca*>(e);
                if (f) {
                    arqExercicio << f->getCarga() << ";"
                                 << f->getSeries() << ";"
                                 << f->getRepeticoes() << ";"
                                 << f->getTempoDescanso() << ";";
                }
            }
            arqExercicio << (e->isAtivo() ? "1" : "0") << "\n";
        }
        arqExercicio.close();
    }

    std::ofstream arqFicha("fichas.txt");
    if (arqFicha.is_open()) {
        for (const auto& f : fichas) {
            arqFicha << f->getId() << ";"
                     << f->getNome() << ";"
                     << f->getExercicios().size(); 
            
            for (const auto& e : f->getExercicios()) {
                arqFicha << ";" << e->getId();
            }
            arqFicha << "\n";
        }
        arqFicha.close();
    }
    
    historico.salvarEmArquivo();
}

Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (auto* e : exercicios) {
        if (e->getId() == id) return e;
    }
    return nullptr;
}

Ficha* Sistema::buscarFichaPorId(int id) {
    for (auto* f : fichas) {
        if (f->getId() == id) return f;
    }
    return nullptr;
}

void Sistema::cadastrarExercicio() {
    limparTela();
    std::cout << "=== CADASTRO DE EXERCICIO ===" << std::endl;
    
    int tipo = lerInt("Tipo (1-Cardio, 2-Forca): ", 1, 2);
    std::string nome = lerString("Nome: ");

    Exercicio* novo = nullptr;

    if (tipo == 1) {
        int dur = lerInt("Duracao (min): ", 1, 999);
        double cal = lerDouble("Calorias/min: ");
        novo = new Cardio(nome, dur, cal);
    } else {
        double carga = lerDouble("Carga (kg): ");
        int series = lerInt("Series: ", 1, 999);
        int reps = lerInt("Repeticoes: ", 1, 999);
        int descanso = lerInt("Descanso (seg): ", 0, 999);
        novo = new Forca(nome, carga, series, reps, descanso);
    }

    if (novo) {
        exercicios.push_back(novo);
        std::cout << "Exercicio cadastrado com ID: " << novo->getId() << std::endl;
    }
    pausar();
}

void Sistema::listarExercicios() {
    limparTela();
    std::cout << "=== EXERCICIOS ATIVOS ===" << std::endl;
    bool achou = false;
    for (const auto& e : exercicios) {
        if (e->isAtivo()) {
            e->exibirDetalhes();
            std::cout << "-------------------------" << std::endl;
            achou = true;
        }
    }
    if (!achou) std::cout << "Nenhum exercicio ativo." << std::endl;
    pausar();
}

void Sistema::excluirExercicio() {
    listarExercicios();
    int id = lerInt("ID para excluir (0 para voltar): ");
    if (id == 0) return;

    Exercicio* e = buscarExercicioPorId(id);
    if (e) {
        e->desativar();
        std::cout << "Exercicio desativado." << std::endl;
    } else {
        std::cout << "Exercicio nao encontrado." << std::endl;
    }
    pausar();
}

void Sistema::criarFicha() {
    limparTela();
    std::string nome = lerString("Nome da Ficha: ");
    Ficha* nova = new Ficha(nome);
    fichas.push_back(nova);
    std::cout << "Ficha criada com ID: " << nova->getId() << std::endl;
    pausar();
}

void Sistema::adicionarExercicioFicha() {
    listarFichas();
    if (fichas.empty()) return;

    int idFicha = lerInt("ID da Ficha: ");
    Ficha* f = buscarFichaPorId(idFicha);
    if (!f) {
        std::cout << "Ficha nao encontrada." << std::endl;
        pausar();
        return;
    }

    std::cout << "\n=== EXERCICIOS DISPONIVEIS ===" << std::endl;
    bool achouEx = false;
    for (const auto& e : exercicios) {
        if (e->isAtivo()) {
            std::cout << "ID: " << e->getId() << " - " << e->getNome() << std::endl;
            achouEx = true;
        }
    }
    if (!achouEx) {
        std::cout << "Nenhum exercicio disponivel para adicionar." << std::endl;
        pausar();
        return;
    }

    int idEx = lerInt("ID do Exercicio: ");
    Exercicio* e = buscarExercicioPorId(idEx);
    
    if (e && e->isAtivo()) {
        f->adicionarExercicio(e);
        std::cout << "Exercicio adicionado!" << std::endl;
    } else {
        std::cout << "Exercicio inválido ou inativo." << std::endl;
    }
    pausar();
}

void Sistema::listarFichas() {
    limparTela();
    std::cout << "--- FICHAS ---" << std::endl;
    if (fichas.empty()) std::cout << "Nenhuma ficha cadastrada." << std::endl;
    
    for (const auto& f : fichas) {
        f->exibirFicha();
    }
    pausar();
}

void Sistema::registrarTreino() {
    listarFichas();
    if (fichas.empty()) return;

    int id = lerInt("ID da Ficha realizada: ");
    Ficha* f = buscarFichaPorId(id);
    if (f) {
        RegistroTreino reg;
        reg.dataHora = obterDataHoraAtual();
        reg.idFicha = f->getId();
        reg.nomeFicha = f->getNome();
        reg.tempoTotal = f->calcularTempoTotal();
        reg.caloriasTotal = f->calcularCaloriasTotais();
        
        historico.adicionarRegistro(reg);
    } else {
        std::cout << "Ficha nao encontrada." << std::endl;
    }
    pausar();
}

void Sistema::exibirHistorico() {
    limparTela();
    historico.exibirHistorico();
    pausar();
}