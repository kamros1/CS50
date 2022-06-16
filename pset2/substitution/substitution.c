#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

bool letter_check(int a, string arrey[]);
bool cell_equals_check(int a, string arrey[]);

int main(int argc, string argv[])
{

    // If to check command line arg
    if (argc != 2)
    {
        printf("subtstitution KEY\n");
        return 1;
    }

    // If key is valid
    if (strlen(argv[1]) == 26 &&  cell_equals_check(1, argv) && letter_check(1, argv) && argc == 2)
    {
        string plain_text = get_string("Plaintext: \n");

        char cipher[strlen(plain_text)];

        printf("ciphertext: ");

        // Fill up array in
        for (int i = 0; i < strlen(plain_text); i++)
        {

            // For uppercase letter
            if (plain_text[i] >= 65 && plain_text[i] <= 90)
            {
                cipher[i] = argv[1][plain_text[i] - 65];
                printf("%c", toupper(cipher[i]));
            }

            // For lowercase letter
            else if (plain_text[i] >= 97 && plain_text[i] <= 122)
            {
                cipher[i] = argv[1][plain_text[i] - 97];
                printf("%c", tolower(cipher[i]));
            }

            // Other char
            else
            {
                cipher[i] = plain_text[i];
                printf("%c", cipher[i]);
            }
        }
        printf("\n");
        return 0;
    }

    // If to check 26 char
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // If to check for other char then letters
    if (!letter_check(1, argv))
    {
        printf("Key should contain only characters\n");
        return 1;
    }

    // If to check repeted letters
    if (!cell_equals_check(1, argv))
    {
        printf("Repeted letter in the code\n");
        return 1;
    }
}

// Function definition

// Letter check function
bool letter_check(int a, string arrey[])
{
    for (int i = 0; i < strlen(arrey[a]); i++)
    {
        if (!(((arrey[a][i] >= 65) && (arrey[a][i] <= 90)) || ((arrey[a][i] >= 97) && (arrey[a][i] <= 122))))
        {
            return false;
            break;
        }
    }
    return true;
}

// Cell compare function
bool cell_equals_check(int a, string arrey[])
{
    for (int i = 0; i < (strlen(arrey[a])); i++)
    {
        for (int j = i + 1; j < strlen(arrey[a]); j++)
        {
            if (arrey[a][i] == arrey[a][j])
            {
                return false;
                break;
            }
        }
    }
    return true;
}