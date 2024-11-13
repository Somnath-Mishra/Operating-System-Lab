/*Name: Somnath Mishra
 * Roll No: 002211001058
 * Assignment -2
 *Question A
 *
 * Catch the signal ‘SIGINT’ and display “Ha Ha, Not Stopping”. Use ‘signal’ system call. Always use “perror” to check the return status of a library/system call.
 * */


#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

static int sigint_count=0;

void handle_sigint(int sig){
	sigint_count++;
	
	if(sigint_count<2){
		printf("Ha Ha, Not Stopping\n");
	}
	else{
		printf("Received SIGINT twice. Exiting....\n");
		exit(EXIT_SUCCESS);
	}
}

int main(){
	if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        	perror("signal");
        	exit(EXIT_FAILURE);
   	 }
	printf("Press Ctrl+C to test the signal handling...\n");
   	while (1) {
        	pause();  // Wait for signals
    	}
	return 0;
}
