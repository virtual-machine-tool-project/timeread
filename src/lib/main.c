#include <stdio.h>
#include <stdlib.h>

FILE *fIn;
FILE *fOut;

int dataBuffer;
unsigned int offset;

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Usage: -inputfile -outputfile\n");
        return 0;
    }
    if(argc > 3)
    {
        printf("Too many arguments supplied\n");
        return 0;
    }
    offset = 1;
    fIn = fopen(argv[1],"rb");
    fOut = fopen(argv[2],"wb");
    fprintf(fOut,"{\n");
    // For every read char make a registry
    while(dataBuffer != EOF)
    {
        // wrtie
        if(offset < 2)
        {
            dataBuffer = getc(fIn);
            offset++;
        }
        else
        {
            fprintf(fOut,"\t\x22%u\x22\n",offset-2);
            fprintf(fOut,"\t{\n");
            fprintf(fOut,"\t\t\x22");
            fprintf(fOut,"hex_value\x22:0x%X\n",dataBuffer);
            fprintf(fOut,"\t\t\x22");
            fprintf(fOut,"numeric_value\x22:%d\n",dataBuffer);
            if(dataBuffer > 32)
            {
                fprintf(fOut,"\t\t\x22");
                fprintf(fOut,"char_value\x22:\x22%c\x22\n",dataBuffer);
            }
            fprintf(fOut,"\t}\n");
            // read
            dataBuffer = getc(fIn);
            offset++;
        }
    }
    fprintf(fOut,"}");
    fclose(fIn);
    fclose(fOut);
    printf("Finished\n");
    return 0;
}
