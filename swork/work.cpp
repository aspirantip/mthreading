#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>

int main(int argc, char **argv)
{
    int sv[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, sv);

    if ( !fork() ){     // child process
        close(sv[0]);
        printf("Child PID = %i\n", getpid());
        pause();
    }
    else{               // parent process
        close(sv[1]);
        printf("Parent PID = %i\n", getpid());
        wait(NULL);
        pause();
    }

    return 0;
}
