/*
MIT License
Copyright (c) 2019 Jesus A. Diaz
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "lib/istdas.h"

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
            fprintf(fOut,"\t\t\x22");
            fprintf(fOut,"char_value\x22:\x22");
            if(dataBuffer > 32)
            {
                fprintf(fOut,"%c",dataBuffer);
            }
            else
            {
                switch(dataBuffer)
                {
                case 0:
                    fprintf(fOut,"NUL");
                    break;
                case 1:
                    fprintf(fOut,"SOH");
                    break;
                case 2:
                    fprintf(fOut,"STX");
                    break;
                case 3:
                    fprintf(fOut,"ETX");
                    break;
                case 4:
                    fprintf(fOut,"ENT");
                    break;
                case 5:
                    fprintf(fOut,"ENQ");
                    break;
                case 6:
                    fprintf(fOut,"ACK");
                    break;
                case 7:
                    fprintf(fOut,"BEL");
                    break;
                case 8:
                    fprintf(fOut,"BS");
                    break;
                case 9:
                    fprintf(fOut,"TAB");
                    break;
                case 10:
                    fprintf(fOut,"LF");
                    break;
                case 11:
                    fprintf(fOut,"VT");
                    break;
                case 12:
                    fprintf(fOut,"FF");
                    break;
                case 13:
                    fprintf(fOut,"CR");
                    break;
                case 14:
                    fprintf(fOut,"SO");
                    break;
                case 15:
                    fprintf(fOut,"SI");
                    break;
                case 16:
                    fprintf(fOut,"DLE");
                    break;
                case 17:
                    fprintf(fOut,"DC1");
                    break;
                case 18:
                    fprintf(fOut,"DC2");
                    break;
                case 19:
                    fprintf(fOut,"DC3");
                    break;
                case 20:
                    fprintf(fOut,"DC4");
                    break;
                case 21:
                    fprintf(fOut,"NAK");
                    break;
                case 22:
                    fprintf(fOut,"SYN");
                    break;
                case 23:
                    fprintf(fOut,"ETB");
                    break;
                case 24:
                    fprintf(fOut,"CAN");
                    break;
                case 25:
                    fprintf(fOut,"EM");
                    break;
                case 26:
                    fprintf(fOut,"SUB");
                    break;
                case 27:
                    fprintf(fOut,"ESC");
                    break;
                case 28:
                    fprintf(fOut,"FS");
                    break;
                case 29:
                    fprintf(fOut,"GS");
                    break;
                case 30:
                    fprintf(fOut,"RS");
                    break;
                case 31:
                    fprintf(fOut,"US");
                    break;
                }
            }
            fprintf(fOut,"\x22\n");
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
