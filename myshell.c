#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

int main(void)
{
    close(2);
    dup(1);
    char command[BUFFER_SIZE];
    char* pch;
    char* argv[BUFFER_SIZE];
    int length = 0;
    int i = 0;
    int isBackground = 0;
    pid_t pid;
    while (1)
    {
        i = 0;
        fprintf(stdout, "my-shell> ");
        memset(command, 0, BUFFER_SIZE);
        fgets(command, BUFFER_SIZE, stdin);

        printf(" pid is %d \n",pid);

        if(strncmp(command, "exit", 4) == 0)
        {
            break;
        }

        pch  = strtok(command, " \n");
        while(pch != NULL){
        argv[i] = pch;
        i++;
//        printf("%s \n", pch);
        pch = strtok(NULL, " \n");
        }
        if(strcmp(argv[i-1],"&") == 0) {
            isBackground = 1;
            argv[i-1] = NULL;
        }
        else isBackground = 0;

        argv[i] = NULL;
        length = i;

//        for(i=0; i<length; i++){
//            printf("%s \n", argv[i]);
//        }

        pch = argv[0];


 
// test if for status
waitpid(pid,NULL,0);


/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * when 'execv' add printf "my pid and fathers' pid"
 * google about execv what exactly it executes
 */


        if ((pid = fork()) < 0) {
            printf("*** ERROR: forking child process failed\n");
            exit(1);
        }
        else if (pid == 0) { // child process

                if (execvp(pch,argv) < 0) {
                    printf("*** ERROR: exec failed\n");
                    exit(1);
                }

        } else { // parent
            if(isBackground==0)
            wait(NULL);

        }






    }

    return 0;
}
