#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/shm.h> 

 //p2

 #define chave 6000

 int main(){

   int sleepTimeP2 = 0;

   sleep(sleepTimeP2);

   key_t id = shmget(chave, 10*sizeof(int), IPC_CREAT | 0777);

   int *v = (int *) shmat(id, NULL, 0);

   v[0] = 1;
   v[1] = 1;

   for(int i=2; i<10; i++){
      v[i] = v[i-1] + v[i-2];
   }

   return 0;

 }