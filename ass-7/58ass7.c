/*
Name : Somnath Mishra
Roll No : 002211001058
*/

/*
Assignment Details - Consider a main process which creates three threads Th1,
Th2, and Th3. The main process also creates two random quantities (X, Y), both
less than 10. These two values will be placed by the main process in the shared
memory (One variant of IPC Primitive)  that is accessible by all the three
threads Th1, Th2 and Th3. The shared memory will be created by the main process
also.

For each pair of values (X,Y), it is required that some computations will be
done by various threads. The thread Th1 will compute A (X*Y) and the thread Th2
will compute B (X*Y)/2). Similarly,  Th3 computes C (X+Y), Th2 again computes D
((X*Y)/(X+Y)), and finally Th1 computes E ((X+Y)(X-Y)). All these values are
kept in the shared memory in a tabular fashion as shown below.

The number of (X,Y) pairs will be taken as an argument from the CLI. It is the
responsibility of the main process to populate required numbers of (X,Y)s in the
shared memory. The program will only exit when all A,B,C etc. are computed for
all given (X,Y) values. Before exiting, all (X,Y)s, As, Bs etc. should be
displayed.

Whenever, the threads complete one phase of computations (A, B, C, D and E),
they will go for another pair of (X,Y) values; but they will start all together.
This can be achieved by proper synchronization.

Use the proper shell command to display the Shared Memory Status/Info/Statistics
and attach this sample output as a comment.

*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc 58ass7.c
Execution Command (in Linux Bash Terminal) :- ./a.out  5
After running the program, use the following shell command to display shared
memory statistics:   ipcs -m

-- -- --Shared Memory Segments-- -- -- --
key         shmid  owner    perms  bytes  nattch status
0x00000000  6      somnath  600    524288 2      dest


Sample Input  -

Enter N, the number of pairs : 5

Enter pair 1 (X Y): 1 2
Enter pair 2 (X Y): 2 3
Enter pair 3 (X Y): 3 4
Enter pair 4 (X Y): 4 5
Enter pair 5 (X Y): 5 6
Th1: A (X*Y) = 2, E ((X+Y)*(X-Y)) = -3
Th2: B (X*Y)/2 = 1.00, D ((X*Y)/(X+Y)) = 0.67
Th3: C (X+Y) = 3
Th1: A (X*Y) = 6, E ((X+Y)*(X-Y)) = -5
Th2: B (X*Y)/2 = 3.00, D ((X*Y)/(X+Y)) = 1.20
Th3: C (X+Y) = 5
Th1: A (X*Y) = 12, E ((X+Y)*(X-Y)) = -7
Th2: B (X*Y)/2 = 6.00, D ((X*Y)/(X+Y)) = 1.71
Th3: C (X+Y) = 7
Th1: A (X*Y) = 20, E ((X+Y)*(X-Y)) = -9
Th2: B (X*Y)/2 = 10.00, D ((X*Y)/(X+Y)) = 2.22
Th3: C (X+Y) = 9
Th1: A (X*Y) = 30, E ((X+Y)*(X-Y)) = -11
Th2: B (X*Y)/2 = 15.00, D ((X*Y)/(X+Y)) = 2.73
Th3: C (X+Y) = 11

Results:
---------------------------------------------------------
Pair    X       Y       A       B       C       D       E
---------------------------------------------------------
1       1       2       2       1.00    3       0.67    -3
2       2       3       6       3.00    5       1.20    -5
3       3       4       12      6.00    7       1.71    -7
4       4       5       20      10.00   9       2.22    -9
5       5       6       30      15.00   11      2.73    -11
---------------------------------------------------------
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAX_PAIRS 10  // Max number of pairs
#define SHM_SIZE 1024 // Shared memory size

struct SharedData {
  int X[MAX_PAIRS];
  int Y[MAX_PAIRS];
  int A[MAX_PAIRS];
  double B[MAX_PAIRS];
  int C[MAX_PAIRS];
  double D[MAX_PAIRS];
  int E[MAX_PAIRS];
  int task_index;
  int total_pairs;
  sem_t sem1, sem2, sem3; // Semaphores for synchronization
};

struct SharedData *shared_data;
pthread_mutex_t mutex;

void printLine() {
  printf("---------------------------------------------------------\n");
}

void *Th1(void *arg) {
  int idx;
  while (1) {
    sem_wait(&shared_data->sem1);

    pthread_mutex_lock(&mutex);
    idx = shared_data->task_index;
    if (idx >= shared_data->total_pairs) {
      pthread_mutex_unlock(&mutex);
      sem_post(&shared_data->sem2);
      break;
    }
    shared_data->A[idx] = shared_data->X[idx] * shared_data->Y[idx];
    shared_data->E[idx] = (shared_data->X[idx] + shared_data->Y[idx]) *
                          (shared_data->X[idx] - shared_data->Y[idx]);
    pthread_mutex_unlock(&mutex);

    printf("Th1: A (X*Y) = %d, E ((X+Y)*(X-Y)) = %d\n", shared_data->A[idx],
           shared_data->E[idx]);
    sem_post(&shared_data->sem2);
  }
  return NULL;
}

void *Th2(void *arg) {
  int idx;
  while (1) {
    sem_wait(&shared_data->sem2);

    pthread_mutex_lock(&mutex);
    idx = shared_data->task_index;
    if (idx >= shared_data->total_pairs) {
      pthread_mutex_unlock(&mutex);
      sem_post(&shared_data->sem3);
      break;
    }
    shared_data->B[idx] = (double)(shared_data->A[idx]) / 2;
    if (shared_data->X[idx] + shared_data->Y[idx] != 0) {
      shared_data->D[idx] = (double)(shared_data->A[idx]) /
                            (shared_data->X[idx] + shared_data->Y[idx]);
    } else {
      shared_data->D[idx] = 0; // Handle division by zero
    }
    pthread_mutex_unlock(&mutex);

    printf("Th2: B (X*Y)/2 = %.2f, D ((X*Y)/(X+Y)) = %.2f\n",
           shared_data->B[idx], shared_data->D[idx]);
    sem_post(&shared_data->sem3);
  }
  return NULL;
}

void *Th3(void *arg) {
  int idx;
  while (1) {
    sem_wait(&shared_data->sem3);

    pthread_mutex_lock(&mutex);
    idx = shared_data->task_index;
    if (idx >= shared_data->total_pairs) {
      pthread_mutex_unlock(&mutex);
      sem_post(&shared_data->sem1);
      break;
    }
    shared_data->C[idx] = shared_data->X[idx] + shared_data->Y[idx];
    shared_data->task_index++;
    pthread_mutex_unlock(&mutex);

    printf("Th3: C (X+Y) = %d\n", shared_data->C[idx]);
    sem_post(&shared_data->sem1);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <number_of_pairs>\n", argv[0]);
    return 1;
  }
  int N = atoi(argv[1]);
  if (N > MAX_PAIRS) {
    fprintf(stderr, "Number of pairs exceeds maximum limit (%d).\n", MAX_PAIRS);
    return 1;
  }

  int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
  if (shmid < 0) {
    perror("shmget");
    exit(1);
  }
  shared_data = (struct SharedData *)shmat(shmid, NULL, 0);
  if (shared_data == (struct SharedData *)-1) {
    perror("shmat");
    exit(1);
  }

  shared_data->total_pairs = N;
  shared_data->task_index = 0;
  pthread_mutex_init(&mutex, NULL);
  sem_init(&shared_data->sem1, 1, 1);
  sem_init(&shared_data->sem2, 1, 0);
  sem_init(&shared_data->sem3, 1, 0);

  for (int i = 0; i < N; i++) {
    printf("Enter pair %d (X Y): ", i + 1);
    scanf("%d %d", &shared_data->X[i], &shared_data->Y[i]);
  }

  pthread_t th1, th2, th3;
  pthread_create(&th1, NULL, Th1, NULL);
  pthread_create(&th2, NULL, Th2, NULL);
  pthread_create(&th3, NULL, Th3, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);

  printf("\nResults:\n");
  printLine();
  printf("Pair\tX\tY\tA\tB\tC\tD\tE\n");
  printLine();
  for (int i = 0; i < N; i++) {
    printf("%d\t%d\t%d\t%d\t%.2f\t%d\t%.2f\t%d\n", i + 1, shared_data->X[i],
           shared_data->Y[i], shared_data->A[i], shared_data->B[i],
           shared_data->C[i], shared_data->D[i], shared_data->E[i]);
  }
  printLine();

  sem_destroy(&shared_data->sem1);
  sem_destroy(&shared_data->sem2);
  sem_destroy(&shared_data->sem3);
  pthread_mutex_destroy(&mutex);
  shmdt(shared_data);
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}
