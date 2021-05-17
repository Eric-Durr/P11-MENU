/**
 * @file menu.cpp
 * @author Eric Dürr (eric.durr.20@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 2021-05-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/vigenere_simulation.h"
#include "../include/rc4_simulation.h"
#include "../include/chacha20_simulation.h"
#include "../include/ca_gps_simulation.h"
#include "../include/binary_mult_simulation.h"
#include "../include/aes_simulation.h"
#include "../include/cbc_simulation.h"
#include "../include/gamal_simulation.h"
#include "../include/rsa_simulation.h"
#include "../include/ecc_simulation.h"
#include "../include/feige_fiat_shamir.h"
#include <iostream>

int main(int argc, char *argv[])
{
     while (1)
     {
          int opt = -1;
          std::cout << "--- P11 | MENÚ DE PRÁCTICAS DE ENCRIPTACIÓN ---\n";
          std::cout << "\n";
          std::cout << "Simulaciones disponibles:"
                    << "\n"
                    << "\t 1.- Cifrado de Vigenere\n"
                    << "\t 2.- Cifrado RC4\n"
                    << "\t 3.- Cifrado ChaCha20\n"
                    << "\t 4.- Generador C/A de GPS\n"
                    << "\t 5.- Multiplicación en SNOW 3G y AES\n"
                    << "\t 6.- Cifrado AES\n"
                    << "\t 7.- Cifrado en bloque CBC\n"
                    << "\t 8.- Cifrado ElGamal\n"
                    << "\t 9.- Cifrado RSA\n"
                    << "\t 10.- Cifrado Diffie-Hellman y ElGamal Elípticos\n"
                    << "\t 11.- Protocolo Feige-Fiat-Shamir\n";
          std::cout << "Introduzca la opción a elegir, 0 para salir: ";
          std::cin >> opt;

          if (opt == 0)
               return 0;

          switch (opt)
          {
          case 1:
               vigenere();
               /* code */
               break;
          case 2:
               rc4();
               /* code */
               break;
          case 3:
               chacha20();
               /* code */
               break;
          case 4:
               ca_gps();
               /* code */
               break;
          case 5:
               binary();
               /* code */
               break;
          case 6:
               aes();
               /* code */
               break;
          case 7:
               cbc();
               /* code */
               break;
          case 8:
               elgamal();
               /* code */
               break;
          case 9:
               rsa();
               /* code */
               break;
          case 10:
               ecc();
               /* code */
               break;
          case 11:
               ffs();
               /* code */
               break;

          default:
               std::cout << "ERROR: opción escogida no es válida ...\n";
               break;
          }
          getchar();
          std::cout << "\n\t\t-Pulse ENTER para continuar-";
          getchar();
          system("clear");
     }

     return 0;
}
