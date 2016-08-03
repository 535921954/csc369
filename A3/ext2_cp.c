/* ext2_cp: This program takes three command line arguments. The first
is the name of an ext2 formatted virtual disk. The second is the path
to a file on your native operating system, and the third is an
absolute path on your ext2 formatted disk. The program should work
like cp, copying the file on your native file system onto the
specified location on the disk. If the specified file or target
location does not exist, then your program should return the appropriate
error (ENOENT). Please read the specifications of ext2 carefully, some
things you will not need to worry about (like permissions, gid, uid, etc.),
while setting other information in the inodes may be important
(e.g., i_dtime). */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char **argv) {
	unsigned char *disk;
	if(argc != 4) {
        fprintf(stderr, "please enter correct number of arguments\n");
        exit(1);
    }
	int fd = open(argv[1], O_RDWR);
	disk = mmap(NULL, 128 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(disk == MAP_FAILED) {
		printf("disk invaild\n");
		perror("mmap");
		exit(1);
    }
  int cp_file = open(argv[2], O_RDONLY);
	if (cp_file < 0) {
		perror("Error");
		exit(1);
	}
  return 0;
}
