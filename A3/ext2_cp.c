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
