/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int calcPadding (int width, int sizeRGBTRIPLE);
int padding;
fpos_t position;

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // saves factor
    int factor = atoi(argv[1]);

    
    // ensure that the number provided is valid
    if ((factor < 0) || (factor > 100))
    {
        printf("Usage: The number should be between 1 and 100\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    bf.bfSize = 54 + ((bi.biWidth * factor) * sizeof(RGBTRIPLE) + calcPadding((bi.biWidth * factor), sizeof(RGBTRIPLE))) * abs(bi.biHeight * factor);
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    long oldHeight = bi.biHeight;
    long oldWidth = bi.biWidth;
    bi.biWidth = bi.biWidth * factor;
    bi.biHeight = bi.biHeight * factor;
    
    // get biSizeImage. If biHeight is negative, if turns positve
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + calcPadding(bi.biWidth, sizeof(RGBTRIPLE))) * abs(bi.biHeight);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // determine padding for old image
    int pad =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // remembers line     
    int bytesLine = (sizeof(RGBTRIPLE) * oldWidth) + pad;
    

    // iterate over infile's scanlines
    for (int i = 0; i < abs(oldHeight); i++)
    {
        // get pointer
        fgetpos(inptr, &position);
        
        // repeat times factor
        for (int a = 0; a < factor; a ++) {
        
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int px = 0; px < factor; px ++) {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, pad, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }

        // reset pointer
        fsetpos(inptr, &position);
        
        }
        
        // advance pointer
        fseek(inptr, bytesLine, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

    // determine padding for scanlines
    int calcPadding (int width, int sizeRGBTRIPLE) {
        padding = (4 - (width * sizeRGBTRIPLE) % 4) % 4;
        return padding;
    }
