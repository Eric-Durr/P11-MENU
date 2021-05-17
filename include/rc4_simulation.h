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
#include <vector>
#include <sstream>
#include "rc4_functions.h"

template <char T>
class SplitWith : public std::string
{
    friend std::istream &operator>>(std::istream &is, SplitWith<T> &output)
    {
        std::getline(is, output, T);
        return is;
    }
};

std::vector<int> extract_csv_values(std::string readed)
{
    std::istringstream iss(readed);

    std::vector<std::string> svalues((std::istream_iterator<SplitWith<','>>(iss)),
                                     std::istream_iterator<SplitWith<','>>());

    std::vector<int> values;
    for (auto element : svalues)
        values.push_back(std::stoi(std::string{element}));
    for (auto el : values)
        std::cout << el << " ";
    std::cout << "\n";
    return values;
}

void rc4(void)
{

    std::vector<int> vseed, vptext, s, vctext;

    std::cout << "\n\n--CIFRADO EN FLUJO RC4--\n\n";
    std::cout << "Introducir semilla con los valores separados por coma: ";
    std::string seed; // seed for key
    std::cin >> seed;
    vseed = extract_csv_values(seed);
    std::cout << "Introducir el texto original con los valores separados por coma: ";
    std::string ptext; // plain text values
    std::cin >> ptext;
    vptext = extract_csv_values(ptext);
    std::cout << "\nInicialización:\n";
    initializeRC4(s, vseed);

    std::cout << "\nGeneración de secuencia cifrante y texto cifrado:\n";

    vctext = generateCipheringSecuence(vptext, s);
}
