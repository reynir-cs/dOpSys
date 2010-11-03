#include <stdio.h>
#include "redirect.h"

int main(void) {
  puts("Executing cat in foreground with opgave2test.c as infile");
  char *argv1[] = {"cat", NULL};
  redirect_stdincmd(argv1[0], argv1, "opgave2test.c");

  puts("Executing echo in foreground with test.txt as outfile");
  char *argv2[] = {"echo", "test", NULL};
  redirect_stdoutcmd(argv2[0], argv2, "test.txt");

  return 0;
}
