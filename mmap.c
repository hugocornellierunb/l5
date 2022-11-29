/*
   mmap.c
   COMP 3413 Operating Systems

   An example of memory mapping - a type of IPC
   whereby a process maps a file into its memory
   space. The file may be read and written directly,
   without reading its contents into local storage
   first. Unrelated processes may also map the same
   file for use in IPC (though this is not shown
   in this example).

   This program assumes the existence of a file
   called "mmap.txt" in the same directory.

   to compile: gcc -lrt mmap.c
*/

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>           /* For O_* constants */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define BUFSIZE 81
char syscmd[80];

char *name = "mmap.txt";
int oflag = O_RDONLY;
int fd;
mode_t mode = 0444;
int prot = PROT_READ;
int flags = MAP_SHARED;
void *mapped_file = NULL;

int main(){
  fd = open(name, oflag, mode);
  printf("fd = %d\n", fd);
  if(fd == -1){
    printf("open return error code %d.\n", errno);
    exit(0);
  }
  mapped_file = mmap(0, BUFSIZE, prot, flags, fd, 0);
  if((long)mapped_file == -1){
    printf("mmap returned error code %d\n", errno);
    exit(0);
  }
  sprintf(syscmd, "pmap -x %d", getpid());
  system(syscmd);
  printf("%s\n", (char *)mapped_file);
  close(fd);
  munmap(mapped_file, BUFSIZE);
  printf("\nEnd of processing.\n");
  return 0;
}// main
