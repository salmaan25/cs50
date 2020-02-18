#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    int count = 0;
    FILE* inptr = fopen("card.raw", "r");
    //FILE* outptr = NULL;
    char bytes512[512];
    char bytes1024[1024];
    while(1)
    {
        fread(bytes512, 512 * sizeof(char), 1, inptr);
        if((bytes512[0] == (char)(0xff) && bytes512[1] == (char)(0xd8) && bytes512[2] == (char)(0xff)) && ((bytes512[3] == (char)(0xe0)) ||  bytes512[3] == (char)(0xe1)))
        {
            fseek(inptr, -1 * 512 * sizeof(char), SEEK_CUR);
            break;
        }
    }
    while(1)
    {
        char title[10];
        if(fread(bytes1024, 512 * sizeof(char), 2, inptr) == 1)
        {
            fseek(inptr, -1 * 512 * sizeof(char), SEEK_CUR);
            break;
        }
        fseek(inptr, -1 * 1024 * sizeof(char), SEEK_CUR);
        
        if((bytes512[0] == (char)(0xff) && bytes512[1] == (char)(0xd8) && bytes512[2] == (char)(0xff)) && ((bytes512[3] == (char)(0xe0)) ||  bytes512[3] == (char)(0xe1)))
        {
            sprintf(title, "%03d.jpg", count);
            //outptr = fopen(title, "w");
            count++;
        }
        FILE* outptr = fopen(title, "w");
        
        while(1)
        {
            fread(bytes512, 512 * sizeof(char), 1, inptr);
            fwrite(bytes512, 512 * sizeof(char), 1, outptr);
            
            fread(bytes512, 512 * sizeof(char), 1, inptr);
            
            if((bytes512[0] == (char)(0xff) && bytes512[1] == (char)(0xd8) && bytes512[2] == (char)(0xff)) && ((bytes512[3] == (char)(0xe0)) ||  bytes512[3] == (char)(0xe1)))
            {
                fseek(inptr, -1 * 512 * sizeof(char), SEEK_CUR);
                fclose(outptr);
                break;
            }
            
            fseek(inptr, -1 * 512 * sizeof(char), SEEK_CUR);
                
            if(fread(bytes1024, 512 * sizeof(char), 2, inptr) == 1)
            {
                fseek(inptr, -1 * 512 * sizeof(char), SEEK_CUR);
                break;
            }
            fseek(inptr, -1 * 1024 * sizeof(char), SEEK_CUR);
        }
        if(fread(bytes1024, 512 * sizeof(char), 2, inptr) == 1)
        {
            fseek(inptr, -1 * 512 * sizeof(char), SEEK_CUR);
            break;
        }
        fseek(inptr, -1 * 1024 * sizeof(char), SEEK_CUR);
    }
}
