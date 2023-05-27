#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define FIFO_NAME "RESP_PIPE_10230"
#define FIFO_OPEN "REQ_PIPE_10230"

int main(int argc, char** argv){
    int fd =-1;
    int fd2 = -1;


    if(mkfifo(FIFO_NAME,0666) != 0){
        perror("cannot create response pipe");
        return 1;
    }

    fd= open(FIFO_OPEN,O_RDWR);
    if(fd == -1){
        perror("ERROR\ncannot open request pipe");
        return 1;
    }
    fd2= open(FIFO_NAME,O_RDWR);
    if(fd2 == -1){
        perror("ERROR\ncannot open response pipe");
        return 1;
    }
    const char* requestMessage = "HELLO#";

   
    write(fd2, requestMessage, strlen(requestMessage));
    


    char request[250];
    
    while (1) {
    read(fd, request, 250);    
    if(strcmp("ECHO",strtok(request,"#"))==0){
        unsigned int x = 10230;
        write(fd2,"ECHO#",strlen("ECHO#"));
        write(fd2,&x,sizeof(x));
        write(fd2,"VARIANT#",strlen("VARIANT#"));
        break;
    }
    else{
        break;
    }
    }

    close(fd2);
    close(fd);
    
    unlink(FIFO_NAME);
    unlink(FIFO_OPEN);
  

    return 0;
}