/**
 * 
 * Author: Eric Dürr Sierra | eric.durr.20@ull.edu.es
 * 
 * Created: 01/03/2021
 * Modified: 01/03/2021
 * 
 * 
 */

#include <vector>
#include <bitset>
#include <string>
#include <sstream>
#include <iostream>

void initializeRC4(std::vector<int> &s,
                   std::vector<int> &seed)
{
  std::vector<int> k;
  for (int i = 0; i < 256; i++)
  {
    s.push_back(i);
  }

  for (unsigned i = 0; i < 256; i++)
  {
    k.push_back(seed[i % seed.size()]);
  }

  std::cout << "\tS=[ ";
  for (auto val : s)
    std::cout << val << " ";
  std::cout << "]\n";
  std::cout << "\tK=[ ";
  for (auto val : k)
    std::cout << val << " ";
  std::cout << "]\n";

  int j = 0;
  for (int i = 0; i < 256; i++)
  {
    j = (j + s[i] + k[i]) % 256;
    std::cout << "\ts[" << i << "]=" << s[i] << " k[" << i << "]=" << k[i] << " produce f=" << j;
    std::swap(s[i], s[j]);
    std::cout << " y s[" << i << "]=" << s[i] << " <-> s[" << j << "]=" << s[j] << "\n";
  }
  std::cout << "\tS=[ ";
  for (auto val : s)
    std::cout << val << " ";
  std::cout << "]\n";
}

std::vector<int> generateCipheringSecuence(std::vector<int> &o,
                                           std::vector<int> &s)
{
  std::vector<int> t;
  int n = 0;
  int m = 0;
  for (unsigned int i = 0; i < o.size(); i++)
  {
    n = (n + 1) % 256;
    m = (m + s[n]) % 256;
    std::swap(s[n], s[m]);
    int rand = (s[n] + s[m]) % 256;
    t.push_back(s[rand] ^ o[i]);
    std::cout << "BYTE " << i + 1 << " de secuencia cifrante: S[" << rand + 1 << "]=" << s[rand] << ":\t\t" << std::bitset<8>(s[rand]) << "\n";
    std::cout << "BYTE " << i + 1 << " de texto original: M[" << i + 1 << "]=" << o[i] << ":\t\t\t" << std::bitset<8>(o[i]) << "\n";
    std::cout << "BYTE " << i + 1 << " de texto cifrado: C[" << i + 1 << "]=" << t[i] << ":\t\t\t" << std::bitset<8>(t[i]) << "\n";
  }
  return t;
}

std::string secuenceToString(const std::vector<int> &s)
{
  std::string output = "[\n";
  int line = 0;
  for (auto i : s)
  {
    if (line == 16)
    {
      output += "\n";
      line = 0;
    }
    output += std::to_string(i) + " ";

    line++;
  }
  output += "\n]";
  return output;
}
