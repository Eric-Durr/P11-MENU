/**
 * Function development file for 
 * Vigenere's ciphering ~refered at vigenere.cpp (main file)
 * 
 * Author: Eric Dürr Sierra | eric.durr.20@ull.edu.es
 * 
 * Created: 23/02/2021
 * Modified: 23/02/2021
 * 
 * 
 */

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

/* Two constants: the alphabet map which we use to cypher and the size of the alphabet. */
const std::vector<std::pair<std::string, int>> alphabet_key_map = {
    {"A", 0}, {"B", 1}, {"C", 2}, {"D", 3}, {"E", 4}, {"F", 5}, {"G", 6}, {"H", 7}, {"I", 8}, {"J", 9}, {"K", 10}, {"L", 11}, {"M", 12}, {"N", 13}, {"O", 14}, {"P", 15}, {"Q", 16}, {"R", 17}, {"S", 18}, {"T", 19}, {"U", 20}, {"V", 21}, {"W", 22}, {"X", 23}, {"Y", 24}, {"Z", 25}};
const int mod = alphabet_key_map.size();

/* the join function will translate the created data structure into a string*/
std::string join(const std::vector<std::vector<std::string>> &ciphered_output)
{
    std::string output = "";

    for (auto block : ciphered_output)
    {
        for (auto element : block)
        {
            output += element;
        }
    }
    return output;
}

/* Compact function used to erase all spaces of the message, this is helpfull for the splitting */
std::string compact(const std::string &input)
{
    std::string result = "";
    for (const auto letter : input)
    {
        if (letter != ' ')
            result += letter;
    }
    return result;
}

/* 
    As long as we work with a structure composed by vectors of vectors that contains a single string (each letter);
    the next function will split the input into that kind of structure. The split is based on the keyword length wich 
    refers to the lenght of each bloc os string vectors pusshed into the main vector. 

 */
std::vector<std::vector<std::string>> v_split(std::string input,
                                              const std::string &keyword)
{
    std::vector<std::vector<std::string>> result;
    while (!input.empty())
    {
        if (!input.empty())
        {
            std::vector<std::string> tmp_str_block;
            for (unsigned int i = 0; i < keyword.size(); i++)
            {
                if (input.empty())
                {
                    break;
                }
                tmp_str_block.push_back(std::string{input.at(0)});
                input.erase(input.begin());
            }
            result.push_back(tmp_str_block);
        }
    }

    return result;
}

/* 
The cipher function will apply the vigenere's modular operation to a single 
letter and the paired keyword letter.

Two separated loops are used to find the number match in the alphabet match 
const, each one for the message letter to cipher and the keyword letter.

When both numbers are found then the module of the add is applied to obtain 
the letter from the alphabet.
*/
std::string cipher(const std::string &letter,
                   const std::string &keyword_letter)
{
    int letter_pos = -1;
    for (auto element : alphabet_key_map)
    {
        if (element.first == letter)
            letter_pos = element.second;
    }
    int key_letter_pos = -1;
    for (auto element : alphabet_key_map)
    {
        if (element.first == keyword_letter)
            key_letter_pos = element.second;
    }

    if (letter_pos == -1 || key_letter_pos == -1)
    {
        return "?";
    }
    else
    {
        std::string ciphered_letter;
        for (auto element : alphabet_key_map)
        {
            if (element.second == (letter_pos + key_letter_pos) % mod)
                ciphered_letter = element.first;
        }
        return ciphered_letter;
    }
}

/* 
The vector ciphering will cover all the data structure calling the cipher function to
form a new structure of the same kind wich contains the ciphered message
 */
std::vector<std::vector<std::string>> v_cipher(
    std::vector<std::vector<std::string>> input,
    const std::string &keyword)
{

    std::vector<std::vector<std::string>> result;
    for (auto block : input)
    {
        std::vector<std::string> ciphered_block;
        int offset = 0;
        for (auto letter : block)
        {
            ciphered_block.push_back(cipher(letter, std::string{keyword[offset]}));
            offset++;
        }
        result.push_back(ciphered_block);
    }

    return result;
}

/* 
The decipher element function will decipher a single letter from the structure using the keyword letter.

The number hunting is equal to the ciper funtion, a change is noticed when extracting the result letter from the alphabet.
    - When the substract of the position numbers is positive is as simple as returning the module of the substract
    - When the substract is negative it is necesary to add the module (alphabet size constant) to the substract, then module is applied.
*/
std::string decipher_element(const std::string &letter,
                             const std::string &keyword_letter)
{
    int letter_pos = -1;
    for (auto element : alphabet_key_map)
    {
        if (element.first == letter)
            letter_pos = element.second;
    }
    int key_letter_pos = -1;
    for (auto element : alphabet_key_map)
    {
        if (element.first == keyword_letter)
            key_letter_pos = element.second;
    }
    if (letter_pos == -1 || key_letter_pos == -1)
    {
        return "?";
    }
    else
    {
        std::string deciphered_letter;
        for (auto element : alphabet_key_map)
        {
            if ((letter_pos - key_letter_pos) >= 0)
            {
                if (element.second == (letter_pos - key_letter_pos) % mod)
                    deciphered_letter = element.first;
            }
            else if ((letter_pos - key_letter_pos) < 0)
            {

                if (element.second == (letter_pos - key_letter_pos + mod) % mod)
                    deciphered_letter = element.first;
            }
        }
        return deciphered_letter;
    }
}

/* 
The vector ciphering will cover all the data structure calling the decipher_element function to
form a new structure of the same kind wich contains the deciphered message
 */
std::string decipher(const std::string ciphered_str, const std::string keyword)
{
    std::vector<std::vector<std::string>> temporal;
    std::vector<std::vector<std::string>> splitted = v_split(ciphered_str, keyword);
    for (auto block : splitted)
    {
        std::vector<std::string> dechipered_block;
        int offset = 0;
        for (auto letter : block)
        {
            dechipered_block.push_back(decipher_element(letter, std::string{keyword[offset]}));
            offset++;
        }
        temporal.push_back(dechipered_block);
    }

    return join(temporal);
}
