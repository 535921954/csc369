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
