#include<stdio.h>
#include<cs50.h>




int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    // make all characters spaces

    char row_status[height + 2 + height];
    for (int i = 0; i < height + 4; i++)
    {
        row_status[i] = ' ';
    }
    for (int row = 1; row <= height; row++)
    {
        // add hashes and end the string
        row_status[height - row] = '#';
        row_status[height + 1 + row] = '#';
        row_status[height + 2 + row] = 0;

        // print out characters
        for (int i = 0; i < height + 2 + row; i++)
        {
            printf("%c", row_status[i]);
        }
        printf("\n");
    }


}