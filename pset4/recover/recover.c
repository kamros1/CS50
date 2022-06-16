#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <stdint.h>

bool jpegheader(uint8_t *buffer);

int main(int argc, char *argv[])
{
    // Check if proper command line arg
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    // Create header buffer pointer
    uint8_t *headbuff = malloc(sizeof(uint8_t) * 512);

    if (headbuff == NULL)
    {
        return 1;
    }

    // Creat variable name for jpg file
    char *intname = malloc(sizeof(char *));
    if (intname == NULL)
    {
        return 1;
    }

    //counter for file name
    int k = 0;

    while (true)
    {
        fread(headbuff, 512, 1, f);
        if (jpegheader(headbuff))
        {
            break;
        }
    }
    /* Create new name for file Open new file to write JPEG*/
    sprintf(intname, "%03i.jpg", k);
    FILE *s = fopen(intname, "a");
    fwrite(headbuff, 512, 1, s);

    while (fread(headbuff, 512, 1, f))
    {
        if (jpegheader(headbuff))
        {
            fclose(s);
            k++;
            sprintf(intname, "%03i.jpg", k);
            s = fopen(intname, "a");
            fwrite(headbuff, 512, 1, s);
        }

        else if (!jpegheader(headbuff))
        {
            fwrite(headbuff, 512, 1, s);
        }
    }

    // FREE
    free(headbuff);
    free(intname);
}

bool jpegheader(uint8_t *buffer)
{
    if (*(buffer) == 0xff && *(buffer + 1) == 0xd8 &&
        *(buffer + 2) == 0xff && (*(buffer + 3) & 0xf0) == 0xe0)
    {
        return true;
    }

    else
    {
        return false;
    }
}
