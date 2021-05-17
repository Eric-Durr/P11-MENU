#include "aes_functions.h"
#include "aes.h"

void aes()
{
  std::cout << "\n\n--- Encriptado AES de 128 b ---\n\n";

  std::cout << "Introduzca la clave como secuencia de cifras decimales: ";
  std::string key;
  std::cin >> key;
  if (check(key) != 0)
  {
    return;
  }
  std::cout << "Introduzca el texto original como secuencia de cifras decimales: ";
  std::string ptxt;
  std::cin >> ptxt;
  if (check(ptxt) != 0)
  {
    return;
  }
  std::cout << "\n Bloque de texto plano origen: \n\n";
  print_grid(parse_grid(ptxt));

  // Cypherer object instance with plain text and key once parsed into byte_grid_object
  AES_128 my_aes_obj(parse_grid(ptxt), parse_grid(key));

  // Result grid operation by generating AES
  //// Trace is printed by passing boolean value which depends on the command line input
  byte_grid_t result;

  std::cout << "¿desea aplicar la traza? (s/n): ";
  std::string trace;
  std::cin >> trace;
  result = my_aes_obj.generate((trace == "s"));

  // Result block print in the terminal
  std::cout << "\n\n Bloque encriptado resultante: \n";
  print_grid(result);
}