#include "el_gamal.h"
void elgamal()
{

  std::cout << "\n\n--- CIFRADO DE INTERCAMBIO DE CLAVES - ELGAMAL ---\n\n";
  std::cout << "Introduzca el número primo p (módulo) como número entero positivo: ";
  unsigned p;
  std::cin >> p;
  if (!is_prime(p))
  {
    std::cout << "p debe ser un número primo, terminando el programa\n";
    return;
  }

  std::cout << "Introduzca el valor de a (base de Allice) como número entero positivo: ";
  unsigned a;
  std::cin >> a;

  std::cout << "Introduzca el valor de k (secreto de Allice) como número entero positivo: ";
  unsigned k;
  std::cin >> k;

  std::cout << "Introduzca el valor de x (secreto de Bob) como número entero positivo: ";
  unsigned x;
  std::cin >> x;

  std::cout << "Introduzca el valor del mensaje original como valor entero positivo: ";
  unsigned plaintxt;
  std::cin >> plaintxt;

  unsigned ciphertxt, Ka, Ya, Kb, Yb, invK, decipheredtxt;

  // Create Alice private key
  Ya = f_exp(a, k, p);
  Ka = f_exp(Ya, x, p);
  // Create Bob private key
  Yb = f_exp(a, x, p);
  Kb = f_exp(Yb, k, p);

  //message ciphering
  if (Ka == Kb)
  {
    ciphertxt = (Ka * plaintxt) % p;
  }
  else
  {
    std::cout << "Error durante la creación de las claves \n";
    return;
  }

  //Modular multiplicative inverse:
  invK = mod_mult_inv(Ka, p);
  decipheredtxt = (invK * Ka * plaintxt) % p;

  std::cout << "\nEntrada: p="
            << p << ", a="
            << a << ", k="
            << k << ", x="
            << x << ", m="
            << plaintxt
            << "\nSalida: Ya="
            << Ya << ", Yb="
            << Yb << ", K="
            << Ka << ", C="
            << ciphertxt << ", K^(-1)="
            << invK
            << ", M=" << decipheredtxt
            << "\n";
}
