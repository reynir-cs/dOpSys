/* 

Observation af kernetilstand 

dOpSys

*/

/* API for standard input/output */
#include <stdio.h>
#include <string.h>

/* Symbolic constants */
#define DAYSEC  86400   /* seconds per day   */
#define HOURSEC 3600    /* seconds per hour  */
#define MINSEC  60      /* seconds per minut */

#define MAXBUF 512     /* lenght of largest string required to read */

/* ----  CPU model ---- */
void cpumodel(void)
{
  FILE *cpuinfofile;
  const char *prefix = "model name\t: ";
  int pref_len = strlen(prefix);

  char cpumodel[MAXBUF]; 
  char line[MAXBUF];

  cpuinfofile = fopen ("/proc/cpuinfo","r");
  
  while (fgets(line,MAXBUF,cpuinfofile))
    if (strncmp(prefix,line,pref_len) == 0)
      printf("CPU model: %s",line+pref_len);

  fclose(cpuinfofile);
}

/* ---- kernel version of the operating system ---- */
void kernelversion(void)
{
  FILE *versionfile;

  char kernelversion[MAXBUF];
  char line[MAXBUF]; 

  /* Kernel version */
  versionfile = fopen("/proc/version","r");

  fgets(line,MAXBUF,versionfile);

  if (sscanf(line,"Linux version %s",kernelversion))
    printf("Kerne version: %s\n",kernelversion);

  fclose(versionfile);
}

/* ---- uptime of the machine ---- */
void uptime(void)
{
  FILE *cpuinfofile, *versionfile, *uptimefile;

  int uptime;
  char line[MAXBUF]; 

  uptimefile = fopen("/proc/uptime","r");
  
  fgets(line,MAXBUF,uptimefile);

  fclose(uptimefile);
  if (sscanf(line,"%d.",&uptime)) {
    int left,days,hours,minutes,secs;
      
    days = uptime / DAYSEC;
    left = uptime - (days * DAYSEC);
	      
    hours = left / HOURSEC;
    left = left - (hours * HOURSEC);

    minutes = left / MINSEC;
    secs = left - minutes * MINSEC;
      
    printf("Uptime: %2d:%2d:%2d:%2d\n",days,hours,minutes,secs);
  }
}

/* ---- main program ---- */
int main (void)
{

  cpumodel();
  kernelversion();
  uptime();
  
  return 0;
}

