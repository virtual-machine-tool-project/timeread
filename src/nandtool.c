/*
	Superleaf1995: please have a processor capable of using nanoseconds
	otherwise all this will be useless
	
	Compile like this:
		gcc -Wall -Wextra -ansi -pedantic -lrt -lm nandtool.c -o nandtool
*/

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/* Temporal byte storage*/
unsigned char temp;

long double * get_cell_degeneration(int fd, const size_t n_cells, const size_t average_time) {
	/* Timespecs for chrono */
	struct timespec start, end;
	/* Cells degeneration array */
	long double * cells_deg;
	/* Iterators */
	size_t j, i;
	int r;
	
	cells_deg = malloc(sizeof(long double)*n_cells);
	if(cells_deg == NULL) {
		return NULL;
	}
	
	/* Set all to zero */
	memset(cells_deg,0,n_cells);
	
	/* Find degenerated cells */
	for(j = 0; j < 128; j++) {
		lseek(fd,SEEK_SET,0);
		for(i = 0; i < n_cells; i++) {
			/* Time that the cell took to read */
			size_t took;
			
			clock_gettime(CLOCK_MONOTONIC,&start);
			r = read(fd,&temp,1);
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
	
	return cells_deg;
}

int get_average_time(int fd, const size_t n_cell) {
	/* Timespecs for chrono */
	struct timespec start, end;
	/* Result holder */
	ssize_t r;
	/* Variable representing average time to read a cell in seconds */
	size_t average_time;
	int i;
	
	/* Get timing records */
	average_time = 0;
	for(i = 0; i < n_cell; i++) {
		/* Start chrono */
		clock_gettime(CLOCK_MONOTONIC,&start);
		
		/* Read a single cell */
		r = read(fd,&temp,1);
		if(r == 0) { break; }
		
		/* End chrono, calulate time that took to read that cell */
		clock_gettime(CLOCK_MONOTONIC,&end);
		average_time += (end.tv_nsec-start.tv_nsec);
	}
	
	/* Divide by number of samples evaluated and voila!, we
	have average reading time */
	average_time /= i;
	
	/* Return our average time */
	return average_time;
}

int main(int argc, char ** argv) {
	int fd;
	FILE * fp;
	size_t i;
	int r;
	
	const char * devpath;
	const char * outpath;
	
	/* Number of cells to probe of the NAND for degeneration */
	size_t n_probe = 4096;
	
	/*
	-d [file] :: File to put degeneration on
	-e [numb] :: Number of cells to analyze
	-a [file] :: File where nand cells are exported (bytes)
	*/
	
	for(i = 1; i < argc; i++) {
		if(!strcmp(argv[i],"-d")) {
			long double * cells_deg;
			
			outpath = argv[i];
			
			i++;
			if(i >= argc) {
				printf("Specify file to put degeneration on\n");
				return 1;
			}
			
			fd = open(devpath,O_RDONLY);
			if(fd == -1) {
				perror("cannot use fd");
				return 1;
			}
			
			cells_deg = get_cell_degeneration(fd,n_probe,get_average_time(fd,n_probe));
			
			/* Write data to file */
			fp = fopen(outpath,"wt");
			for(i = 0; i < n_probe; i++) {
				fprintf(fp,"%lu::%4.2Lf\n",i,cells_deg[i]);
			}
			fclose(fp);
			printf("Data written to %s\n",outpath);
			
			free(cells_deg);
			
			/* Destroy everything and then end */
			close(fd);
		} else if(!strcmp(argv[i],"-e")) {
			i++;
			if(i >= argc) {
				printf("Specify number of cells to evaluate\n");
			}
			n_probe = atoi(argv[i]);
		} else if(!strcmp(argv[i],"-a")) {
			unsigned char * cells;
			
			outpath = argv[i];
			
			i++;
			if(i >= argc) {
				printf("Specify file to put array on\n");
				return 1;
			}
			
			fd = open(devpath,O_RDONLY);
			if(fd == -1) {
				perror("cannot use fd");
				return 1;
			}
			
			cells = malloc(n_probe+1);
			if(cells == NULL) {
				return 1;
			}
			
			/* Read a single cell */
			r = read(fd,&cells,1);
			if(r == 0) { break; }
			
			/* Write data to file */
			fp = fopen(outpath,"wb");
			for(i = 0; i < n_probe; i++) {
				fwrite(cells,sizeof(unsigned char),n_probe,fp);
			}
			fclose(fp);
			printf("Data written to %s\n",outpath);
			
			free(cells);
			
			/* Destroy everything and then end */
			close(fd);
		} else if(!strcmp(argv[i],"-dev")) {
			i++;
			if(i >= argc) {
				printf("Specify file to use device as\n");
				return 1;
			}
			
			devpath = argv[i];
			printf("Using %s as device\n",devpath);
		}
	}
	return 0;
}
