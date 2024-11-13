/*
 * Name: Somnath Mishra
 * Roll no : 002211001058
 * Assignment - 2
 *
 *
 * . IPC using Named Pipe(FIFO)
 *
 * Create two processes, named Proc1 and Proc2. Transfer 1GB file from Proc1 to Proc2 using a FIFO. Now, transfer the same file from Proc2 to Proc1 using another FIFO. Now, compare the two files to make sure that the same file has returned back. Also, print the time required to do this double transfer. Attach this output to the source file as a comment.
 *
 *
 *output: 
 *  Opened the file initialFile.txt for reading
 *  Writing to FIFO fifo1
 *  Opened the file receivedFile.txt for writing
 *  Reading from FIFO fifo1
 *  Writing to FIFO fifo1 is completed
 *  File received from process 1
 *  Writing to FIFO fifo2 from the file receivedFile.txt
 *  Writing to fifo2 is completed
 *  Reading from fifo2 and writing to the file receivedBackFile.txt to compare received back file with the initial file sent by process1
 *  Both the files are same, there is no mismatch!
 *  The round-about time for transferring the file between process1 and process2 and back to process1 is 6 milliseconds
 *
 *
 */


#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

//Method to get the time elapsed since the invoking of this function
long getTimeElapsed()
{
    struct timeval timeElapsed;
    gettimeofday(&timeElapsed, NULL);
    return timeElapsed.tv_sec * 1000 + timeElapsed.tv_usec / 1000;
}

//Method to compare two files and check if there is any mismatch or not
void compareFiles(FILE *firstFile, FILE *secondFile)
{
    char firstFileChar = getc(firstFile);
    char secondFileChar = getc(secondFile);

    int lineNumber = 1;
    int totalErrors = 0;

    while (firstFileChar != EOF && secondFileChar != EOF)
    {
        if (firstFileChar == '\n' && secondFileChar == '\n')
        {
            lineNumber++;
        }
        if (firstFileChar != secondFileChar)
        {
            totalErrors++;
            printf(" Mismatch occurred at line number : %d\n", lineNumber);
        }

        firstFileChar = getc(firstFile);
        secondFileChar = getc(secondFile);
    }

    if (totalErrors == 0)
    {
        printf(" Both the files are same, there is no mismatch!\n");
    }
}

int main()
{
    int startingTime = getTimeElapsed();
    char *fifo1 = "FIFOTEMP1";
   //Creating named pipe(FIFO) fifo1 using mknod() system call to transfer large file from process1 to process2 
    mknod(fifo1, S_IFIFO | 0666, 0);
    char *fifo2 = "FIFOTEMP2";
   //Creating named pipe(FIFO)  fifo2 using mknod() system call to transfer large file from process2 to process1 
    mknod(fifo2, S_IFIFO | 0666, 0);
    
    int processID = fork();

    if (processID == 0) // Child process
    {
       
        int fd = open(fifo1, O_RDONLY);
        const char *receivedFile = "receivedFile.txt";
        FILE *receivedfp = fopen(receivedFile, "w");
        if (receivedfp == NULL)
            printf(" Failed to open the file %s for writing\n", receivedFile);
        else
            printf(" Opened the file %s for writing\n", receivedFile);
        if (fd > 0)
        {
            printf(" Reading from FIFO fifo1\n");
            char str[100];
            while (read(fd, str, sizeof(str)))
            {
                fputs(str, receivedfp);
            }
            printf(" File received from process 1\n");
            close(fd);
        }
        else
        {
            printf(" Failed to open FIFO fifo1 for reading\n");
        }

        fclose(receivedfp);

        

        receivedfp = fopen(receivedFile, "r");
        fd = open(fifo2, O_WRONLY);
        if (fd > 0)
        {
            printf(" Writing to FIFO fifo2 from the file %s\n", receivedFile);
            char buffer[100];
            while (fgets(buffer, sizeof(buffer), receivedfp))
            {
                int len = strlen(buffer);
                int n = write(fd, buffer, len);
                if (n != len)
                    perror("write");
            }

            printf(" Writing to fifo2 is completed\n");
        }
    }
    else 
    {
       
        const char *initialFile = "FFF";
        FILE *fp = fopen(initialFile, "r");
        if (fp == NULL)
            printf(" Failed to open the file %s for reading\n", initialFile);
        else
            printf(" Opened the file %s for reading\n", initialFile);
        int fd = open(fifo1, O_WRONLY);
        if (fd > 0)
        {
            printf(" Writing to FIFO fifo1\n");
            char str[100];
            while (fgets(str, sizeof(str), fp))
            {
                int len = strlen(str);
                int n = write(fd, str, len);
                if (n != len)
                    perror("write");
            }

            printf(" Writing to FIFO fifo1 is completed\n");
        }
        else
        {
            printf(" Failed to open FIFO fifo1 for writing\n");
        }
        close(fd);
        fclose(fp);

       
        fd = open(fifo2, O_RDONLY);
        const char *receivedBackFile = "receivedBackFile.txt";
        FILE *receivedbackfp = fopen(receivedBackFile, "w");
        if (fd > 0)
        {
            printf(" Reading from fifo2 and writing to the file %s to compare received back file with the initial file sent by process1\n", receivedBackFile);
            char buffer[100];
            while (read(fd, buffer, sizeof(buffer)))
            {
                fputs(buffer, receivedbackfp);
            }
        }
        else
        {
            perror("read");
        }

        close(fd);
        fclose(receivedbackfp);

        int endingTime = getTimeElapsed();
       
        int totalTimeTaken = endingTime - startingTime;

        
        fp = fopen(initialFile, "r");
        receivedbackfp = fopen(receivedBackFile, "r");
        compareFiles(fp, receivedbackfp);

        fclose(fp);
        fclose(receivedbackfp);
        printf(" The round-about time for transferring the file between process1 and process2 and back to process1 is %d milliseconds\n", totalTimeTaken);
    }

    return 0;
}
