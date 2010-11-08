/**
 * dosh.c
 *
 * vim:shiftwidth=2
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "forback.h"
#include "redirect.h"

/* --- symbolic constants --- */
#define HOSTNAMEMAX 100
#define COMMANDMAX 500
#define MAXARGUMENTS 25

/* --- shell commands --- */
typedef enum _cmdtype {FOREGROUNDCMD = 1, 
  BACKGROUNDCMD,
  STDOUTREDIRECT,
  STDINREDIRECT } cmdtype;

typedef struct _shellcmd {
  int type;
  char *filename1;
  char *arguments1[MAXARGUMENTS]; 
  char argcount1;
  char *filename2;
} Shellcmd;


/* --- print a shell command --- */
void printshellcmd(Shellcmd *shellcmd)
{
  int i = 0;

  printf("Type      : %d\n", shellcmd->type);
  printf("Filename1 : %s\n", shellcmd->filename1);
  printf("Arguments : %d\n", shellcmd->argcount1);

  while (i < shellcmd->argcount1) {
    printf("Argument %d: %s\n", i, (shellcmd->arguments1)[i]);
    i++;
  }

  if (shellcmd->filename2)
    printf("filename 2: %s\n", shellcmd->filename2);
}

/* --- use the /proc filesystem to obtain the hostname --- */
char *gethostname(char *hostname)
{
  FILE *hostnamefile;

  hostnamefile = fopen ("/proc/sys/kernel/hostname", "r");

  if (fgets(hostname, HOSTNAMEMAX, hostnamefile) == NULL) {
    hostname = NULL;
  } /* --- remove the newline --- */
  else
    hostname[strlen(hostname)-1] = '\0';

  fclose(hostnamefile);

  return hostname;
}

/* --- parse the commandline and build shell commmand structure --- */
int parsecommand(char *commandline, Shellcmd *shellcmd)
{
  char *token;
  int cont = 1;
  int argcount = 0;

  /* obtain the filename */
  token = strtok(commandline, " \t\n");

  if (token == NULL)
    return 0;

  /* we have a command */
  shellcmd->filename1 = token;
  shellcmd->type = FOREGROUNDCMD; /* assume foreground command */

  /* obtain the command line arguments for filename 1 */
  token = strtok(NULL, " \t\n");

  (shellcmd->arguments1)[0] = shellcmd->filename1;
  argcount = 1;

  while ((token != NULL) && cont) {
    /* assume only one &,> or < in commandline if any */
    if (strcmp(token, "&") == 0) {
      shellcmd->type = BACKGROUNDCMD;
      break;
    }
    else if (strcmp(token,">") == 0) {
      shellcmd->type = STDOUTREDIRECT;
      break;
    }
    else if (strcmp(token,"<") == 0) {
      shellcmd->type = STDINREDIRECT;
      break;
    }
    else {
      (shellcmd->arguments1)[argcount] = token;
      argcount++;
    }

    /* read the next token */
    token = strtok(NULL, " \t\n");
  }

  /* set argcount and end of arguments */
  shellcmd->argcount1 = argcount;
  (shellcmd->arguments1)[argcount] = NULL;

  /* read remaining arguments depending on type */
  token = strtok(NULL, " \t\n");

  shellcmd->filename2 = NULL;

  switch (shellcmd->type)
  {
    case STDOUTREDIRECT:
    case STDINREDIRECT:
      if (token == NULL)
        return 0; /* illegal command - filename required */
      else {
        shellcmd->filename2 = token;
      }
      break;
    default:
      break;
  }      

  return 1;
}

/* --- execute a shell command --- */
int executecommand (Shellcmd *shellcmd)
{
  printshellcmd(shellcmd);

  if (strcmp(shellcmd->filename1, "exit") == 0)
    return 1;

  /* Execute! */
  switch (shellcmd->type) {
    case FOREGROUNDCMD:
      foregroundcmd(shellcmd->filename1, shellcmd->arguments1);
      break;
    case BACKGROUNDCMD:
      backgroundcmd(shellcmd->filename1, shellcmd->arguments1);
      break;
    case STDOUTREDIRECT:
      redirect_stdoutcmd(shellcmd->filename1, shellcmd->arguments1,
          shellcmd->filename2);
      break;
    case STDINREDIRECT:
      redirect_stdincmd(shellcmd->filename1, shellcmd->arguments1,
          shellcmd->filename2);
      break;
  }
  return 0;
}

/* --- main loop of the simple shell --- */
int main(int argc, char* argv[])
{
  /* initialise the shell */
  char commandline[COMMANDMAX];
  char hostname[HOSTNAMEMAX];

  int terminate = 0;
  Shellcmd shellcmd;

  if (gethostname(hostname)) {
    /* loop until control-D */
    while(!terminate) {
      printf("dosh-%s>>", hostname);
      if (fgets(commandline, COMMANDMAX, stdin) == NULL)
        terminate = 1;
      else {
        if (parsecommand(commandline, &shellcmd))
          terminate = executecommand(&shellcmd);
      }
    }
  }

  printf("\n");

  return 0;
}

