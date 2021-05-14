/**
 * 
 * Author: Eric Dürr Sierra | eric.durr.20@ull.edu.es
 * 
 * Created: 01/03/2021
 * Modified: 01/03/2021
 * 
 * 
 */

#include <iostream>
#include <regex>
#include "../include/rc4_functions.h"

/* Text formart check function: throug a regular expresion validates the message to cipher */
bool text_check(const std::string &input_str);

int main(void)
{
    std::string message, keyword;
    int op;

    std::string temp_key;
    bool ciphered_status = false;

    while (1)
    {
        op = 7;
        std::cout << "\n\n--MENÚ PARA EL CIFRADO DE VIGENERE--\n\n";
        std::cout << "\t0) Salir del programa\n";
        std::cout << "Introducir opción: ";
        std::cin >> op;
        std::cout << "\n\n";

        if (op == 0)
        {
            break;
        }

        switch (op)
        {
        default:
            std::cout << "Opción no contemplada para el número " << op
                      << " vuelva a intentarlo\n";
            break;
        }

        std::cout << "\n\t\tPulse enter para continuar...";
        getchar();
        getchar();
        system("clear");
    }

    return 0;
}
