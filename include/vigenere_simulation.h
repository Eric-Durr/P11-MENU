

#include <iostream>
#include <regex>
#include "vigenere_functions.h"

/* Text formart check function: throug a regular expresion validates the message to cipher */
bool text_check(const std::string &input_str);

void vigenere(void)
{
    system("clear");
    std::string message, keyword;
    int op;

    std::string temp_key;
    bool ciphered_status = false;

    while (1)
    {
        op = 7;
        std::cout << "\n\n--MENÚ PARA EL CIFRADO DE VIGENERE--\n\n";
        std::cout << "\t1) Introducir mensaje\n";
        std::cout << "\t2) Encriptar mensaje\n";
        std::cout << "\t3) Desencriptar mensaje\n";
        std::cout << "\t4) Mostrar mensaje en estado actual\n";
        std::cout << "\t0) Volver al programa principal\n";
        std::cout << "Introducir opción: ";
        std::cin >> op;
        std::cout << "\n\n";

        if (op == 0)
        {
            break;
        }

        switch (op)
        {
        case 1: /* Message input: the user can insert a message to cypher */
            std::cout << "Mensaje: ";
            std::cin.ignore();
            std::getline(std::cin, message, '\n');
            if (text_check(message))
            {
                std::cout << "\n\n\t mensaje introducido: " << message << "\n";
            }
            else
            {
                message = "";
                std::cout << "\n\n\t mensaje erroneo solo pueden ser palabras en mayúscula y sin Ñ, se pueden utilizar espacios pero no números ni signos de puntuación\n";
            }
            break;
        case 2: /* Message Ciphering: when launched and if there is a message a keyword is asked, 
                   then message passes to encrypted status */
            if (message.empty())
            {
                std::cout << "--- No hay mensaje ---\n\n";
            }
            else
            {
                if (ciphered_status == false)
                {
                    std::cout << "Itroduzca una palabra clave: ";
                    std::cin.ignore();
                    std::getline(std::cin, keyword, '\n');
                    std::cout << "\n\n\t palabra clave introducida: " << keyword << "\n";
                    keyword = compact(keyword);
                    message = join(v_cipher(v_split(compact(message), keyword), keyword));
                    ciphered_status = true;
                }
                else
                {
                    std::cout << "\n\n\t mensaje ya cifrado \n";
                }
            }

            break;
        case 3: /* Message Deciphering: if there is a message, the user is asked for the keyword. 
                   When the right keyword is introduced the message passes to deciphered status */
            if (message.empty())
            {
                std::cout << "--- No hay mensaje ---\n\n";
            }
            else
            {
                if (ciphered_status == true)
                {
                    std::cout << "Itroduzca la palabra clave: ";
                    std::cin.ignore();
                    std::getline(std::cin, temp_key, '\n');
                    temp_key = compact(temp_key);
                    if (temp_key != keyword)
                    {
                        std::cout << "\n\nPalabra clave equivocada - saliendo de la opción";
                    }
                    else
                    {
                        ciphered_status = false;
                        message = decipher(message, keyword);
                    }
                }
                else
                {
                    std::cout << "\n\n\t mensaje ya descifrado \n";
                }
            }

            break;
        case 4: /* Message Output: If there is a message it can be displayed at console whenever it 
                   is ciphered or not. */
            if (message.empty())
            {
                std::cout << "--- No hay mensaje ---\n\n";
            }
            else
            {
                std::cout << "Mensaje en el estado actual: " << message << " \n";
            }
            break;
        default:
            std::cout << "Opción no contemplada para el número " << op
                      << " vuelva a intentarlo\n";
            break;
        }

        std::cout << "\n\t\tPulse enter para continuar...";
        getchar();
        getchar();
        //system("clear");
    }
}

/* INSTRUCCIÓN PARA COMPROBACIÓN DEL CONTENIDO DEL TEXTO -> REGEXP */
bool text_check(const std::string &input_str)
{
    std::regex only_letters_and_spaces("[A-Z ]*$");
    return std::regex_match(input_str, only_letters_and_spaces);
}