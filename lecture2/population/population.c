




#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Start Size: ");
    }
    while (start_size < 9);
    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End Size: ");
    }
    while (end_size < start_size);
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int start_of_year;
    for (; start_size < end_size; years++)
    {
        start_of_year = start_size;
        start_size += start_of_year / 3;
        start_size -= start_of_year / 4;

    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}
