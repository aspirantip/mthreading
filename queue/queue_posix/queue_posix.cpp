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
	struct mq_attr attr;
	attr.mq_flags = O_CREAT | O_RDONLY;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 100;
	attr.mq_curmsgs = 10;
/*
	int st_unl = mq_unlink( "/test.mq" );
	if (st_unl == -1){
		std::cout << "[error | un_link] " << strerror( errno ) << std::endl;
		return 0;
}
*/


    mqd_t mq_id = mq_open( "/test.mq", O_CREAT | O_RDONLY, 0666, &attr );
    if (mq_id == -1){
        std::cout << "[error | mq_open] " << strerror( errno ) << std::endl;
        return 0;
    }
	printf("message queue ID = %d\n", mq_id);
//    std::cout << "message queue ID = " << mq_id << std::endl;

    //receive message
    // ==========================================
    char buff[100];
	printf("wait message ....\n");
//    std::cout << "wait message ...";
    int sz_buff = mq_receive ( mq_id, buff, 8192, NULL);
    if (sz_buff == -1){
        std::cout << "[error | mq_receive] " << strerror( errno ) << std::endl;
        return 0;
    }
    printf("received %d bytes\n", sz_buff);
    printf("text of message: %s \n", buff);


    // write to file
    // ==========================================

    FILE *p_file;
    p_file = fopen("/home/box/message.txt", "w");
    if (p_file != NULL){
        fwrite(buff, sizeof(char), sz_buff, p_file);
        fclose( p_file);
    }
    else {
        std::cout << "[error | fopen] " << strerror ( errno ) << std::endl;

    }



    //close queue
    // ==========================================
    int st_close = mq_close( mq_id );
    if (st_close == -1){
        std::cout << "[error | mq_close] " << strerror( errno ) << std::endl;
        return 0;
    }

    int st_unlink = mq_unlink( "/test.mq" );
    if (st_unlink == -1){
        std::cout << "[error | mq_unlink] " << strerror( errno ) << std::endl;
        return 0;
    }



    cout << "finish ...\n";
    return 0;
}
