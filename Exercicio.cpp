#include "Exercicio.h"

int Exercicio::proximoId = 1;

Exercicio::Exercicio(std::string nome) {
    this->nome = nome;
    this->ativo = true;
    this->id = proximoId++;
}

Exercicio::Exercicio(int id, std::string nome, bool ativo) {
    this->id = id;
    this->nome = nome;
    this->ativo = ativo;
    
    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

Exercicio::~Exercicio() {}

int Exercicio::getId() const {
    return id;
}

std::string Exercicio::getNome() const {
    return nome;
}

bool Exercicio::isAtivo() const {
    return ativo;
}

void Exercicio::desativar() {
    ativo = false;
}

void Exercicio::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}