#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define and &&
#define or ||
#define not !


int main(void)
{

    // get input

    string phrase = get_string("Text: ");
    int letters = 0;
    // get letters
    for (int i = 0; i < strlen(phrase); i++)
    {
        if (isalpha(phrase[i]))
        {
            letters++;
        }
    }


    int words = 1;

    //get words
    for (int i = 0; i < strlen(phrase); i++)
    {
        if (phrase[i] == ' ')
        {
            words++;
        }
    }

    //get letters per one hundred words

    float L = ((float) letters / (float) words) * 100.0;

    //get sentances

    int sentances = 0;

    for (int i = 0; i < strlen(phrase); i++)
    {
        if (phrase[i] == '.' or phrase[i] == '?' or phrase[i] == '!')
        {
            sentances++;
        }
    }

    // get number of sentances per 100 words

    float S = ((float) sentances / (float) words) * 100.0;


    /*
    printf("Letters: %i\n", letters);
    printf("Words: %i\n", words);
    printf("Sentances: %i\n", sentances);
    */

    //make grade level

    float index = 0.0588 * L - 0.296 * S - 15.8;

    // check if grade is greater than or equal to 1 and is less than 16
    if (index < 16 and index >= 1)
    {
        printf("Grade %i\n", (int) round(index));
    }

    //if grade is 16+

    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    // if grade is under 1

    else
    {
        printf("Before Grade 1\n");
    }
}

