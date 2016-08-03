/* ext2_rm: This program takes two command line arguments.
The first is the name of an ext2 formatted virtual disk,
and the second is an absolute path to a file or link (not a directory)
on that disk. The program should work like rm, removing the specified
file from the disk. If the file does not exist or if it is a directory,
then your program should return the appropriate error. Once again,
please read the specifications of ext2 carefully, to figure out what
needs to actually happen when a file or link is removed
(e.g., no need to zero out data blocks, must set i_dtime in the inode,
removing a directory entry need not shift the directory entries after
the one being deleted, etc.).

Bonus(5% extra): Implement an additional "-r" flag
(after the disk image argument), which allows removing directories
as well. In this case, you will have to recursively remove all the
contents of the directory specified in the last argument. If "-r" is
used with a regular file or link, then it should be ignored
(the ext2_rm operation should be carried out as if the flag had
not been entered). If you decide to do the bonus, make sure first
that your ext2_rm works, then create a new copy of it and rename
it to ext2_rm_bonus.c, and implement the additional functionality
in this separate source file. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "ext2.h"

int main(int argc, char **argv) {
  return 0;
}
