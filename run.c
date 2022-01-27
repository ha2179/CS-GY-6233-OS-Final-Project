//Standard Libraries

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

    // unsigned int buf[block_size];
    unsigned int *buf = (unsigned int *)malloc((block_size));
    unsigned int xorcumulate = 0; 
    int count = 0;
    int n;

    while ((n = read(fd, buf, block_size)) > 0){
        xorcumulate ^= xorbuf(buf, n/4);

        if (count == block_count){
        break;
        }

        count = count+1;

        
    }

    return xorcumulate;
}

int simple_write(int fd, int block_size, int block_count){

    // unsigned int buf[block_size];
    unsigned int *buf = (unsigned int *)malloc((block_size));
    unsigned int xorcumulate = 0; 
    int count = 0;
    int n;

    while ((n = write(fd, buf, block_size)) > 0){
        // xorcumulate ^= xorbuf(buf, n/4);

        if (count == block_count){
        break;
        }
        count = count+1;

    }

    return count;
}


int main(int argc, char *argv[]) {
  int fd;
  int xor_final;

  if (argc > 1) {
    if (strcmp(argv[2],"-r") == 0){
        fd = open(argv[1],O_RDWR);
        time_t t1, t2;
        time(&t1);
        xor_final = simple_read(fd, atoi(argv[3]), atoi(argv[4]));
        time(&t2);
        printf("Time Taken to execute is %.2f seconds \n",difftime(t2, t1));
        printf("Calculated XOR for the input file is ==> %08x\n", xor_final);
        close(fd);
    }

    if (strcmp(argv[2],"-w") == 0){
        fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
        time_t t1, t2;
        time(&t1);
        int out_write = simple_write(fd, atoi(argv[3]), atoi(argv[4]));
        time(&t2);
        unsigned int write_byte_count = atoi(argv[3])*atoi(argv[4]);
        printf("\n Wrote file of size %i Bytes in %.2f Seconds", write_byte_count, difftime(t2, t1));
        close(fd);
    }
  }
  return 0;
}