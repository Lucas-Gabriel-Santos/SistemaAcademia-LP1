#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <iomanip> 
#include <algorithm> 

inline void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline void pausar() {
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

inline std::string obterDataHoraAtual() {
    std::time_t t = std::time(nullptr);
    char buffer[100];
    if (std::strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", std::localtime(&t))) {
        return std::string(buffer);
    }
    return "Data Indisponivel";
}

std::string lerString(const std::string& prompt);
int lerInt(const std::string& prompt); 
int lerInt(const std::string& prompt, int min, int max);
double lerDouble(const std::string& prompt);
bool confirmar(const std::string& prompt);


#endif