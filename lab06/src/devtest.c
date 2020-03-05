#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	unsigned int result, read_i, read_j;
	int fd;
	int i, j;
	char input = 0;
	int* mv = (int*)malloc(2 * sizeof(int));
	char* outs = (char*)malloc(3 * sizeof(int));
	int* intbuff; //used to convert from char* to int* buffer

	fd = open("/dev/multiplier", O_RDWR);
	
	//handle error opening file
	if (fd == -1) {
		printf("Failed to open device file!\n");
		return -1;
	}
	
	while (input != 'q') { 
		for (i = 0; i <= 16; i++) {
			for (j = 0; j <= 16; j++) {
				
				//Set values
				mv[0] = i;
				mv[1] = j;
				//Cast to character array
				char* buffer = (char*)mv; 
				
				write(fd, buffer, 2 * sizeof(int));
				read(fd, outs, 3 * sizeof(int));
				
				intbuff = (int*)outs;
				
				read_i = intbuff[0];
				read_j = intbuff[1];			
				result = intbuff[2];
				
				printf("%d * %d = %d\n", read_i, read_j, result);

				if (result == (i * j)) {
					printf("Result Correct!\n");
				}
				else {
					printf("Result Incorrect!\n");
				}
				//read from terminal
				input = getchar();
			}
		}
	}
	close(fd);
	free(mv);
	free(outs);
	return 0;
}
