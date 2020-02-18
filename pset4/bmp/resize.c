/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    int n = atoi(argv[1]);
    printf("%d\n", n);
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
    int paddinginp =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("%d\n%d\n%d\n%d\n%d\n", bf.bfSize, paddinginp, bi.biWidth, bi.biHeight, bi.biSizeImage);
    // write outfile's BITMAPFILEHEADER
    int paddingout =  (4 - (n * bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bf.bfSize =  (sizeof(RGBTRIPLE) * (n * n * (bi.biWidth)* (-1 * bi.biHeight))) + 54 + (paddingout * n * (-1 * bi.biHeight) * sizeof(RGBTRIPLE));
    printf("%d\n", bf.bfSize);
    
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    bi.biSizeImage = ((-1 * bi.biHeight * paddingout) + (bi.biWidth * -1 * bi.biHeight)) * 3; 
    // write outfile's BITMAPINFOHEADER 
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    RGBTRIPLE colors[n * (bi.biWidth)]; 
    printf("%d\n%d\n%d\n%d\n", paddingout, bi.biWidth, bi.biHeight, bi.biSizeImage);
    // determine padding for scanlines
    

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight) / n; i < biHeight; i++)
    {
        int count = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth / n; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            int k;
            for(k = 0; k < n; k++)
            {
                colors[k + n * count] = triple;
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            count += 1;
        }
        // skip over padding, if any
        fseek(inptr, paddinginp, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < paddingout; k++)
        {
            fputc(0x00, outptr);
        }


        int l;
        for(l = 0; l < n - 1; l++)
        {
            int m;
            for(m = 0; m < n * (bi.biWidth / n); m++)
            {
                fwrite(&colors[m], sizeof(RGBTRIPLE), 1, outptr);
            }
            for (int k = 0; k < paddingout; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
