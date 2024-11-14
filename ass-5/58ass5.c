/*
Name: Somnath Mishra
Roll No : 002211001058
*/

/*
Assignment Details - The objective of this assignment is to create a deadlock.
For this purpose define two global variables (Total_1 and Total_2) and
initialize both of them to 1000. You should also have two mutexes to protect
these two global variables. You need to create two threads also.

The function of each of the threads is to generate a random quantity (not more
than 50) and subtract that quantity from one of the Total and add that quantity
to the other Total. While manipulating the Totals, each Thread should lock both
the mutex and then unlock it after changing the Totals.

The order of locking and unlocking the Mutex is very important, because that’s
what creates a Deadlock. Once you correctly identify this order, you should
upload the program. Also, include that information (as comment in your source
file) how to avoid this kind of Deadlock.

If these two Threads, Two Totals and Two Mutex are not good enough for Deadlock;
Then you need to create one more Thread, one more Total and and one more Mutex;
and carry on the same experiment.

Make sure there are enough printf in your program so that it can be clearly
understood that there is a Deadlock. One way to ensure enough printf is to
display the total of Total_1 and Total_2 all the time after every operation on
it.

Input Description  - No input
Output Description - Print the individual total and the grand total
*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc -o ass4 58ass5.c -lpthread
Execution Command (in Linux Bash Terminal) :- ./ass4
*/

/*
Deadlock Sequence -

To avoid deadlock:
- Both threads should lock the mutexes in the same order.
- For example, both `threadOne` and `threadTwo` should lock `mutex_1` first and
then `mutex_2`.
- This prevents a circular wait condition, which is a key factor in deadlocks.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Initialize global totals
int Total_1 = 1000;
int Total_2 = 1000;

// Mutexes to protect the totals
pthread_mutex_t mutex_1;
pthread_mutex_t mutex_2;

// Function to generate a random number between 1 and 50
int randomNumberGenerator(int lower, int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

// Thread function to simulate deadlock condition in threadOne
void *threadOne() {
  // Lock mutex_1 first, then mutex_2
  pthread_mutex_lock(&mutex_1);
  printf("Thread 1 locked mutex_1\n");

  sleep(1); // Delay to increase chance of deadlock

  pthread_mutex_lock(&mutex_2);
  printf("Thread 1 locked mutex_2\n");

  // Transfer a random amount from Total_1 to Total_2
  int amount = randomNumberGenerator(1, 50);
  Total_1 -= amount;
  Total_2 += amount;
  printf("Thread 1: Transferred %d from Total_1 to Total_2\n", amount);
  printf("Total_1: %d, Total_2: %d\n", Total_1, Total_2);

  // Unlock mutexes in reverse order
  pthread_mutex_unlock(&mutex_2);
  printf("Thread 1 unlocked mutex_2\n");

  pthread_mutex_unlock(&mutex_1);
  printf("Thread 1 unlocked mutex_1\n");

  return NULL;
}

// Thread function to simulate deadlock condition in threadTwo
void *threadTwo() {
  // Lock mutex_2 first, then mutex_1 (opposite order to threadOne)
  pthread_mutex_lock(&mutex_2);
  printf("Thread 2 locked mutex_2\n");

  sleep(1); // Delay to increase chance of deadlock

  pthread_mutex_lock(&mutex_1);
  printf("Thread 2 locked mutex_1\n");

  // Transfer a random amount from Total_2 to Total_1
  int amount = randomNumberGenerator(1, 50);
  Total_2 -= amount;
  Total_1 += amount;
  printf("Thread 2: Transferred %d from Total_2 to Total_1\n", amount);
  printf("Total_1: %d, Total_2: %d\n", Total_1, Total_2);

  // Unlock mutexes in reverse order
  pthread_mutex_unlock(&mutex_1);
  printf("Thread 2 unlocked mutex_1\n");

  pthread_mutex_unlock(&mutex_2);
  printf("Thread 2 unlocked mutex_2\n");

  return NULL;
}

int main() {
  // Initialize mutexes
  pthread_mutex_init(&mutex_1, NULL);
  pthread_mutex_init(&mutex_2, NULL);

  // Seed the random number generator
  srand(time(NULL));

  // Create threads
  pthread_t th1, th2;
  pthread_create(&th1, NULL, threadOne, NULL);
  pthread_create(&th2, NULL, threadTwo, NULL);

  // Wait for threads to complete
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  // Destroy mutexes
  pthread_mutex_destroy(&mutex_1);
  pthread_mutex_destroy(&mutex_2);

  return 0;
}


