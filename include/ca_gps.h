#include <vector>
#include <string>

#define LINE 120

/* This enum is used to select the Satellite ID */
enum taps_num
{
  PRN1,
  PRN2,
  PRN3,
  PRN4,
  PRN5,
  PRN6,
  PRN7,
  PRN8,
  PRN9,
  PRN10,
  PRN11,
  PRN12,
  PRN13,
  PRN14,
  PRN15,
  PRN16,
  PRN17,
  PRN18,
  PRN19,
  PRN20,
  PRN21,
  PRN22,
  PRN23,
  PRN24,
  PRN25,
  PRN26,
  PRN27,
  PRN28,
  PRN29,
  PRN30,
  PRN31,
  PRN32
};

/* The const structure contains all the taps for each ID */
const std::vector<std::pair<int, int>>
    id_taps({
        {2, 6},
        {3, 7},
        {4, 8},
        {5, 9},
        {1, 9},
        {2, 10},
        {1, 8},
        {2, 9},
        {3, 10},
        {2, 3},
        {3, 4},
        {5, 6},
        {6, 7},
        {7, 8},
        {8, 9},
        {9, 10},
        {1, 4},
        {2, 5},
        {3, 6},
        {4, 7},
        {5, 8},
        {6, 9},
        {1, 3},
        {4, 6},
        {5, 7},
        {6, 8},
        {7, 9},
        {8, 10},
        {1, 6},
        {2, 7},
        {3, 8},
        {4, 9},
    });

/* Transforms a vector of integers into a string value */
std::string to_string(const std::vector<int> &secuence)
{
  std::string output = "";
  for (auto digit : secuence)
    output += std::to_string(digit);

  return output;
}

/* Rotates the elements in a vector to the Right and 
   inserts a new value */
void rotate_elements(std::vector<int> &secuence, int feedback)
{
  for (unsigned int i = secuence.size() - 1; i > 0; --i)
    secuence[i] = secuence[i - 1];
  secuence[0] = feedback;
}

/* Transforms in one step the first Gold secuence and 
   returns the 10th number after rotation*/
int step_g1(std::vector<int> &secuence)
{
  int feedback = secuence[2] ^ secuence[9];
  int last = secuence[9];
  rotate_elements(secuence, feedback);
  return last;
}

/* Transforms in one step the second Gold secuence */
void step_g2(std::vector<int> &secuence)
{
  int feedback = secuence[1] ^ secuence[2] ^ secuence[5] ^
                 secuence[7] ^ secuence[8] ^ secuence[9];
  rotate_elements(secuence, feedback);
}

/* Computes one unique digit of the C/A code depending
   on the satellite ID tap selected and the 10th digit 
   returned by one LFSR operation */
int ca_digit(const int &g1,
             const std::vector<int> &g2,
             std::pair<int, int> &taps)
{
  return g1 ^ g2[taps.first - 1] ^ g2[taps.second - 1];
}

/* Generates the specified amoount of steps in the 
   C/A GPS generator */
/* When the number of steps arent specified it generates 
   the full code.*/
std::vector<int> generate(std::vector<int> &g1,
                          std::vector<int> &g2,
                          std::pair<int, int> tap,
                          const int &times = 1023,
                          bool snitch = false)
{
  std::vector<int> result;
  if (snitch)
  {
    std::cout << "\t-LFSR1-\t\t-FB-\t\t-10th bit-\t|\t-LFSR2-\t\t-FB-\t\t|\tC/A GPS bit: \n";
    for (int i = 0; i < LINE; ++i)
      std::cout << "-";
    std::cout << "\n";
  }

  for (int i = 0; i < times; ++i)
  {
    if (snitch)
    {
      std::cout << "\t" << to_string(g1);
    }

    int last = step_g1(g1);

    if (snitch)
    {
      std::cout << "\t " << g1[0] << "\t\t " << last << "\t\t|\t" << to_string(g2);
    }

    result.push_back(ca_digit(last, g2, tap));
    step_g2(g2);

    if (snitch)
    {
      std::cout << "\t " << g2[0] << "\t\t|\t" << result.back() << "\n";
    }
  }
  return result;
}
