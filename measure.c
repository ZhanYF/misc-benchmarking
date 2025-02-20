#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int SAMPLE = 1000;  // sync with libvmm. 1000 sample * 2 record per sample
int DELAY  = 15000; // delay in microsec

void end(void)
{
    // quick: reture as soon as possible
    off_t offset = strtoul("0x1ff400000", NULL, 0);
    size_t len = 1;
    size_t pagesize = sysconf(_SC_PAGE_SIZE);
    off_t page_base = (offset / pagesize) * pagesize;
    off_t page_offset = offset - page_base;

    int fd = open("/dev/mem", O_SYNC);
    volatile unsigned char *mem = mmap(NULL, page_offset + len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, page_base);
    printf("", (int)mem[page_offset + 1]);
}

void init_clean(void)
{
    // clean: reset counter and record pointer
    off_t offset = strtoul("0x1ff300000", NULL, 0);
    size_t len = 1;
    size_t pagesize = sysconf(_SC_PAGE_SIZE);
    off_t page_base = (offset / pagesize) * pagesize;
    off_t page_offset = offset - page_base;

    int fd = open("/dev/mem", O_SYNC);
    volatile unsigned char *mem = mmap(NULL, page_offset + len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, page_base);
    printf("", (int)mem[page_offset + 1]);
}

int main(int argc, char *argv[]) {
    sleep(5); // wait for linux to stablize
    init_clean();
    off_t offset = strtoul("0x1ff100000", NULL, 0);
    size_t len = 1;
    size_t pagesize = sysconf(_SC_PAGE_SIZE);
    off_t page_base = (offset / pagesize) * pagesize;
    off_t page_offset = offset - page_base;


    volatile int fd = open("/dev/mem", O_SYNC);
    volatile unsigned char *mem = mmap(NULL, page_offset + len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, page_base);
for (int i=0; i<SAMPLE; i++) {
      uint64_t r;
      asm volatile("mrs %0,  PMCCNTR_EL0" : "=r" (r));
      printf("", (volatile int)mem[page_offset + 1]);
      printf("counter from VM: %llu\n", r);
      usleep(DELAY);
}
    end(); // fault one more time to trigger print
    return 0;
}
