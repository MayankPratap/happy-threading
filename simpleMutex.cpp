/* A simple program to see use of mutex in thread synchronisation 
  
   Remove the lines having pthread_mutex in beginning to see the problem we face if no mutex 
   
*/   



#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

int counter;

pthread_mutex_t lock;

void *doSomething(void *arg){

   pthread_mutex_lock(&lock);

   counter+=1;

   printf("Thread %d started\n",counter);

   sleep(1);

   printf("Thread %d finished\n",counter);	

   pthread_mutex_unlock(&lock);

}

int main(){

   pthread_t threads[2];

  // pthread_mutex_init(&lock,NULL);

   int i=0;
  
   while(i<2){

      pthread_create(&threads[i],NULL,doSomething,NULL);
      ++i;
   }

   pthread_join(threads[0],NULL);
   pthread_join(threads[1],NULL);

 //  pthread_mutex_destroy(&lock);

   return 0;
}
