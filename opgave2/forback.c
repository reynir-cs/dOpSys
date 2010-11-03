/* 

   Opgave 1

   forback.c

 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "forback.h"

int startprocess(char *filename, char *argv[]) {
  int pid = fork();
  if (pid == 0) // I are child
    execvp(filename, argv);
  return pid;
}

/* start the program specified by filename with the arguments in argv 
   in a new process and wait for termination */
int foregroundcmd(char *filename, char *argv[]) {
  int pid = startprocess(filename, argv);
  waitpid(pid, NULL, 0);
  return 0;
}

/* start the program specified by filename with the arguments in argv 
   in a new process */
int backgroundcmd(char *filename, char *argv[]) {
  startprocess(filename, argv);
  return 0;
}
