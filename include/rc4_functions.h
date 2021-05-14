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
#include <string>
#include <sstream>
#include <iostream>

void initializeRC4(std::vector<int> &s,
                   const std::vector<int> &seed)
{
  for (int i = 0; i < 256; i++)
  {
    s.push_back(i);
  }
  int j = 0;
  for (int i = 0; i < 256; i++)
  {
    j = (j + s[i] + seed[i % seed.size()]) % 256;
    std::swap(s[i], s[j]);
  }
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
