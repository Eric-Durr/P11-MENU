
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>

const uint8_t s3g_poly = 0xA9;
const uint8_t aes_poly = 0x1B;

enum algortihm
{
  AES,
  S3G
};

/**
 * @brief Checks the program command line input. If the input is the desired returns 0
 * and the main program can proceed.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int filter(int argc, char *argv[])
{

  if (argc < 4)
  {
    std::cout << "ERROR: wrong execution input\n";
    std::cout << "USAGE: " << argv[0] << " <aes/s3g> <num1> <num2> [trace]\n";
    return 1;
  }

  if (std::string{argv[1]} != "aes" &&
      std::string{argv[1]} != "s3g")
  {
    std::cout << "ERROR: unknown algorithm byte input - "
                 "introduced "
              << argv[1] << "\n";
    std::cout << "USAGE: " << argv[0] << " <aes/s3g> <num1> <num2> [trace]\n";
    return 2;
  }

  if (std::string{argv[2]}.substr(0, 2) != "0x")
  {
    std::cout << "ERROR: expected hex format in numbers - "
                 "introduced "
              << argv[2] << " - expected 0xXX\n";
    std::cout << "USAGE: " << argv[0] << " <aes/s3g> <num1> <num2> [trace]\n";
    return 3;
  }

  if (std::string{argv[3]}.substr(0, 2) != "0x")
  {
    std::cout << "ERROR: expected hex format in numbers - "
                 "introduced "
              << argv[3] << " - expected 0xYY\n";
    std::cout << "USAGE: " << argv[0] << " <aes/s3g> <num1> <num2> [trace]\n";
    return 4;
  }

  if (std::string{argv[2]}.size() != 4)
  {
    std::cout << "ERROR: expected hex number of 8 bits - "
                 "introduced "
              << argv[2] << " - expected 0xXX\n";
    std::cout << "USAGE: " << argv[0] << " <aes/s3g> <num1> <num2> [trace]\n";
    return 5;
  }

  if (std::string{argv[3]}.size() != 4)
  {
    std::cout << "ERROR: expected hex number of 8 bits - "
                 "introduced "
              << argv[3] << " - expected 0xYY\n";
    std::cout << "USAGE: " << argv[0] << " <aes/s3g> <num1> <num2> [trace]\n";
    return 6;
  }

  return 0;
}

/**
 * @brief Adds two uint8_t values which expresses a byte from the LFSR, the result is returned
 * 
 * @param a 
 * @param b 
 * @return uint8_t 
 */

uint8_t byte_add(const uint8_t &a, const uint8_t &b)
{
  return a ^ b;
}

/**
 * @brief Prints the bits in the command line from the uint8_t byte value.
 * The number to print is given as argument.
 * 
 * @param a 
 */

void byte_print(uint8_t a)
{
  int i = 8;
  while (i--)
    putchar((a >> i & 1) + '0');
}

/**
 * @brief byte multiplication function. Two bytes and the algorithm must be provided as arguments.
 * If desired the trace can be shown by giving true as last argument
 * 
 * @param a 
 * @param b 
 * @param option 
 * @param snitch 
 * @return uint8_t 
 * 
 * **usage**
 * ```cpp
 * uint8_t my_aes_result byte_mul(0x57, 0x83, aes) //0b11000001
 * uint8_t my_s3g_result byte_mul(0x57, 0x83, s3g) //0b10010110
 * ```
 * 
 * **Algorithm explained:**
 *  mult of A and B
 * 
 *  1. product result byte initialisation
 * 
 *   is the least significant bit of B equal to 1 ?
 * 
 *     yes -> product byte = A
 *     no  -> product byte = 0
 * 
 *  for 7 times
 *   
 *  2. is the most significant bit of A equal to 1 ?
 * 
 *      yes -> A left shift 1 time and bitwise XOR with algorithm byte
 *      (algorithm byte is chosen previously)
 * 
 *      no -> A left shift 1 time
 * 
 *  3. is the nth bit of B a 1 (distributive)
 *
 *      yes -> bitwise XOR between the product result and A
 */

uint8_t byte_mul(uint8_t &a, uint8_t &b, algortihm option, bool snitch = false)
{

  uint8_t prod;

  (b & (1 << 0)) == 1 ? prod = a : prod = 0x00;

  int k = 0;
  if (snitch)
  {
    std::cout << "STEP " << k << ": \n";
    byte_print(a);
    std::cout << "\n";
  }
  for (int i = 1; i < 8; i++)
  {
    if (((a & (1 << 7)) >> 7) == 0x01)
    {
      a <<= 1;
      if (snitch)
      {
        std::cout << "STEP " << ++k << ": \n";
        byte_print(a);
        std::cout << " + ";
      }
      switch (option)
      {
      case AES:
        a = byte_add(a, aes_poly);
        if (snitch)
        {
          std::cout << " = ";
          byte_print(aes_poly);
          byte_print(a);
          std::cout << "\n";
        }
        break;
      case S3G:
        a = byte_add(a, s3g_poly);
        if (snitch)
        {
          byte_print(s3g_poly);
          std::cout << " = ";
          byte_print(a);
          std::cout << "\n";
        }
        break;
      default:
        break;
      }
    }
    else
    {
      a <<= 1;
      if (snitch)
      {
        std::cout << "STEP " << ++k << ": \n";
        byte_print(a);
        std::cout << "\n";
      }
    }
    if (((b & (1 << i)) >> i) == 0x01)
    {
      prod = byte_add(prod, a);
    }
  }
  return prod;
}

/*!
 * @brief Compact GF(2^8) multiplication function for AES
 *
 * @returns the 8 bits of the resultant multiplication between the given numbers.
 * */
uint8_t gf2n_multiply(uint8_t a, uint8_t b)
{
  uint8_t p = 0;
  uint8_t carry;
  int i;
  for (i = 0; i < 8; i++)
  {
    if (b & 1)
      p ^= a;
    carry = a & 0x80;
    a = a << 1;
    if (carry)
      a ^= 0x1b;
    b = b >> 1;
  }
  return p;
}
