#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

// A simple program, which takes in input from child process and send its output to a parent process
int main()
{
    int fd1[2];
    if (pipe(fd1)==-1)
    {
        printf("Pipe Failed" );
        return 1;
    }

    int cpid = fork();

    if (cpid < 0)
    {
        printf("fork Failed" );
        return 1;
    }
    if (cpid ==0 )
    {
      char input_str[100];
      printf("Enter a string:");
      scanf("%[^\n]s", input_str);
      write(fd1[1], input_str, strlen(input_str)+1);
      close(fd1[1]);
      exit(0);
    }
    else
    {
      wait(NULL);
      char output_str[100];
      read(fd1[0], output_str, 100);
      printf("From Child Process: %s\n", output_str);
      close(fd1[0]);

    }
}
