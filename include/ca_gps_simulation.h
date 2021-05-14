#include <iostream>
#include <regex>
#include "../include/ca_gps.h"

#define LENGTH 14

int ca_gps(void)
{
    std::cout << "--- C/A code GPS generator simulation expample ---\n"
              << "\tGenerating the first 14 bits of the code output ...\n"
              << "\tThe tap used is satellite ID: " << PRN1 + 1 << "\n"
              << "\t\ttaps " << id_taps[PRN1].first << " and " << id_taps[PRN1].second << "\n";
    std::vector<int> g1(10, 1);
    std::vector<int> g2(10, 1);
    std::cout << "\n\n--- Processing output code ---\n";

    std::vector<int> output = generate(g1, g2, id_taps[PRN1], LENGTH, true);
    std::cout << "\n\n--- Generated C/A code of " << LENGTH << " bits ---\n";
    std::cout << "\t" << to_string(output) << " \n";
    std::cout << "\n\n--- Full C/A code  for taps "
              << id_taps[PRN1].first << " and "
              << id_taps[PRN1].second << " ---\n";
    std::cout << to_string(generate(g1, g2, id_taps[PRN1])) << "\n";
    return 0;
}