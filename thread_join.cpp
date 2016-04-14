#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

#define NUM 4

void *BusyWork(void *t){

   int i;

   long tid;

   double result=0.0;

   tid=(long)t;

   printf("Thread %ld starting ...\n",tid);

   for(i=0;i<1000000;++i) 
        result=result+sin(i)*tan(i);

   printf("Thread %ld done.Result=%lf\n",tid,result);

   pthread_exit((void*)t);

   // pthread_exit(NULL);
}

int main(){
 
 

   pthread_t thread[NUM];

   pthread_attr_t attr;

   int rc;
   long t;
   void *status;

   /* Initialise thread attribute */

   pthread_attr_init(&attr);

   /* Set thread detached attribute */ 

   pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

  for(t=0;t<NUM;t++){

    printf("Main:Creating thread %ld\n",t);

    rc=pthread_create(&thread[t],&attr,BusyWork,(void*)t);
  
    //  rc=pthread_create(&thread[t],NULL,BusyWork,(void*)t);

  }

  /* Free attributes and wait for other threads */

  for(t=0;t<NUM;t++){

     rc=pthread_join(thread[t],&status);

     printf("Main:Completed join with thread %ld having a status of %ld\n",t,(long)status);

  } 

   printf("Main:Program Completed.Exiting.\n");

   
   pthread_exit(NULL);


   return 0;
}
