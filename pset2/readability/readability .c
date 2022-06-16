#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

int coleman(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: \n");

// counting of arrey cells
    int lenth = strlen(text);

// init. of var.
    int letters = 0, words = 0, sentenses = 0;

    for (int i = 0; i < lenth; i++)
    {

// condition for word
        if (text[i] == ' ')
        {
            words++;
        }

// conditiion for letters
        else if ((65 <= text[i] && text[i] <= 90) || (97 <= text[i] && text[i] <= 122))
        {
            letters++;
        }

// Condition for sensteses
        else if ((text[i] == 46) || (text[i] == 63) || (text[i] == 33))
        {
            sentenses++;
        }

    }
// Word +1 must be
    words = words + 1;

// Final conditions for more then 16+
    int grade = coleman(letters, words, sentenses);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
// Cond less 1
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

// Rest
    else
    {
        printf("Grade %i\n", grade);
    }
}



int coleman(int letters, int words, int sentences)
{
    float L = (letters * 100) / (float)words;
    float S = (sentences * 100) / (float)words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return round(index);
}
