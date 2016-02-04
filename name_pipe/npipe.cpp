/*
 * Задача на именованные каналы.
 * Напишите программу, которая создает два именованных канала - /home/box/in.fifo и /home/box/out.fifo
 * Пусть программа читает in.fifo и все прочитанное записывает в out.fifo.
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


using namespace std;

int main (int argc, char **argv)
{
    pid_t ppid = getpid();
    printf("Parent PID = %i\n", ppid);

    int in_fifo  = mkfifo("in.fifo", 0666);
    int out_fifo = mkfifo("out.fifo", 0666);

    const unsigned int size_bf = 512;
    char bf[size_bf];

    while ( int sz = read(in_fifo, bf, size_bf) ) {
        printf("Read: %s\n", bf);
        write( out_fifo, bf, sz );

        memset(bf, 0, 512);
    }


    close( in_fifo );
    close( out_fifo );

    return 0;
}
