/*
MIT License
Copyright (c) 2019 Alexander Hill
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
#include <dos.h>
#include <conio.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

FILE *fOut;
byte sOut;
signed char commandArg;
dword comPort;
byte comInp;
int comIntInp;
byte comChar;

int main(void)
{
	printf("\nSpecify COM port (1-4)");
	comInp = getch();
	if(comInp == '1')
	{
		comPort = 0x3F8;
	}
	if(comIntInp == '2')
	{
		comPort = 0x2F8;
	}
	else if(comInp == '3')
	{
		comPort = 0x3E8;
	}
	else if(comIntInp == '4')
	{
		comPort = 0x2E8;
	}
	else
	{
		printf("\nError 1");
		return -1;
	}
	printf("\nSelect mode (s) to send, (r) to receive");
	comInp = getch();
	if(comInp == 'S'||comInp == 's')
	{
		printf("\nSpecify char to send (in hex)");
		scanf("%x",&comInp);
		sOut = comInp;
		outportb(comPort,comChar);
		printf("\nSent data from COM port 0x%X",comPort);
	}
	else if(comInp == 'R'||comInp == 'r')
	{
		sOut = inportb(comPort);
		printf("\nReceived data from COM port 0x%X",comPort);
	}
	else
	{
		printf("\nError 2");
		return -2;
	}
	printf("\tHex Value: 0x%X",sOut);
	printf("\tDecimal Value: %d",sOut);
	printf("\nCharacter: (%c)",sOut);
	return 0;
}
