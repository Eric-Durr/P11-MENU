#include "binary_mult.h"

int binary(int argc, char *argv[])
{
  int flag = filter(argc, argv);
  if (flag != 0)
  {
    return flag;
  }

  if (std::string{argv[1]} == "aes")
    std::cout << "\n---- P05 AES MULT ----\n";
  else
    std::cout << "\n---- P05 SNOW 3G MULT ----\n";

  uint8_t a = std::stoi(std::string{argv[2]}.substr(2, 2), 0, 16);
  uint8_t b = std::stoi(std::string{argv[3]}.substr(2, 2), 0, 16);
  uint8_t prod;
  if (argc == 5 && std::string{argv[4]} == "trace")
    prod = std::string{argv[1]} == "aes" ? byte_mul(a, b, AES, true) : byte_mul(a, b, S3G, true);
  else
    prod = std::string{argv[1]} == "aes" ? byte_mul(a, b, AES) : byte_mul(a, b, S3G);

  std::cout << "result :";
  byte_print(prod);
  std::cout << "\n";
  return 0;
}