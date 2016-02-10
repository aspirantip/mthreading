#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>


#include <errno.h>
#include <iostream>


using namespace std;


int main(int argc, char **argv){
    cout << "start ...\n";

    char mqd[] = "/test.mq";

    //creat queue
    // ==========================================
    mqd_t mq_id = mq_open( mqd, O_CREAT | O_RDONLY );
    if (mq_id == -1){
        std::cout << "[error | mq_open] " << strerror( errno ) << std::endl;
        return 0;
    }
    std::cout << "message queue ID = " << mq_id << std::endl;


    //receive message
    // ==========================================
    char *buff;
    std::cout << "wait message ...";
    int sz_buff = mq_receive ( mq_id, buff, 8192, NULL);
    if (sz_buff == -1){
        std::cout << "[error | mq_receive] " << strerror( errno ) << std::endl;
        return 0;
    }
    printf("received %d bytes\n", sz_buff);
    printf("text of message: %s \n", buff);


    // write to file
    // ==========================================
/*
    FILE *p_file;
    p_file = fopen("/home/box/message.txt", "w");
    if (p_file != NULL){
        fwrite(buff, sizeof(char), sz_buff, p_file);
        fclose( p_file);
    }
    else {
        std::cout << "[error | fopen] " << strerror ( errno ) << std::endl;

    }
*/


    //close queue
    // ==========================================
    int st_close = mq_close( mq_id );
    if (st_close == -1){
        std::cout << "[error | mq_close] " << strerror( errno ) << std::endl;
        return 0;
    }

    int st_unlink = mq_unlink( mqd );
    if (st_unlink == -1){
        std::cout << "[error | mq_unlink] " << strerror( errno ) << std::endl;
        return 0;
    }



    cout << "finish ...\n";
    return 0;
}
