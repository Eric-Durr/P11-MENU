#include <iostream>
#include <regex>
#include "../include/ca_gps.h"

void ca_gps(void)
{
    std::cout << "\n\n--- C/A code GPS generator simulation expample ---\n\n";
    std::cout << "Introduzca la ID del satélite a usar:";
    unsigned sid;
    std::cin >> sid;
    if (sid < 1 || sid >= id_taps.size())
    {
        std::cout << "ID no válido, debe ser un valor entre 1 y 32\n";
    }
    else
    {
        std::cout << "Introduzca la longitud de la secuencia a generar:";
        int length;
        std::cin >> length;
        std::cout << "\tGenerando los primeros " << length << " bits del código de salida ...\n"
                  << "\tSe usan los taps del satélite con ID: " << sid << "\n"
                  << "\t\ttaps " << id_taps[sid - 1].first << " y " << id_taps[sid - 1].second << "\n";
        std::vector<int> g1(10, 1);
        std::vector<int> g2(10, 1);
        std::cout << "\n\n--- Processing output code ---\n";

        std::vector<int> output = generate(g1, g2, id_taps[sid - 1], length, true);
        std::cout << "\n\n--- Código C/A generado de " << length << " bits ---\n";
        std::cout << "\t" << to_string(output) << " \n";
        std::cout << "\n\n--- Código completo de C/A generado para los taps  "
                  << id_taps[sid - 1].first << " y "
                  << id_taps[sid - 1].second << " ---\n";
        std::cout << to_string(generate(g1, g2, id_taps[sid - 1])) << "\n";
    }
}
