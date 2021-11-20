#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/shm.h>

#define chave 6000

int main() {

  key_t id = shmget(chave, 10*sizeof(int), IPC_CREAT | 0777);

  int *v = (int *) shmat(id, NULL, 0);

  int sleepTimeP1 = 0;

  sleep(sleepTimeP1);

  for(int i=0; i<10; i++){
    printf("%d %d\n", getpid(), v[i]);
  }

  return 0;

}