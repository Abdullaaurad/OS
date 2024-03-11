#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];                                //not a Array but  file descriptors

    pid_t pipeId=pipe(fd);
    if(pipeId==-1) {                          //returns -1 if the pipe was a failure 0 if success
        printf("Failed pipe\n");
        return 1;
    } 
    
    pid_t id=fork();                          //creating fork to check the pipe
    if (id<0){
        printf("Failed fork\n");
        return 2;
    }

    if (id==0) {                               //child process
        close(fd[1]);                          //closes the write end of the pipe once closed can't open it 
        char y[20];
        read(fd[0], y, sizeof(y));
        printf("%s\n", y);
        close(fd[0]);                          //closes the read end of the pipe
    }
    else{                                        //parent process
        close(fd[0]);                          //closes the read end of the pipe
        char x[20] = "Hello, from parent";
        write(fd[1], x, sizeof(x));
        close(fd[1]);                          //closes the write end of the pipe
    }
    return 0;
}
