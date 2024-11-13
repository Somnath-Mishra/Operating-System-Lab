/*
 *Name : Somnath Mishra
 *Roll No- 002211001058
 *Assignment -3


 *create two processes. Transfer 1GB file from parent to child using a Socket. Now, transfer the same file from child to parent using the same Socket. 

Now, the parent process should compare the two files to make sure that the same file has returned back. 

 *
 *Output: 
 *
 *[be2258@localhost ass-3]$ ./a.out bigFileAss3.txt 
 Server side socket is created successfully!
 Server bind to server is suceessful!
 Server is now listening suceessfully at port 8069
 Client side socket is created successfully!
 Client connected to the server successfully!
 Server connected to the client successfully!
 Comparing the files...
 The files are compared and found to be the same
 The round-about time for the file transfer is : 86 milliseconds
 Cleaning the created files!
 The created files are cleaned!

 *
 *
 *
 * Output :- (CHECKING THE SOCKET DETAILS)
 * Linux Bash Command :- ss -t -a
 *
 * [be2258@localhost ass-2]$ ss -t -a
 * State       Recv-Q Send-Q Local Address:Port                 Peer Address:Port                
 * LISTEN      0      128             *:sunrpc                        *:*                    
 * LISTEN      0      5      192.168.122.1:domain                        *:*                    
 * LISTEN      0      128             *:ssh                           *:*                    
 * LISTEN      0      128     127.0.0.1:ipp                           *:*                    
 * LISTEN      1      1               *:italk                         *:*                    
 * LISTEN      0      100     127.0.0.1:smtp                          *:*                    
 * LISTEN      0      1               *:8069                          *:*                    
 * ESTAB       0      0      172.16.4.112:ssh                  172.16.4.201:52050                
 * ESTAB       0      0      172.16.4.112:ssh                  172.16.4.230:53913    
 *
 *
 *Command for creating a 1GB file :- fallocate -l 1G bigFileAss3.txt
NOTE - This file has to be created in the same directory as that of the program

Compilation Command (in Linux Bash Terminal) :- gcc 58_ass3.c

Execution Command (in Linux Bash Terminal) :- ./a.out bigFileAss3.txt

 *
 *
 *Output :-
Linux Bash Command :- ls -l
 *
 *[be2258@localhost ass-3]$ ls -l
total 36
-rw-r--r--. 1 be2258 ugyr22 12716 Sep 12 14:01 58_ass3.c
-rwxr-xr-x. 1 be2258 ugyr22 18296 Sep 12 14:04 a.out

 *
 */


#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TEMP_FILE1 "process1_temporary_file_ass3"
#define TEMP_FILE2 "process2_temporary_file_ass3"

#define MAXLEN 1024
#define LOCALHOST "127.0.0.1" //IP address of the local host
#define PORT 9034           //port number 

//Method to get the time elapsed since the invoking of this function
long getTimeElapsed()
{
    struct timeval timeElapsed;
    gettimeofday(&timeElapsed, NULL);
    return timeElapsed.tv_sec * 1000 + timeElapsed.tv_usec / 1000;
}

//Method for cleaning the created files
void cleanFiles()
{
    printf(" Cleaning the created files!\n");

    remove(TEMP_FILE1);
    remove(TEMP_FILE2);
    remove("bigFileAss3.txt");

    printf(" The created files are cleaned!\n");
}


//Method to compare two files and check  if there is any mismatch or not
int compareFiles(char *firstFile, char *secondFile)
{
    int fileID1, fileID2; //File IDs of the files

  //Open the initial input file 
    if ((fileID1 = open(firstFile, O_RDONLY)) == -1)
    {
        perror(" Error in opening the file!\n");
        return -1;
    }

   //Open the received file 
    if ((fileID2 = open(secondFile, O_RDONLY)) == -1)
    {
        perror(" Error in opening the file!\n");
        if (close(fileID2) == -1)
        {
            perror(" Error in closing the file!\n");
        }
        return -1;
    }

   //Buffers to store contents of the file which can be later matched if they are identical 
    char buffer1[MAXLEN];
    char buffer2[MAXLEN];

    int returnValue = 1;

    while (true)
    {
        int len1 = read(fileID1, buffer1, MAXLEN);
        int len2 = read(fileID2, buffer2, MAXLEN);
       //If lenght of the files are -1 then there occurs an error in reading file 
        if (len1 == -1 || len2 == -1)
        {
            perror(" Error in reading the file!\n");
            returnValue = -1;
            break;
        }

       //If the sent and received files are different then their length will differ 
        if (len1 != len2)
        {
            returnValue = 0;
            break;
        }

      //If length is 0, it means we have read the whole file and reached EOF 
        if (len1 == 0)
        {
            break;
        }

	//if len1>0, we continue to read.

      	int i; 
        for (i = 0; i < len1; i++)
        {
            if (buffer1[i] != buffer2[i])
            {
             	//Files are different in their input, hence error has occured while transmission 
                returnValue = 0;
                break;
            }
        }

        if (returnValue == 0)
        {
            break;
        }
    }

  //Close the files after reading and checking them 
    if (close(fileID1) == -1)
    {
        perror(" Error in closing the file!\n");
        return -1;
    }

    if (close(fileID2) == -1)
    {
        perror(" Error in closing the file!\n");
        return -1;
    }

    return returnValue;
}

//Method to get the file size in bytes, this allows us to validate that the entire file has reached the other side
long getFileSize(char *fileName)
{
    FILE *file;

  //Opening the file 
    if ((file = fopen(fileName, "r")) == NULL)
    {
        perror(" Error in fopen. Unable to determine file size\n");
        return -1;
    }

  //Taking the pointer to the end of the file 
    if (fseek(file, 0, SEEK_END) == -1)
    {
        perror(" Error in fseek. Unable to determine file size\n");
        return -1;
    }

   //Gets the size of the file, by calculating the difference between the start of the file and the current position of the pointer int the file 
    long fileSize = ftell(file);

   //If size could not be determined then -1 
    if (fileSize == -1)
    {
        perror(" Error in ftell. Unable to determine file size\n");
        return -1;
    }

    return fileSize;
}

//Sending the file via the socket
int sendFile(char *sourceFile, int destination)
{

    //Getting the size of the file 
    long fileSize = getFileSize(sourceFile);

   //Error in getting the size of the file 
    if (fileSize == -1)
    {
        return -1;
    }

    //Buffer/packet to be sent 
    char buffer[MAXLEN];

    
    *((long *)buffer) = fileSize;

   //First message sent is the size of the file 
    if (send(destination, buffer, sizeof(long), 0) < 0)
    {
        perror(" Error in sending the file!\n");
        return -1;
    }

   //Opening the file whose content is to be sent 
    int fileID = open(sourceFile, O_RDONLY);

  //If there is an error in openining the file then -1 
    if (fileID == -1)
    {
        perror(" Error in opening the file!\n");
        return -1;
    }

    int returnValue = 1;

   //An infinite loop until the entire file is sent 
    while (1)
    {

       //Reading from the file into the buffer 
        long bufferRead = read(fileID, buffer, MAXLEN);

       //If any error occured then -1 
        if (bufferRead < 0)
        {
            perror(" Error in reading the file!\n");
            returnValue = -1;
            break;
        }

        if (bufferRead == 0)
            break; //EOF is reached

       //Sending the buffer/packet to the other side of the socket, if there is any failure then -1 
        if (send(destination, buffer, bufferRead, 0) == -1)
        {
            returnValue = -1;
            break;
        }
    }

   //Closing the file 
    if (close(fileID) == -1)
    {
        perror(" Error in closing the file!\n");
        return -1;
    }

   //returns 1 is success 
    return returnValue;
}

//Receiving the file via the socket
int receiveFile(char *destinationFile, int source)
{

    char buffer[MAXLEN];

   //Receives the filesize so as to authenticate that the entire file has been received or not 
    if (recv(source, buffer, sizeof(long), 0) < 0)
    {
        perror(" Error in receiving the file!\n");
        return -1;
    }

    //size of the file 
    long fileSize = *((long *)buffer);

   //Opening the destination file, where the contents received via socket will be stored 
    int destinationID = open(destinationFile, O_WRONLY | O_CREAT, 0666);

    if (destinationID < 0)
    {
        perror(" Error in opening the file!\n");
        return -1;
    }

    long toReceive = fileSize;

    int returnValue = 1;

   //An infinite loop until the file has been received 
    while (toReceive > 0)
    {

      //Receiving the contents in the form of packets 
        int bytesRead = recv(source, buffer, MAXLEN, 0);

      //is negative is there is an error while receiving the contents of the file 
        if (bytesRead < 0)
        {
            perror(" Error in reading!\n");
            returnValue = -1;
            break;
        }

        if (bytesRead == 0)//EOF has been reached 
            break;

       //writing into the destination file 
        if (write(destinationID, buffer, bytesRead) < 0)
        {
            perror(" Error in writing!\n");
            returnValue = -1;
            break;
        }

        toReceive -= bytesRead;
    }

    if (close(destinationID) < 0)
    {
        perror(" Error in closing the file!\n");
        return -1;
    }

   //If the file has been recieved successfully then return 1 
    return returnValue;
}

//Creating the server
int createServer()
{
  
    int serverID;

  //Creating the server side interface using TCP/IP protocols 
    serverID = socket(AF_INET, SOCK_STREAM, 0);

  //If there is a failure in creating the server than -1 
    if (serverID < 0)
    {
        perror(" Unable to create server side socket!\n");
        return serverID;
    }
    printf(" Server side socket is created successfully!\n");

  //server side address information 
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;//IPv4 family of address  
    server_address.sin_port = htons(PORT);//Adding the port number
    server_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&server_address.sin_zero, 8);

   //Binding the server address to the socket created, if it fails to bind then -1 
    if (bind(serverID, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror(" Error in binding to the server!\n");

        if (close(serverID) == -1)
        {
            perror(" Error in closing the server!\n");
        }

        return -1;
    }

    printf(" Server bind to server is suceessful!\n");

  //Listening for the clients 
    if (listen(serverID, 1) < 0)
    {
        perror(" Error in server listening!\n");
        if (close(serverID) == -1)
        {
            perror(" Error closing!!!\n");
        }

        return -1;
    }

    printf(" Server is now listening suceessfully at port %d\n", PORT);

    //Returning the server side descripter 
    return serverID;
}

//To connect to the server to client
int acceptConnection(int serverID)
{

    int connectionfd;              //Connection socket file descriptor  
    struct sockaddr_in clientAddress;//A sockaddr_in for client 
    unsigned int addressLength = sizeof(clientAddress);

   //Accepting the client and connecting to the server 
    connectionfd = accept(serverID, (struct sockaddr *)&clientAddress, &addressLength);

   //When it fails to accept the client then -1 
    if (connectionfd < 0)
    {
        perror(" Server could not accept connection!\n");
        return -1;
    }

  //Return server side descriptor 
    return connectionfd;
}

//To connect the client to the server
int connectToServer()
{

   //Creating the client side of socket interface using TCP/IP protocols 
    int clientID = socket(AF_INET, SOCK_STREAM, 0);

  //If it fails to create the socket then -1 
    if (clientID < 0)
    {
        perror(" Error in creating client side socket!\n");
        return clientID;
    }
    printf(" Client side socket is created successfully!\n");

   //Address details 
    struct sockaddr_in clientAddress;
    clientAddress.sin_family = AF_INET;  //IPv4 address family 
    clientAddress.sin_port = htons(PORT);//Adding port to the address
    clientAddress.sin_addr.s_addr = inet_addr(LOCALHOST);
    bzero(&clientAddress.sin_zero, 8);

  //Connecting the server side of the socket, when it fails to connect then -1 
    if (connect(clientID, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) < 0)
    {
        perror(" Client could not connect!\n");

        if (close(clientID) == -1)
        {
            perror(" Error in closing client!\n");
        }
        return -1;
    }

   //Returning client side descriptor 
    return clientID;
}

//process1 (server side program)
void process1(char *sourceFile)
{

  //server id is negtive if the server socket fails to get created 
    int serverID = createServer();

    
    if (serverID < 0)
    {
        perror(" Creation of server failed!\n");
        exit(EXIT_FAILURE);
    }

  //connecting to a client 
    int connectID = acceptConnection(serverID);

   //Connect ID is negative if the server is not connected the client 
    if (connectID < 0)
    {
        perror(" Connection failed!\n");
        exit(EXIT_FAILURE);
    }

    printf(" Server connected to the client successfully!\n");

    long startingTime = getTimeElapsed();

  //Sending to the client 
    if (sendFile(sourceFile, connectID) < 0)
    {
        if (close(connectID) < 0)
        {
            perror(" Error in closing!\n");
        }
        if (close(serverID) < 0)
        {
            perror(" Error in closing!\n");
        }

        exit(EXIT_FAILURE);
    }

   //receiving the file from the client 
    if (receiveFile(TEMP_FILE1, connectID) < 0)
    {
        if (close(connectID) < 0)
        {
            perror(" Error in closing!\n");
        }
        if (close(serverID) < 0)
        {
            perror(" Error in closing\n");
        }

        exit(EXIT_FAILURE);
    }

    long endingTime = getTimeElapsed();

  //Calculating the round-about time for tranferring the file between process1 and process2 and back to process1 
    long totalTimeTaken = endingTime - startingTime;

    printf(" Comparing the files...\n");

   //compares the contents of the file 
    if (compareFiles(sourceFile, TEMP_FILE1) > 0)
    {
        printf(" The files are compared and found to be the same\n");
        printf(" The round-about time for the file transfer is : %ld milliseconds\n", totalTimeTaken);
    }
    else
    {
        printf(" Mismatch found in the files!\n");
    }

   //Closing the connections to the socket 
    if (close(connectID) < 0)
    {
        perror(" Error in closing!\n");
    }

    if (close(serverID) < 0)
    {
        perror(" Error in closing!\n");
    }

    cleanFiles();//Method for cleaning the created files 
}

//process2 (client side program)
void process2()
{

    int clientID = connectToServer(); //Method to connect to server

   //clientID is -1 for failure in connection 
    if (clientID < 0)
    {
        perror(" Connecting to server failed!\n");
        exit(EXIT_FAILURE);
    }

    printf(" Client connected to the server successfully!\n");

    //Receiving file via the socket (from the server) 
    if (receiveFile(TEMP_FILE2, clientID) == -1)
    {
        if (close(clientID) < 0)
        {
            perror(" Error in closing!\n");
        }
        exit(EXIT_FAILURE);
    }

   //Sending file via the socket(from the client) 
    if (sendFile(TEMP_FILE2, clientID) < 0)
    {
        if (close(clientID) == -1)
        {
            perror(" Error in closing!\n");
        }

        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[argc + 1])
{
   //checking the number of og arguments 
    if (argc != 2)
    {
        printf(" The number of arguments must be equal 1!\n");
        return 1;
    }

   
    char *sourceFilePath = argv[1];

  //The path of the file which is to be sent and received via the socket 
    pid_t forkID = fork();

  //Forking to create two processess(parent and child) 
    if (forkID < 0)
    {
        perror(" An error occured in forking...\n");
        return 1;
    }

    else if (forkID == 0)
    {
      //child process(process2) 
        process2();
    }

    else
    {
      //Parent process(process1) 
        process1(sourceFilePath);
    }

    return 0;
}
