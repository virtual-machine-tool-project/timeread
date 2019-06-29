/*Gets data from memory
By Jesus A. Diaz*/

#include <stdio.h>
#include <stdlib.h>
#ifndef __TURBOC__
#include <stdint.h>
#endif
#include <limits.h>
#include <string.h>

FILE *fp;

char * a;
// We dont know what we are touching!
void * ptr;
volatile unsigned char * samPtr = (volatile unsigned char *)0x408088;
// Use the widest type
uint64_t counter;
uint64_t baseAddr;
uint64_t finalAddr;

char mode;

char * width[8] =
{
    "-byte","-word","-dword","-qword"
};

int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("Usage: %s [base address] [final address]",argv[0]);
        return 0;
    }
    *samPtr = 1;
    baseAddr = strtoll(argv[1],NULL,16);
    finalAddr = strtoll(argv[2],NULL,16);
    printf("Sample address: [0x%lx]\n",(long unsigned int)samPtr);
    printf("From:           [0x%lX]\n",(long unsigned int)baseAddr);
    printf("To:             [0x%lX]\n",(long unsigned int)finalAddr);
    fp = fopen("out.dat","wb");
    for(counter = baseAddr; counter < finalAddr; counter++)
    {
        ptr = counter;
        fwrite(ptr,1,1,fp);
    }
    fclose(fp);
    return 0;
}
