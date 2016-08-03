/* This program takes two command line arguments. The first is the name
of an ext2 formatted virtual disk. The second is an absolute path on the
ext2 formatted disk. The program should work like ls -1 (that's number one
"1", not lowercase letter "L"), printing each directory entry on a separate
line. If the flag "-a" is specified (after the disk image argument), your
program should also print the . and .. entries. In other words, it will print
one line for every directory entry in the directory specified by the absolute
path. If the path does not exist, print "No such file or directory", and
return an ENOENT. Directories passed as the second argument may end in a
"/" - in such cases the contents of the last directory in the path
(before the "/") should be printed (as ls would do). Additionally, the path
(the last argument) may be a file or link. In this case, your program
should simply print the file/link name (if it exists) on a single line,
and refrain from printing the . and ... */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char **argv) {
	unsigned char *disk;
	if(argc != 3) {
        fprintf(stderr, "please enter correct number of arguments\n");
        exit(1);
    }
	int fd = open(argv[1], O_RDWR);
	disk = mmap(NULL, 128 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(disk == MAP_FAILED) {
		perror("mmap");
		exit(1);
    }
	
  return 0;
}
