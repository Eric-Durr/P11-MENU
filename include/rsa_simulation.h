#include <iostream>
#include "rsa.h"

void rsa(void)
{

     std::cout << "\n\n----SIMULADOR DE CIFRADO RSA-----\n\n";
     std::cout << "Introduzca el número primo p como valor entero positivo:";
     long p;
     std::cin >> p;
     std::cout << "Introduzca el número primo q como valor entero positivo:";
     long q;
     std::cin >> q;

     std::cout << "Introduzca el número primo d como un valor entero positivo:";
     long d;
     std::cin >> d;
     std::cout << "P=" << p << "\n"
               << "q=" << q << "\n"
               << "d=" << d << "\n\n";
     std::cout << "Comprobando primalidad de p y q ...\n";

     if (is_prime(p))
     {
          if (is_prime(q))
          {
               std::cout << "Ambos números son primos se procede con el cifrado...\n";
          }
          else
          {
               std::cout << "q=" << q << " no es primo, cancelando el cifrado\n";
               return;
          }
     }
     else
     {
          std::cout << "p=" << p << " no es primo, cancelando el cifrado\n";
          return;
     }

     std::cout << "Calculando n y phi(n) ...\n";

     long n = p * q;
     long phi = (p - 1) * (q - 1);

     std::cout << "Comprobando primalidad de d con phi(n)=" << phi << " ...\n";

     if (gcd(d, phi) != 1)
     {
          std::cout << "No se cumple que d=" << d << " sea primo con phi(n)=" << phi << ", cancelando cifrado \n";
          return;
     }
     else
     {
          std::cout << "d=" << d << " es primo con phi(n)=" << phi << ", se procede con el cifrado \n";
     }
     long e = mod_mult_inv(d, phi);
     std::cout << "Valor de clave de cifrado e=" << e << "\n";

     char cmsg[1000];
     std::cout << "Introduzca el mensaje a cifrar: ";
     getchar();
     std::cin.getline(cmsg, 1000);
     std::string msg = cmsg;
     to_upper(msg);
     std::cout << "Texto a encriptar: " << msg << "\n";
     std::cout << "Como n=" << n << " se divide eltexto en bloques de "
               << block_sz(n) << " caracteres\n";
     std::vector<long> blocks = encode(msg, block_sz(n));
     blocks.pop_back();
     std::cout << "Bloques decimales extraidos del texto: ";
     for (auto element : blocks)
          std::cout << element << " ";
     std::cout << "\n";
     std::vector<long> cblocks = cipher(blocks, e, n);
     std::cout << "Bloques decimales cifrados: ";
     for (auto element : cblocks)
          std::cout << element << " ";

     return;
}