#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define and &&
#define or ||
#define not !
#define BLOCK_SIZE 512





int main(int argc, char *argv[])
{
    // check for valid command line arguments

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE  \n");
        return 1;
    }

    // open raw file to read
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        return 1;
    }

    //buffer for 512 bytes

    uint8_t buffer[BLOCK_SIZE];

    // current file string name

    char current_file_name[8];

    // current file jpg value

    FILE *current_file = NULL;

    // current file number and if a file has already been opened


    int file_num = 0;

    bool file_open = false;


    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff and buffer[1] == 0xd8 and buffer[2] == 0xff)
        {
            if (buffer[3] == 0xe0 or buffer[3] == 0xe1 or buffer[3] == 0xe2 or buffer[3] == 0xe3 or buffer[3] == 0xe4 or buffer[3] == 0xe5
                or buffer[3] == 0xe6 or buffer[3] == 0xe7 or buffer[3] == 0xe8 or buffer[3] == 0xe9 or buffer[3] == 0xea or buffer[3] == 0xeb
                or buffer[3] == 0xec or buffer[3] == 0xed or buffer[3] == 0xee or buffer[3] == 0xef)
            {
                if (file_open)
                {
                    fclose(current_file);
                    file_num++;
                }
                sprintf(current_file_name, "%03i.jpg", file_num);
                current_file = fopen(current_file_name, "w");
                file_open = true;
            }
        }
        if (file_open)
        {
            fwrite(buffer, 1, BLOCK_SIZE, current_file);
        }
    }
    if (current_file != NULL)
    {
        fclose(current_file);
    }
    fclose(file);
}