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
int chacha_20_simulation()
{

    std::vector<std::string> in = {
        // 128b Word
        "61707865", "3320646e", "79622d32", "6b206574",
        // 256 Key
        "0e99a397", "3c53eb1b", "e2426bad", "2f312d24",
        "d9c2762b", "535e14d7", "8e1775a9", "453a68a5",
        // 32b Counter and 96b nonce
        "01000000", "b69edeac", "73ee4405", "d3fa9a8e"};

    std::vector<std::string> out;

    std::cout << "\nEstado previo al generador = " << std::endl;
    std::cout << strings_to_string(in) << "\n";
    in = reverse_set(in, BASE, OFFSET);
    out = chacha_block(out, in, ROUNDS, true);

    std::cout << "\nEstado de salida del generador = " << std::endl;
    std::cout << strings_to_string(out) << "\n";
}