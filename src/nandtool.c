/*
	Superleaf1995: please have a processor capable of using nanoseconds
	otherwise all this will be useless
	
	Compile like this:
		gcc -Wall -Wextra -ansi -pedantic -lrt -lm nandtool.c -o nandtool
*/

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char ** argv) {
	int fd;
	FILE * fp;
	
	size_t i;
	
	ssize_t r;
	
	/* Tempbuffer for NAND reads */
	unsigned char * tempbuf;
	
	long double * cells_deg;
	size_t j;
	
	/* Timeval struct dynarrays */
	struct timespec start;
	struct timespec end;
	
	/* Size of buffer */
	size_t bufsize = 8192;
	
	/* Number of cells to take in account for average
	calculation */
	size_t n_average_calc = 4096;
	
	/* Number of cells to probe of the NAND for degeneration */
	size_t n_probe = 4096;
	
	/* The median time (in ms) for a single access of a cell */
	size_t average_time;
	
	if(argc < 1) {
		printf("Give [devpath] and optionaly with [outfile] so this works\n");
		return 1;
	}
	
	tempbuf = malloc(bufsize);
	if(tempbuf == NULL) {
		return 1;
	}
	
	printf("Opening %s\n",argv[1]);
	
	fd = open(argv[1],O_RDONLY);
	
	/* Get timing records */
	average_time = 0;
	for(i = 0; i < n_average_calc; i++) {
		clock_gettime(CLOCK_MONOTONIC,&start);
		r = read(fd,tempbuf,1);
		if(r == 0) {
			return 1;
		}
		clock_gettime(CLOCK_MONOTONIC,&end);
		average_time += (end.tv_nsec-start.tv_nsec);
	}
	
	/* Obtain the average timing for read access */
	average_time /= n_average_calc;
	
	printf("Average reading took %lu nanoseconds\n",average_time);
	
	cells_deg = malloc(sizeof(long double)*n_probe);
	if(cells_deg == NULL) {
		return 1;
	}
	
	for(i = 0; i < n_probe; i++) {
		cells_deg[i] = 0.0f;
	}
	
	/* Find degenerated cells */
	for(j = 0; j < 128; j++) {
		lseek(fd,SEEK_SET,0);
		for(i = 0; i < n_probe; i++) {
			size_t took;
			
			clock_gettime(CLOCK_MONOTONIC,&start);
			r = read(fd,tempbuf,1);
			if(r == 0) {
				break;
			}
			clock_gettime(CLOCK_MONOTONIC,&end);
			
			took = (end.tv_nsec-start.tv_nsec);
			
			if(took >= average_time) {
				cells_deg[i] += 0.1f;
			}
		}
	}
	
	/* Write data to file */
	if(argc == 2) {
		fp = fopen(argv[2],"wt");
		for(i = 0; i < n_probe; i++) {
			fprintf(fp,"%lu::%4.2Lf\n",i,cells_deg[i]);
		}
		fclose(fp);
		
		printf("Data written to %s\n",argv[2]);
	}
	
	free(cells_deg);
	
	/* Destroy everything and then end */
	close(fd);
	free(tempbuf);
	return 0;
}
