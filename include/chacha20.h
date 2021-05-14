#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#define ROUNDS 20
#define OFFSET 2
#define BASE 4
/* Transform any UINT32 string into the corresponding number*/
uint32_t string_to_uint32(std::string word_in_string)
{
  return stol(word_in_string, 0, 16);
}

/* Transform any UINT32 into a string that represents it */
std::string uint32_to_string(uint32_t word)
{
  return std::to_string(static_cast<int>(word));
}

/* Transform a whole array of strings into a UINT32 vector */
std::vector<uint32_t> translate_strings(std::vector<std::string> strings)
{
  std::vector<uint32_t> words;
  for (auto element : strings)
    words.push_back(string_to_uint32(element));
  return words;
}

/* Transform a whole array of UINT32 into a UINT32 strings vector */
std::vector<std::string> translate_words(std::vector<uint32_t> words)
{
  std::vector<std::string> strings;
  for (auto element : words)
  {
    strings.push_back(uint32_to_string(element));
  }
  return strings;
}

/* Transform a UINT32 number into Hexadecimal string format */
std::string uint32_to_hexstr(uint32_t word)
{
  std::stringstream result;
  result << std::hex << word;
  return result.str();
}

/* Transform an array UINT32 number into a vectors of Hexadecimal string format values*/
std::vector<std::string> hex_strings(std::vector<uint32_t> words)
{
  std::vector<std::string> result;
  for (auto element : words)
    result.push_back(uint32_to_hexstr(element));
  return result;
}

/* Format of the output of a vector of UINT32 values */
std::string words_to_string(std::vector<uint32_t> words)
{
  std::string output = "[\n";
  int i = 0;
  for (auto word : words)
  {
    output += uint32_to_string(word) + ", ";

    i++;
    if ((i % 4) == 0)
    {
      output += "\n";
    }
  }
  output += "]\n";
  return output;
}

/* Format of the output of a vector of strings values */
std::string strings_to_string(std::vector<std::string> words)
{
  std::string output = "[\n";
  int i = 0;
  for (auto word : words)
  {
    output += word + ", ";

    i++;
    if ((i % 4) == 0)
    {
      output += "\n";
    }
  }
  output += "]\n";
  return output;
}

/* Reverse strings digits by a given offset */
std::string reverse_string(std::string input, int offset)
{
  std::string output = "";
  for (int i = input.size() - 1; i > 0; i -= offset)
  {
    for (int j = offset - 1; j >= 0; j--)
      output.push_back(input[i - j]);
  }
  return output;
}

/* Reverse a whole set of strings with the previous function and from a base*/
std::vector<std::string> reverse_set(std::vector<std::string> input, int base, int offset)
{
  for (unsigned int i = base; i < input.size(); i++)
  {
    input[i] = reverse_string(input[i], offset);
  }

  return input;
}

/* Binary rotation of a UINT32 word by a given value */
uint32_t ROTL(uint32_t word, int n)
{
  return ((word << n) | (word >> (32 - n)));
}

/* Chacha20 Quarter Rotation of the given positions in the given set of strings*/
std::vector<std::string> QR(int a, int b, int c, int d, std::vector<std::string> in)
{
  uint32_t a1 = string_to_uint32(in[a]);
  uint32_t b1 = string_to_uint32(in[b]);
  uint32_t c1 = string_to_uint32(in[c]);
  uint32_t d1 = string_to_uint32(in[d]);
  a1 += b1;
  d1 ^= a1;
  d1 = ROTL(d1, 16);

  c1 += d1;
  b1 ^= c1;
  b1 = ROTL(b1, 12);

  a1 += b1;
  d1 ^= a1;
  d1 = ROTL(d1, 8);

  c1 += d1;
  b1 ^= c1;
  b1 = ROTL(b1, 7);

  in[a] = uint32_to_hexstr(a1);
  in[b] = uint32_to_hexstr(b1);
  in[c] = uint32_to_hexstr(c1);
  in[d] = uint32_to_hexstr(d1);
  return in;
}

std::vector<std::string> chacha_block(std::vector<std::string> out, std::vector<std::string> in, int times, bool inner)
{
  std::vector<std::string> x;
  for (unsigned int i = 0; i < in.size(); i++)
  {
    x.push_back(in[i]);
  }

  for (int i = 0; i < times; i += 2)
  {
    x = QR(0, 4, 8, 12, x);
    x = QR(1, 5, 9, 13, x);
    x = QR(2, 6, 10, 14, x);
    x = QR(3, 7, 11, 15, x);

    x = QR(0, 5, 10, 15, x);
    x = QR(1, 6, 11, 12, x);
    x = QR(2, 7, 8, 13, x);
    x = QR(3, 4, 9, 14, x);
  }

  // Final state
  if (inner == true)
  {
    std::cout << "Estado final tras " << times << " iteraciones =\n";
    std::cout << strings_to_string(x) << "\n";
  }

  for (unsigned int i = 0; i < in.size(); i++)
  {
    uint32_t o = string_to_uint32(x[i]) + string_to_uint32(in[i]);
    out.push_back(uint32_to_hexstr(o));
  }
  return out;
}