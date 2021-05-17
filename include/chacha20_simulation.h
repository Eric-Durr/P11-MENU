/**
 * 
 * Author: Eric Dürr Sierra | eric.durr.20@ull.edu.es
 * 
 * Created: 01/03/2021
 * Modified: 01/03/2021
 * 
 * 
 * 
 * 
 */

#include <iostream>
#include <regex>
#include "chacha20.h"
void chacha20()
{

    std::cout << "\n\n--CIFRADO EN FLUJO RC4--\n\n";
    std::cout << "Introduzca el texto original de 128 bits en forma de 4 palabras en hexadecimal:\n";
    std::vector<std::string> word;
    for (int i = 0; i < 4; ++i)
    {
        std::string aux;
        std::cout << "Cifra hexadecimal " << i + 1 << ": ";
        std::cin >> aux;
        word.push_back(aux);
    }
    std::cout << "Introduzca la clave de 256 bits en forma de 8 palabras en hexadecimal:\n";
    std::vector<std::string> key;
    for (int i = 0; i < 8; ++i)
    {
        std::string aux;
        std::cout << "Cifra hexadecimal " << i + 1 << ": ";
        std::cin >> aux;
        key.push_back(aux);
    }
    std::cout << "Introduzca los 32 bits de contador:";
    std::string ctr;
    std::cout << "Cifra hexadecimal: ";
    std::cin >> ctr;

    std::cout << "Introduzca el nonce  de 96 bits en forma de 3 palabras en hexadecimal:\n";
    std::vector<std::string> nonce;
    for (int i = 0; i < 3; ++i)
    {
        std::string aux;
        std::cout << "Cifra hexadecimal " << i + 1 << ": ";
        std::cin >> aux;
        nonce.push_back(aux);
    }
    std::vector<std::string> in = {
        // 128b Word
        word[0], word[1], word[2], word[3],
        // 256 Key
        key[0], key[1], key[2], key[3],
        key[4], key[5], key[6], key[7],
        // 32b Counter and 96b nonce
        ctr, nonce[0], nonce[1], nonce[2]};

    std::vector<std::string> out;

    std::cout << "\nEstado previo al generador = " << std::endl;
    std::cout << strings_to_string(in) << "\n";
    in = reverse_set(in, BASE, OFFSET);
    out = chacha_block(out, in, ROUNDS, true);

    std::cout << "\nEstado de salida del generador = " << std::endl;
    std::cout << strings_to_string(out) << "\n";
}