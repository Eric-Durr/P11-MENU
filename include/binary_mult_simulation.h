#include "binary_mult.h"

void binary(void)
{

  std::cout << "\n\n---- MULTIPLICACIÓN EN SNOW3G Y AES ----\n\n";

  std::cout << "Introduzca el algoritmo de cifrado para el que generar la multiplicación (aes/s3g): ";
  std::string alg;
  std::cin >> alg;
  std::cout << "Introduzca el primer valor en hexadecimal empleando el formato 0x00: ";
  std::string hex1;
  std::cin >> hex1;
  if (bcheck(hex1) != 0)
  {
    return;
  }
  std::cout << "Introduzca el segundo valor en hexadecimal empleando el formato 0x00: ";
  std::string hex2;
  std::cin >> hex2;
  if (bcheck(hex2) != 0)
  {
    return;
  }

  uint8_t a = std::stoi(hex1.substr(2, 2), 0, 16);
  uint8_t b = std::stoi(hex2.substr(2, 2), 0, 16);
  uint8_t prod;
  std::cout << "¿desea aplicar la traza? (s/n): ";
  std::string trace;
  std::cin >> trace;
  if (trace == "s")
    prod = alg == "aes" ? byte_mul(a, b, AES, true) : byte_mul(a, b, S3G, true);
  else
    prod = alg == "aes" ? byte_mul(a, b, AES) : byte_mul(a, b, S3G);

  std::cout << "Resultado de la multiplicación: ";
  byte_print(prod);
  std::cout << "\n";
}