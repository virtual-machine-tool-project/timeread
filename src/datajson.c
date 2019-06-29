/*Gets data from file and transforms it into an structured
- HTML
- JSON
By Jesus A. Diaz*/

#include <stdio.h>
#include <stdlib.h>
#ifndef __TURBOC__
#include <stdint.h>
#endif
#include <string.h>
#include "lib/istdas.h"

FILE *fIn;
FILE *fOut;

byte dataBuffer;
byte * secondBuffer;
byte textSignal;

#ifndef __TURBOC__
uint32_t sizeOfFile;
uint32_t offset, sOffset, numNot;
#endif
#ifdef __TURBOC__
long long int sizeOfFile,offset,sOffset,numNot;
#endif
unsigned int i;
char * coCo[32] =
{
    "NUL","SOH","STX","ETX","ENT","ENQ","ACK","BEL","BS","TAB","LF","VT","FF","CR","SO","SI","DLE",
    "DC1","DC2","DC3","DC4","NAK","SYN","ETB","CAN","EM","SUB","ESC","FS","GS","RS","US"
};
char * format[8] =
{
    "-json","-html"
};

int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        printf("Usage: [inputfile] [format]\n");
        return -2;
    }
    offset = 1;
    fIn = fopen(argv[1],"rb");
    if(!fIn)
    {
        return -3;
    }
    printf("Writing file head\n");
    secondBuffer = malloc(4096);
    if(secondBuffer == NULL)
    {
        return -1;
    }
    sizeOfFile = 0;
    while(getc(fIn) != EOF)
    {
        sizeOfFile++;
    }
    if(fseek(fIn,0,SEEK_SET) != 0)
    {
        return -4;
    }
    textSignal = 0;
    // JSON
    if(strcmp(format[0],argv[2]) == 0)
    {
        fOut = fopen("out.json","wb");
        fprintf(fOut,"{\n");
        // For every read char make a registry
        while(offset < sizeOfFile+3)
        {
            // write
            if(offset < 2){ /*Do nothing*/ }
            else
            {
                fprintf(fOut,"\t\x22%u\x22\n",offset-2);
                fprintf(fOut,"\t{\n");
                fprintf(fOut,"\t\t\x22");
                fprintf(fOut,"hex_value\x22:0x%X\n",dataBuffer);
                fprintf(fOut,"\t\t\x22");
                fprintf(fOut,"numeric_value\x22:%d\n",dataBuffer);
                fprintf(fOut,"\t\t\x22");
                fprintf(fOut,"char_value\x22:\x22");
                if(dataBuffer > 32)
                {
                    fprintf(fOut,"%c",dataBuffer);
                }
                else
                {
                    for(i = 0; i < 32; i++)
                    {
                        if(dataBuffer == i)
                        {
                            fprintf(fOut,"%s",coCo[i]);
                        }
                    }
                }
                fprintf(fOut,"\x22\n");
                fprintf(fOut,"\t}\n");
                // read
            }
            printf("Writing %d registry entry of %d. (0x%x)\r",offset-2,sizeOfFile,dataBuffer);
            fread(&dataBuffer,1,1,fIn);
            offset++;
        }
        fprintf(fOut,"}");
    }
    // HTML
    if(strcmp(format[1],argv[2]) == 0)
    {
        fOut = fopen("out.html","wb");
        // HTML Head
        fprintf(fOut,"<html>\n\t<body>\n\t\t");
        fprintf(fOut,"\t<style>table, th, td {\n\t\tborder: 1px solid black;\n\t}\t</style>");
        // Table head
        fprintf(fOut,"<table>\n\t\t\t<tr>\n\t\t\t\t<td>Offset</td>\n\t\t\t\t<td>Hex Value</td>\n\t\t\t\t<td>Numeric Value</td>\n\t\t\t\t<td>Character</td>\n");
        // For every read char make a registry
        while(offset < sizeOfFile+3)
        {
            // write
            if(offset < 2){ /*Do nothing*/ }
            else
            {
                fprintf(fOut,"\t\t\t<tr>\n");
                fprintf(fOut,"\t\t\t\t<td>%u</td>\n",offset-2);
                fprintf(fOut,"\t\t\t\t<td>0x%X</td>\n",dataBuffer);
                fprintf(fOut,"\t\t\t\t<td>%d</td>\n",dataBuffer);
                fprintf(fOut,"\t\t\t\t<td>");
                if(dataBuffer > 32)
                {
                    fprintf(fOut,"%c",dataBuffer);
                }
                else
                {
                    for(i = 0; i < 32; i++)
                    {
                        if(dataBuffer == i)
                        {
                            fprintf(fOut,"%s",coCo[i]);
                        }
                    }
                }
                fprintf(fOut,"<td>\n");
                fprintf(fOut,"\t\t\t</tr>\n");
                // read
            }
            printf("Writing %d registry entry of %d. (0x%x)\r",offset-2,sizeOfFile,dataBuffer);
            fread(&dataBuffer,1,1,fIn);
            offset++;
        }
        fprintf(fOut,"}");
    }
    fclose(fIn);
    fclose(fOut);
    free(secondBuffer);
    printf("\nFinished\n");
    return 0;
}
