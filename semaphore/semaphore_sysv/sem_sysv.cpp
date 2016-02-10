#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds* buf;
    unsigned short* array;
};

int main(int argc, char **argv)
{
    key_t key = ftok("/tmp/sem.temp", 1);
    union semun arg;

    int fd = semget(key, 16, IPC_CREAT | 0666);
    for(int i = 0; i < 16; i++)
    {
        arg.val = i;
        semctl(fd, i, SETVAL, arg);
    }

    return 0;
}
