
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
#include<string.h>

void *name_thread(void *myarg)
{
  int tid, i;
  char ch[6];
  
  tid = *((int *) myarg);
  while(1) {
    //Generating random number to sleep - for half number of threads (Number Divisible by 2.)
    if(tid % 2 == 0) {
      int r = rand()%10;
      sleep(r);
      printf("Second Task:thread %d!\n", tid);
    }
  
    // polling a String after random time interval  - for rest number of threads (Number not divisible by 2.)
    else {
      for(i=0; i<5; i++) {
	ch[i] = (char)(rand()%26 + 64);
      }
    
      int r1 = rand() % 2;
      sleep(r1);
      puts(ch);
    
    }
  }
  return 0;
}


int main(int argc, char** argv)
{

  int tt, i, num_threads;
  int thread_args[10];  // max threads allowed is 10 
  pthread_t threads[10];
  if(argc != 2) {
    printf("Need exactly one arguments !");
    return 1;
  }

  num_threads = atoi(argv[1]);
  if((num_threads < 1) || (num_threads >= 10)){
    printf("error");
    return 2;
  }

  for(i=0; i<num_threads; ++i) {
    thread_args[i] = i;
    tt = pthread_create(&threads[i], NULL, name_thread, (void *) &thread_args[i]);
    
    assert(0 == tt);
  }
  
  for(i = 0; i<num_threads; ++i) {
    tt = pthread_join(threads[i], NULL);
    assert(0 == tt);
  }

  exit(EXIT_SUCCESS);
 
}



  
