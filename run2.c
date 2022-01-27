#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <time.h>

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

int simple_read(int fd, int block_size, int block_count){

    unsigned int *buf = (unsigned int *)malloc((block_size));
    unsigned int xorcumulate = 0; 
    int count = 0;
    int n = 0;

    while ((n = read(fd, buf, block_size)) > 0){

        if (count == block_count){
        break;
        }

        count = count+1;
        
    }

    // free(buf);
    return count;
}


int measure_read(int fd, int block_size){

  double time_count = 0.00 ;
  int block_count = 1;
  time_t rb, ra;
  int max_block_count;

  while (time_count < 5.00){
    time(&rb);  
    max_block_count = simple_read(fd, block_size, block_count);
    time(&ra);
    time_count = difftime(ra, rb);
    block_count=block_count*2;
  }

  unsigned int b_read = max_block_count*block_size;
  printf("No. of blocks read for block size %d ==> %d \n", block_size, max_block_count);
  printf("Size of file read ==> %i Bytes \n", b_read);  
  printf("Time Taken ==> %.2f Seconds\n", time_count);
  return max_block_count;
}


int main(int argc, char *argv[]) {
 
  int fd;
  int b_count;

  if (argc > 1) {
    fd = open(argv[1],O_RDONLY);
    b_count = measure_read(fd, atoi(argv[2]));
  }
  return 0;
}