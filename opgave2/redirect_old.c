/* 

   Opgave 2

   redirect.c

 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "redirect.h"

/* 
 * redirect!
 * 
 * @ filename The name of the file to be executed
 * @ argv The arguments to the thread
 * @ IOfilename The file to redirect to/from
 * @ flags The flags for open, ie. O_RDONLY
 * @ stdio The stream to redirect to/from
 */
void redirect(char *filename, char *argv[], 
	      char *IOfilename, int flags, int stdio) {
  pid_t pid = fork();
  
  if (pid == 0) {
    int fid = open(IOfilename, flags);
    dup2(fid, stdio);

    execvp(filename, argv);
  }
  else if (pid != -1) {
    waitpid(pid, NULL, 0);
  }
}

int redirect_stdincmd(char *filename, char *argv[], char *infilename) {
  redirect(filename, argv, infilename, O_RDONLY, 0);

  return 0;
}

int redirect_stdoutcmd(char *filename, char *argv[], char *outfilename) {
  pid_t pid = fork();

  if (pid == 0) {
    int fid = open(outfilename, O_WRONLY | O_CREAT);
    dup2(fid, 1);

    execvp(filename, argv);
  }
  else if (pid != -1) {
    waitpid(pid, NULL, 0);
  }

  return 0;
}
