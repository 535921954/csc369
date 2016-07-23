/* ext2_ln: This program takes three command line arguments.
The first is the name of an ext2 formatted virtual disk.
The other two are absolute paths on your ext2 formatted disk.
The program should work like ln, creating a link from the first
specified file to the second specified path. If the source file
does not exist (ENOENT), if the link name already exists (EEXIST),
or if either location refers to a directory (EISDIR), then your
program should return the appropriate error. Note that this
version of ln only works with files. Additionally, this command
may take a "-s" flag, after the disk image argument. When this
flag is used, your program must create a symlink instead (other
arguments remain the same). If in doubt about correct operation
of links, use the ext2 specs and ask on the discussion board. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char **argv) {
  return 0;
}
