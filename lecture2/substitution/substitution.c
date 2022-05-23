#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#define or ||
#define and &&
#define not !



void ciphered(string key, string text, char *converted_digits)
{
    //set digits to null
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char alphabet_upper[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for (int letter_index = 0; letter_index < strlen(text); letter_index++)
    {
        // check if letter in alphabet
        if (not isalpha(text[letter_index]))
        {
            converted_digits[letter_index] = text[letter_index];
            continue;
        }

        //check where letter is in alphabet

        for (int i = 0; i < strlen(alphabet); i++)
        {
            if (text[letter_index] == alphabet[i])
            {
                //convert
                converted_digits[letter_index] = key[i];
                char lower_digit = tolower(converted_digits[letter_index]);
                converted_digits[letter_index] = lower_digit;
                break;
            }
            else if (text[letter_index] == alphabet_upper[i])
            {
                //convert
                converted_digits[letter_index] = key[i];
                char upper_digit = toupper(converted_digits[letter_index]);
                converted_digits[letter_index] = upper_digit;
                break;
            }
        }
    }
    converted_digits[strlen(text)] = '\0';
}

int main(int argc, string argv[])
{
    // check for invalid command line arguments

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // check for invalid command line argument type
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 letters.\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        //check for non-alphabetical characters
        if (not isalpha(argv[1][i]))
        {
            printf("Key must only contain characters in the alphabet.\n");
            return 1;
        }
        // iterate though other characters to check for duplicates
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (argv[1][j] == argv[1][i])
            {
                printf("Key must not have duplicates.\n");
                return 1;
            }
        }
    }

    string non_ciphered = get_string("plaintext: ");
    char text_ciphered[strlen(non_ciphered)];
    ciphered(argv[1], non_ciphered, text_ciphered);
    printf("ciphertext: %s\n", text_ciphered);
}