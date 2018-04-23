#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char** argv){

    int pipefd[2];
    pipe(pipefd);
    fcntl(pipefd[0], F_SETFL, O_NONBLOCK);

    int n = 0;
    pid_t child_id = fork();
    while (1){
        int ppid = getppid();
        while (child_id == 0 && ppid == getppid()){
            int nbytes = read(pipefd[0], &n, sizeof(n));
            usleep(1000);
        }
        if (child_id == 0){
            //printf("Parent is dead\n");
            child_id = fork();
        }
        
        if (child_id != 0){

            printf("[%d]\t%d\n", getpid(), n);
            n++;

            write(pipefd[1], &n, sizeof(n));

            sleep(1);
        }
    }

    return 0;
}
