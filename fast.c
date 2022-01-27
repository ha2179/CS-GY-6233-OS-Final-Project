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

void simple_read(int fd, int block_size, unsigned int* xorcumulate, unsigned int* b_reads){

    // unsigned int buf[block_size];
    unsigned int *buf = (unsigned int *)malloc((block_size));
    // unsigned int *xorcumulate = 0; 
    int count = 0;
    int n;

    while ((n = read(fd, buf, block_size)) > 0){
        *xorcumulate ^= xorbuf(buf, n/4);

        // if (count == block_count){
        // break;
        // }

        count = count+1;

        
    }

    *b_reads = block_size*count;
}


int main(int argc, char *argv[]) {
  int fd;
  int xor_final;
  unsigned int xorcumulate = 0;
  unsigned int bytes_count;
  float timer;
  unsigned int optimal_block_size = 524288;

  if (argc > 0) {
      fd = open(argv[1],O_RDONLY);
      time_t t1, t2;
      time(&t1);
    //   xor_final = simple_read(fd, optimal_block_size);
      simple_read(fd, optimal_block_size, &xorcumulate, &bytes_count);
      time(&t2);
      timer = difftime(t2, t1);
      printf("Time Taken to execute is %.2f seconds \n",timer);
      printf("Calculated XOR for the input file is ==> %08x\n", xorcumulate);
      printf("Speed ==> %f MiB/s\n", (bytes_count/(1024*1024))/timer);

  }
  return 0;
}