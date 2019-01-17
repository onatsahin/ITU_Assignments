Compiling the program:

gcc main.c -o tidy_html -Wall -ansi -std=c99 -g -ggdb -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -lfuse -I/usr/include/tidy -ltidy


Runnig the executable:

./tidy_html <website directory> <mountpoint>

Also run 

./tidy_html -h for help.
