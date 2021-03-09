#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {

   //This part checks the number of command line arguments
   if (argc < 2) {
        printf("Not enough command line arguments. Please try again.\n");
        exit(1);
    }

    int pid;
    int cid;
    pid = fork();

    if(pid == 0){
        printf("I am child_1 of %d and my pid is: %d\n", getppid(), getpid()); //This prints out the child2 pid and the pid of its parent
        execl("./func2","func2",argv[1],NULL); //This calls func2 which divides the number given via the command line by 2
    }
    else{
        cid = fork();
        if(cid == 0){
            sleep(2); //This provides a wait period to allow func2 to finish before executing the next two lines of code
            printf("I am child_2 of %d and my pid is: %d\n", getppid(), getpid()); //This prints out the child1 pid and the pid of its parent
            execl("./func1","func1",argv[1],NULL); //This calls func1 which multiplies the number given via the command line by 2
        }
        else{
            sleep(4); //this allows the program to wait 4 secs before printing the next line
            printf("I am the parent process with id %d\nAll of my good children have finished their work!\n",getpid()); //This prints out the parent pid
        }
    }

    return 0;
}

