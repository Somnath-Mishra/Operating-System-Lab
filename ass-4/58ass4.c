/*

Name : Somnath Mishra
Roll No : 002211001058
*/

/*

Assignment Details :- Objective of this programming assignment is to use mmap() call and observe page-fault
                      using the ‘sar’ command. A big file (about 8GB) should be created using the ‘fallocate’ command.
                      This big file should be written with a single integer value (say X) at a specific offset (say F).
                      Both the integer value and the offset should be generated using a random function.
                      Please do remember this random function should generate a quantity anywhere between 0 and 8G.
                      The above big file should also be mapped in the virtual address space using mmap() call.
                      Once it is mapped, the data should be read from the same specific offset (F).
                      Now, if the data read is X`; then verify that X and X` are the same.
                      In case of verification failure, an error message is to be printed.
                      Note that, the offset value F can be anywhere between 0 and 8G.
                      This sequence of writing and reading data to/from a specific offset and also verification should
                      be put in a while loop to go forever.
                      In another terminal execute the command ‘sar –B 1 1000’ to observe for the page fault.
                      This command should be started before the above program is put under execution.
                      So, one can observe that the page faults are increasing, once the above program starts executing.
                      The output of the program and the ‘sar’ command should be pasted as a comment at
                      the beginning of the program file.

Input Description  :- The name of the file to be transferred is entered as a command line input for execution of the program.


Output Description :-

    >>  The method prints the value written in the offset of the buffer and also the value read from the same offset
    >>  The method also prints whether the value written and read are the same or not


*/

/*

Command for creating a 8GB file :- fallocate -l  fileAss4.txt
NOTE :- This file has to be created in the same directory as that of the program

Compilation Command :- gcc 58ass4.c

Execution Command   :- ./a.out  fileAss4.txt

*/

/*

Sample Input  :- No input

NOTE :- Use Control + C to exit from the infinite loop

Sample Output :- (PROGRAM OUTPUT)

[be2258@localhost ass-4]$ ./a.out fileAss4.txt 
The Value Written is : 5         
The Value Read is : 5         
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 6         
The Value Read is : 6         
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 43        
The Value Read is : 43        
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 78        
The Value Read is : 78        
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 18        
The Value Read is : 18        
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 76        
The Value Read is : 76        
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 81        
The Value Read is : 81        
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 93        
The Value Read is : 93        
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 10        
The Value Read is : 10        
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 21        
The Value Read is : 21        
The value that is read and written are the same!
---------------------------------------------
 :- (OUTPUT OF SAR COMMAND)
Linux Bash Command :- sar -B 1 1000

[be2258@localhost ~]$ sar -B 1 1000
Linux 3.10.0-514.21.1.el7.x86_64 (localhost.localdomain) 	Monday 11 November 2024 	_x86_64_	(16 CPU)

06:47:54  IST  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
06:47:55  IST      0.00      0.00     38.00      0.00    963.00      0.00      0.00      0.00      0.00
06:47:56  IST      0.00     12.00     30.00      0.00    943.00      0.00      0.00      0.00      0.00
06:47:57  IST      0.00      0.00     18.00      0.00   1106.00      0.00      0.00      0.00      0.00
06:47:58  IST      0.00      0.00     55.00      0.00   1187.00      0.00      0.00      0.00      0.00
06:47:59  IST      0.00      0.00     34.00      0.00   1178.00      0.00      0.00      0.00      0.00
06:48:00  IST      0.00      0.00     20.00      0.00   1123.00      0.00      0.00      0.00      0.00
06:48:01  IST      0.00      4.00     19.00      0.00   1007.00      0.00      0.00      0.00      0.00
06:48:02  IST      0.00      0.00     19.00      0.00   1187.00      0.00      0.00      0.00      0.00
06:48:03  IST      0.00    353.00     53.00      0.00   1068.00      0.00      0.00      0.00      0.00
06:48:04  IST      0.00      0.00     18.00      0.00   1243.00      0.00      0.00      0.00      0.00
06:48:05  IST      0.00      0.00     29.00      0.00   1266.00      0.00      0.00      0.00      0.00
06:48:06  IST      0.00    309.00     19.00      0.00    987.00      0.00      0.00      0.00      0.00
06:48:07  IST      0.00      0.00     63.00      0.00   1514.00      0.00      0.00      0.00      0.00
06:48:08  IST      0.00      0.00    186.00      0.00   2018.00      0.00      0.00      0.00      0.00
06:48:09  IST      0.00      0.00     19.00      0.00   1435.00      0.00      0.00      0.00      0.00
06:48:10  IST      0.00      0.00     22.00      0.00   1930.00      0.00      0.00      0.00      0.00
06:48:11  IST      0.00      4.00     69.00      0.00    715.00      0.00      0.00      0.00      0.00
06:48:12  IST      0.00      0.00     18.00      0.00     42.00      0.00      0.00      0.00      0.00
06:48:13  IST      0.00      0.00     49.00      0.00    165.00      0.00      0.00      0.00      0.00
06:48:14  IST      0.00      0.00     18.00      0.00     42.00      0.00      0.00      0.00      0.00
06:48:15  IST      0.00      0.00     18.00      0.00     43.00      0.00      0.00      0.00      0.00
06:48:16  IST      0.00      4.00     18.00      0.00     42.00      0.00      0.00      0.00      0.00
^C

06:48:16  IST      0.00      0.00     28.57      0.00     61.43      0.00      0.00      0.00      0.00
Average:         0.00     30.22     37.53      0.00    935.99      0.00      0.00      0.00      0.00

*/

// Header Files
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define LOWER 0          // LOWER value for the randomIntegerGenerator method
#define UPPER 100 // UPPER value for the randomIntegerGenerator method

char *addressOfMapBuffer; // The address of the buffer created by the mmap() method call is stored

void printLine()
{
    printf("---------------------------------------------\n");
}
int readInteger(unsigned long offset)
{
    unsigned long readValue;
    sscanf(addressOfMapBuffer + offset, "%lu", &readValue);
    printf("The Value Read is : %-10lu\n", readValue);
    return readValue;
}

int writeInteger(unsigned long offset, unsigned long value)
{
    printf("The Value Written is : %-10lu\n", value);
    sprintf(addressOfMapBuffer + offset, "%lu", value);
}

unsigned long randomIntegerGenerator()
{
    unsigned long lowerRange = LOWER;
    unsigned long upperRange = UPPER;
    unsigned long randomNumber = lowerRange + (rand() % (upperRange - lowerRange + 1));
    return randomNumber;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Sufficient number of arguments are not provided!\n");
        printf("The expected execution command is : ./a.out <file_name>\n");
        exit(1);
    }

    // Opening the user specified file
    int FILE = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);

    // The information about the user specified file is stored in this structure
    struct stat sb;

    // Getting the information of the file in the sb variable
    if (fstat(FILE, &sb) == -1)
    {
        perror("Some ERROR occured while getting the file size!");
        exit(1);
    }

    // Mapping the file in the virtual address space
    if ((addressOfMapBuffer = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, FILE, 0)) == MAP_FAILED)
    {
        perror("Some ERROR occured while mapping the file!");
        exit(2);
    }

    // Setting the seed value for the rand() function
    srand(time(NULL));
    unsigned long offset, writtenValue, readValue;
    
   // int cnt=0;
    while (1)
    {
        writtenValue = randomIntegerGenerator(); // Getting a random integer in the weittenValue variable from the randomIntegerGenerator method

        offset = randomIntegerGenerator(); // Getting a random integer in the offset variable from the randomIntegerGenerator method

        writeInteger(offset, writtenValue); // Writing the value in writtenValue varible in the offset position of the addressOfMapBuffer

        readValue = readInteger(offset); // Reading a value in readValue from the offset position of the addressOfMapBuffer

        // Checking whether readValue and writtenValue are same or not
        if (writtenValue == readValue)
        {
            printf("The value that is read and written are the same!\n");
            printLine();
        }
        else
        {
            printf("The value that is read and written are NOT the same!\n");
            printLine();
        }
	//cnt++;
    }

    return 0;
}
