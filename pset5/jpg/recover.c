/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    // open input file 
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open card.raw");
        return 1;
    }
    
    // placeholder
    uint8_t nfile[512];
    int fileNumber = 0;
    char* fileName = NULL;
    
    // read infile until reaching the end
    while (fread(&nfile, sizeof(uint8_t), 512, inptr) == 512) {       
            // check for header              
            if ((*nfile == 0xff && *nfile+1 == 0xd8 && *nfile+2 == 0xff) && (*nfile+3 == 0xe0 || *nfile+3 == 0xe1)) {
                // create and open output file
                printf("Hello here");
                sprintf(fileName, "0%i.jpg", fileNumber);
                FILE* image = fopen(fileName, "a");
                if (image == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", fileName);
                    return 3;
                } else {
                        fwrite(&nfile, sizeof(uint8_t), 512, image);
                        fclose(image);
                        fileNumber++;
                        free(nfile);
                    }
            } else {
                free(nfile);
            }    
        }

    }

