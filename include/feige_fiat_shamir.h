#include <iostream>
#include <math.h>
#include <vector>

long coprimo(const long &n);
long mcd(long n1, long n2);
unsigned int modulo_a_positivo(int a, unsigned int m);
unsigned exp_rap(unsigned x, unsigned y, unsigned mod);

void ffs()
{
  std::cout << "\n\n--- Protocolo Feige-Fiat-Shamir ---\n\n";
  std::cout << "Introduzca el valor del número primo p como entero positivo:";
  long p;
  std::cin >> p;
  std::cout << "Introduzca el valor del número primo q como entero positivo:";
  long q;
  std::cin >> q;
  long n = p * q;
  std::cout << "Se han escogido los número p=" << p << " y q=" << q << " se publica n=p*q=" << n << "\n";
  std::vector<long> s_v;
  std::cout << "Introduzca  la identificación secreta de Allice como un número s entre 0 y " << n << " donde s es coprimo con n=" << n << "\n";
  while (1)
  {
    long s;
    std::cout << "valor a insertar: ";

    std::cin >> s;
    if (s <= 0 || s >= n)
    {
      std::cout << "ERROR: s debe ser un número comprendido entre 0 y n=" << n << "\n";
      return;
    }
    if (mcd(s, n) != 1)
    {
      std::cout << "ERROR:  s debe ser coprimo con n \n";
      return;
    }
    s_v.push_back(s);
    std::cout << "¿Desea seguir insertando? (s/n)";
    std::string opt;
    std::cin >> opt;
    if (opt == "n")
      break;
  }
  std::vector<long> v_v;
  for (auto s : s_v)
  {
    long v = exp_rap(s, 2, n);
    v_v.push_back(v);
  }
  std::cout << " identificación pública de Allice: \n";
  int i = 1;
  for (auto v : v_v)
  {
    std::cout << "v" << i << "=" << v << "(mod " << n << ")\n";
    i++;
  }
  std::cout << "Introduzca  el compromiso secreto de Allice como un número cualquiera (simula el entero aleatorio y el signo aleatorio)\n";
  std::cout << "Entero aleatorio: ";
  long r;
  std::cin >> r;
  std::cout << "signo aleatorio (+1 / -1): ";
  long sig;
  std::cin >> sig;
  if (sig != -1 && sig != 1)
  {
    std::cout << "ERROR:  solo se contempla que el signo valga +1 o -1, se ha introducido " << sig << "\n";
    return;
  }
  long x = sig * std::pow(r, 2);
  sig < 0 ? x = modulo_a_positivo(x, p) : x %= n;
  std::cout << "Se emite desde Allice a Bob el testigo x=" << x << "(mod " << n << ")\n";

  std::vector<long> a_v;
  std::cout << "Se va a generar el reto que Bob le envía a Allice, se especifican como bits, tantos como valores s introducidos:\n";
  i = 1;
  for (auto s : s_v)
  {
    int a;
    std::cout << "Introducir bit " << i << ": ";
    std::cin >> a;
    if (a != 0 && a != 1)
    {
      std::cout << "ERROR:  debe ser un valor binario (0 o 1)\n";
      return;
    }
    a_v.push_back(a);

    i++;
  }
  long y = r;
  i = 0;

  std::cout << "Y=" << r << "";
  for (auto s : s_v)
  {
    std::cout << "*" << s << "^" << a_v[i];
    y *= exp_rap(s, a_v[i], n);
    i++;
  }
  std::cout << "\nRespuesta enviada de Allice a Bob y=" << y << "(mod " << n << ")\n";
  long lhs_verif = std::pow(y, 2);
  lhs_verif %= n;
  std::cout << "Bob dede verificar que y^2=" << y << "^2=" << lhs_verif << "=";

  long rhs_verif = x;
  std::cout << x;
  i = 0;
  for (auto v : v_v)
  {

    std::cout << "*" << v << "^" << a_v[i];
    rhs_verif *= exp_rap(v, a_v[i], n);
    i++;
  }
  rhs_verif %= n;
  std::cout
      << "=" << rhs_verif << "(mod " << n << ")\n";

  if (lhs_verif == rhs_verif)
  {
    std::cout << "La  respuesta enviada ha sido verificada de manera correcta\n";
  }
  else
  {
    std::cout << "La  respuesta enviada no ha podido ser verificada\n";
  }
}

long mcd(long n1, long n2)
{
  long aux;
  while (n1 != 0)
  {
    aux = n1;
    n1 = n2 % n1;
    n2 = aux;
  }

  return n2;
}

unsigned int modulo_a_positivo(int a, unsigned int m)
{
  while (a < 0)
  {
    a += m;
  }
  return a % m;
}

unsigned exp_rap(unsigned x, unsigned y, unsigned mod)
{
  unsigned res = 1;
  x %= mod; // updating x
  if (x == 0)
    return 0;

  while (y > 0)
  {
    // multiply x with res when y is odd
    if (y & 1)
      res = (res * x) % mod;
    // y = y/2
    y >>= 1;
    // Change x to x^2
    x = (x * x) % mod;
  }
  return res;
}