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

#ifndef ISTDAS_H
#define ISTDAS_H
#if defined (__TINY__)
#error Please use a larger model.
#endif
#include "istdas.c"

/*Base address - in BIOS data range*/
#define COM1_BASE_ADDRESS 0x00000400
#define COM2_BASE_ADDRESS 0x00000402
#define COM3_BASE_ADDRESS 0x00000404
#define COM4_BASE_ADDRESS 0x00000406
#define LPT1_BASE_ADDRESS 0x00000408
#define LPT2_BASE_ADDRESS 0x0000040A
#define LPT3_BASE_ADDRESS 0x0000040C
#define LPT4_BASE_ADDRESS 0x0000040E

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef unsigned long long qword;

typedef struct 

#endif
