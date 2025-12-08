#include "Utils.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>

std::string lerString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::getline(std::cin, input);
    return input;
}

int lerInt(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            return valor;
        }
        std::cout << "Entrada invalida. Digite um numero.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int lerInt(const std::string& prompt, int min, int max) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            if (valor >= min && valor <= max) {
                return valor;
            }
        }
        std::cout << "Entrada invalida (Min: " << min << ", Max: " << max << ").\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double lerDouble(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            return valor;
        }
        std::cout << "Entrada invalida. Digite um numero decimal.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool confirmar(const std::string& prompt) {
    std::string resposta;
    while (true) {
        std::cout << prompt << " (S/N): ";
        std::cin >> resposta;
        std::transform(resposta.begin(), resposta.end(), resposta.begin(), ::tolower);

        if (resposta == "s") return true;
        if (resposta == "n") return false;
        std::cout << "Resposta invalida.\n";
    }
}