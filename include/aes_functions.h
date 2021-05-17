
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>
#include <regex>
#include "s_box.h"

/**
 * @brief Checks the program command line input. If the input is the desired returns 0
 * and the main program can proceed.
 * 
 * @param input
 * @return int 
 */

#ifndef AES_FUNCTIONS_CHECK_H__
#define AES_FUNCTIONS_CHECK_H__

int check(const std::string &input)
{

  if (input.size() != 32)
  {
    std::cout << "ERROR: la cadena debe componerse por 32 cifras hexadecimales\n";
    return 1;
  }

  /* CASES */

  return 0;
}

#endif

#ifndef AES_FUNCTIONS_PRINT_H__
#define AES_FUNCTIONS_PRINT_H__

void print_grid(const byte_grid_t &grid)
{

  for (auto row : grid)
  {
    for (auto element : row)
      std::cout << std::hex << static_cast<int>(element);
    std::cout << "\n";
  }
}

#endif

#ifndef AES_FUNCTIONS_PARSE_H__
#define AES_FUNCTIONS_PARSE_H__

byte_grid_t parse_grid(const std::string &input)
{
  byte_grid_t output = {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}};
  int c = 0;
  int r = 0;
  int pos = 0;
  for (int i = 1; i <= 16 && pos < 32; ++i)
  {

    output[c][r] = static_cast<uint8_t>(std::stoi(input.substr(pos, 2), 0, 16));
    if (((i % 4) == 0) && (i != 0))
      r++;
    c++;
    pos += 2;

    if (((i % 4) == 0))
      c = 0;
  }

  return output;
}

#endif