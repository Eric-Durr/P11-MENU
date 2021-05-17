#include "../include/aes_functions.h"
#include "../include/aes.h"

byte_grid_t CBC_XOR(const byte_grid_t &plaintext, const byte_grid_t &element, const bool &trace = false);

void cbc(void)
{

  std::cout << "\n--- Encriptado CBC con AES de 128 b ---\n";

  std::cout << "Introduzca el vector de inicialización como secuencia de cifras decimales: ";
  std::string str_iv;
  std::cin >> str_iv;
  byte_grid_t iv = parse_grid(str_iv);
  std::cout << "Introduzca la clave como secuencia de cifras decimales: ";
  std::string str_key;
  std::cin >> str_key;
  byte_grid_t key = parse_grid(str_key);
  std::cout
      << "\n Bloques de texto plano origen: \n\n";
  std::vector<byte_grid_t> ptexts;
  while (1)
  {
    std::cout << "Introduzca el texto original como secuencia de cifras decimales: ";
    std::string ptxt;
    std::cin >> ptxt;
    ptexts.push_back(parse_grid(ptxt));

    std::cout << "¿Quiere añadir otro texto plano? (s/n)";
    std::string opt;
    std::cin >> opt;
    if (opt == "n")
      break;
  }

  std::cout << "¿Desea mostrar la traza del proceso? (s/n): ";
  std::string trace;
  std::cin >> trace;
  //// --- CBC proccess ---

  byte_grid_t input;
  std::vector<byte_grid_t> ciph_text;

  // XOR between plaintext and corresponding element
  for (unsigned i = 0; i < ptexts.size(); ++i)
  {
    if (i == 0) // First round with initialization vector (IV)
    {
      input = CBC_XOR(ptexts[i], iv, trace == "s");
    }
    if (i > 0) // The rest of the rounds AES input block contains the previous Ciphertext
    {
      input = CBC_XOR(ptexts[i], ciph_text.back(), trace == "s");
    }

    AES_128 my_aes_obj(input, key);
    //// Trace is printed by passing boolean value which depends on the command line input
    ciph_text.push_back(my_aes_obj.generate(trace == "s"));
  }
  // Result grid operation by generating AES

  // Result block print in the terminal
  std::cout << "\n\nResultados del cifrado CBC:\n";
  for (unsigned i = 0; i < ciph_text.size(); ++i)
  {
    std::cout << "Bloque " << i + 1 << " de tetxo cifrado:\n";
    print_grid(ciph_text[i]);
  }
}

byte_grid_t CBC_XOR(const byte_grid_t &plaintext, const byte_grid_t &element, const bool &trace)
{
  byte_grid_t xored = {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}};
  for (unsigned i = 0; i < plaintext.size(); ++i)
    for (unsigned j = 0; j < plaintext.size(); ++j)
      xored[j][i] = plaintext[j][i] ^ element[j][i];
  if (trace)
  {
    std::cout << "\n\nXOR entre los bloques\n\n";
    print_grid(plaintext);
    std::cout << "\ny\n\n";
    print_grid(element);
    std::cout << "\nresulta en:\n\n";
    print_grid(xored);
    std::cout << "\n\n\n";
  }
  return xored;
}
