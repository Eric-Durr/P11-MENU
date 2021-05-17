/**
 * @file elip.cpp
 * @author Eric Dürr (eric.durr.20@ull.edu.es)
 * @brief Elliptic curve criptography based on ElGamal and Diffie-Hellman algorithms.
 *          -> The Elyptic curve type is: Y^2=X^3+aX+b
 * @version 0.1
 * @date 2021-05-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/ecc.h"
#include <vector>

void ecc()
{

     std::cout << "\n\n--- ElGamal y Diffie-Hellman elípticos ---\n\n";

     std::cout << "Introduzca el valor primo p (módulo) como un entero positivo:";
     long p;
     std::cin >> p;
     if (!prime(p))
     {
          std::cout << "ERROR: El número p (modulo) debe ser un número primo, se introdujo p=" << p << "\n";
          return;
     }

     std::cout << "Introduzca el valor a de la curva en el rango 0 - " << p << " como un entero positivo:";
     long a;
     std::cin >> a;

     std::cout << "Introduzca el valor b de la curva en el rango 0 - " << p << " como un entero positivo:";
     long b;
     std::cin >> b;

     if (a <= 0 || a >= p)
     {
          std::cout << "ERROR: a debe ser un número entre 0 y p=" << p << "\n";
          return;
     }
     if (b <= 0 || b >= p)
     {
          std::cout << "ERROR: b debe ser un número entre 0 y p=" << p << "\n";
          return;
     }
     std::cout << "Introduzca el valor de la coordenada x del punto base como entero positivo:";
     long px;
     std::cin >> px;
     std::cout << "Introduzca el valor de la coordenada y del punto base como entero positivo:";
     long py;
     std::cin >> py;
     std::pair<long, long> base(px, py);

     std::cout << "Introduzca el secreto de Bob (db) como número entero positivo:";
     long db;
     std::cin >> db;

     std::cout << "Introduzca el secreto de Allice (da) como número entero positivo:";
     long da;
     std::cin >> da;

     std::cout << "Introduzca el valor del mensage original como número entero positivo:";
     long msg;
     std::cin >> msg;

     std::cout << "\nValores generados:\n";
     std::cout
         << "p=" << p << "\n"
         << "a=" << a << "\n"
         << "b=" << b << "\n"
         << "G="
         << "(" << base.first << "," << base.second << ")\n"
         << "db=" << da << "\n"
         << "da=" << db << "\n"
         << "msg=" << msg << "\n";
     std::cout << "\nSe opera sobre la curva:  y^2 (mod " << p << ") = x^3 + " << a << "*x + " << b << "(mod " << p << ")\n\n";
     std::cout << "Generando los puntos de la curva ...\n";

     std::vector<std::pair<long, long>> e_points = extract_points(p, a, b);
     std::cout << "Puntos generados: ";
     for (auto point : e_points)
          std::cout << "(" << point.first << "," << point.second << ") ";
     std::cout << "\n";
     std::cout << "Generando las claves públicas de Bob y Alice...\n";
     std::pair<long, long> pub_b = pubkey(db, base, a, p);
     std::pair<long, long> pub_a = pubkey(da, base, a, p);

     std::cout << "dbG=(" << pub_b.first << "," << pub_b.second << ")\n";
     std::cout << "daG=(" << pub_a.first << "," << pub_a.second << ")\n";

     std::cout << "Generando las claves privadas de Allice y Bob...\n";
     std::pair<long, long> shared_a = shkey(da, pub_b, a, p);
     std::pair<long, long> shared_b = shkey(db, pub_a, a, p);

     std::cout << db << "*(" << pub_a.first << "," << pub_a.second << ") = (" << shared_b.first << "," << shared_b.second << ")\n";

     std::cout << da << "*(" << pub_b.first << "," << pub_b.second << ") = (" << shared_a.first << "," << shared_a.second << ")\n";

     std::cout << "Proceso de cifrado del mensaje...\n";
     long M = great_strict_pow(msg);
     long h = p / M;
     std::cout << "M=" << M << "\n";
     std::cout << "h=" << p << "/" << M << "=" << h << "\n";
     std::pair<long, long> msg_point = msg_2_point(msg, h, M, e_points);
     std::cout << "mensaje original como texto plano: Qm=(" << msg_point.first << "," << msg_point.second << ")\n";
     std::cout << "Mensaje cifrad y clave pública enviada de Allice a Bob: \n";
     std::pair<long, long> c_msg = add_points(msg_point, shared_a, a, p);

     std::cout << "{ mensaje cifrado: (" << c_msg.first << "," << c_msg.second << ") ; Clave pública: (" << pub_a.first << "," << pub_a.second << ")}\n";

     return;
}
