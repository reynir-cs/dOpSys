#include <stdio.h>
#include "forback.h"

int main(void) {
  puts("Start Emacs in foreground");
  char *argv1[] = {"emacs", NULL};
  foregroundcmd("emacs", argv1);

  puts("Start Emacs in background");
  char *argv2[] = {"emacs", NULL};
  backgroundcmd("emacs", argv2);

  puts("Start 'echo 10' in foregroundcmd");
  char *argv3[] = {"echo", "10", NULL};
  foregroundcmd("echo", argv3);

  puts("Start 'echo 10' in backgroundcmd");
  char *argv4[] = {"echo", "10", NULL};
  backgroundcmd("echo", argv4);
  
  return 0;
}
