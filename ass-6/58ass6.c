/*
Name : Somnath Mishra
Roll No: 002211001058
*/

/*
Assignment Details - The OS is a program that uses various data structures. Like
all programs in execution, you can determine the performance and other behaviour
of the OS by inspecting its state - the values stored in its data structures. In
this part of the assignment, we study some aspects of the organization and
behaviour of a Linux system by observing values of kernel data structures
exposed through the /proc virtual file system.

The /proc virtual file system:
Linux uses the /proc file system to collect information
from kernel data structures. The /proc implementation provided with Linux can
read many different kernel data structures. If you cd to /proc on a Linux
machine, you will see a number of files and directories at that location. Files
in this directory subtree each correspond to some kernel data structure. The
subdirectories with numeric names contain virtual files with information about
the process whose process ID is the same as the directory name. Files in /proc
can be read like ordinary ASCII files. You can open each file and read it using
library routines such as fgets() or fscanf(). The proc (5) manual page explains
the virtual files and their content available through the /proc file system.

Requirements in detail:
You are supposed to write a C program which should print the following values on
terminal

    • Processor Informations (Vendor ID, Model Name and Cache Size in MB)
    • Kernel Name, Kernel Release and Operating System Name.
    • The amount of memory configured into this computer and Free Memory
    • Amount of time since the system was last booted (In Hours, Minutes,
Seconds)


Input Description  - No input
Output Description - Print the dynamic values every seconds
    • Processor Informations (Vendor ID, Model Name and Cache Size in MB)
    • Kernel Name, Kernel Release and Operating System Name.
    • The amount of memory configured into this computer and Free Memory
    • Amount of time since the system was last booted (In Hours, Minutes,
Seconds)

*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc 58ass6.c
Execution Command (in Linux Bash Terminal) :- ./a.out
*/

/*
Sample Input  - No input
Sample Output -
Output :- (PROGRAM OUTPUT)
Kernel Information:
Operating System Name: Linux
Kernel Name: 6.8.0-48-generic
Kernel Release: 6.8.0-48-generic
Processor Vendor ID: vendor_id  : GenuineIntel
Processor Model: model name     : Intel(R) Core(TM) i5-1035G1 CPU @ 1.00GHz
Processor Cache Size: cache size        : 6144 KB
------------------------------------------------------------------------------------------

Memory Information:
Total Memory: 20259396 kB
Free Memory: 10046144 kB
------------------------------------------------------------------------------------------

System Uptime:
Time since last boot: 0 hours, 26 minutes, 20 seconds
------------------------------------------------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_BUFFER_LENGTH 10000

// Function to print a line separator
void printLine() {
  printf("---------------------------------------------------------------------"
         "---------------------\n\n");
}

// Function to get and print kernel information (Kernel Name, Kernel Release,
// and OS Name)
void kernelInfo() {
  FILE *fp;
  fp = fopen("/proc/sys/kernel/osrelease", "r");
  char *kernelName = (char *)malloc(1024);
  fgets(kernelName, 1024, fp);
  fclose(fp);

  fp = fopen("/proc/sys/kernel/ostype", "r");
  char *osType = (char *)malloc(1024);
  fgets(osType, 1024, fp);
  fclose(fp);

  fp = fopen("/proc/cpuinfo", "r");
  char *vendorID = (char *)malloc(1024);
  char *modelName = (char *)malloc(1024);
  char *cacheSize = (char *)malloc(1024);
  while (fgets(vendorID, 1024, fp)) {
    if (strstr(vendorID, "vendor_id") != NULL) {
      break;
    }
  }
  while (fgets(modelName, 1024, fp)) {
    if (strstr(modelName, "model name") != NULL) {
      break;
    }
  }
  while (fgets(cacheSize, 1024, fp)) {
    if (strstr(cacheSize, "cache size") != NULL) {
      break;
    }
  }
  fclose(fp);

  printf("\nKernel Information:\n");
  printf("Operating System Name: %s", osType);
  printf("Kernel Name: %s", kernelName);
  printf("Kernel Release: %s", kernelName);
  printf("Processor Vendor ID: %s", vendorID);
  printf("Processor Model: %s", modelName);
  printf("Processor Cache Size: %s", cacheSize);
  printLine();
}

// Function to get and print memory information (Total Memory and Free Memory)
void memoryInfo() {
  FILE *mem_file = fopen("/proc/meminfo", "r");
  if (mem_file == NULL) {
    perror("Error opening file to read memory info");
    exit(EXIT_FAILURE);
  }

  long total_memory = 0;
  long free_memory = 0;
  char buffer[256];

  // Reading the total memory
  fgets(buffer, sizeof(buffer), mem_file);
  sscanf(buffer, "MemTotal: %ld kB", &total_memory);

  // Reading the free memory
  fgets(buffer, sizeof(buffer), mem_file);
  sscanf(buffer, "MemFree: %ld kB", &free_memory);

  printf("Memory Information:\n");
  printf("Total Memory: %ld kB\n", total_memory);
  printf("Free Memory: %ld kB\n", free_memory);
  printLine();
  fclose(mem_file);
}

// Function to get and print system uptime (in hours, minutes, and seconds)
void uptimeInfo() {
  FILE *uptime_file = fopen("/proc/uptime", "r");
  if (uptime_file == NULL) {
    perror("Error opening file to read uptime info");
    exit(EXIT_FAILURE);
  }

  double uptime_seconds;
  fscanf(uptime_file, "%lf", &uptime_seconds);
  fclose(uptime_file);

  int hours = (int)(uptime_seconds / 3600);
  int minutes = (int)((uptime_seconds - (hours * 3600)) / 60);
  int seconds = (int)(uptime_seconds - (hours * 3600) - (minutes * 60));

  printf("System Uptime:\n");
  printf("Time since last boot: %d hours, %d minutes, %d seconds\n", hours,
         minutes, seconds);
  printLine();
}

int main() {
  kernelInfo(); // Get and print kernel information
  memoryInfo(); // Get and print memory information
  uptimeInfo(); // Get and print system uptime information

  return 0;
}
