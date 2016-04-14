#include<bits/stdc++.h>
using namespace std;

#define NUM 10

void *printHello(void *threadid){

    long tid;

    tid=(long)threadid;

    for(int i=0;i<5;++i){

       printf("Hello World!It's me, thread %ld\n",tid);

    }
 
    pthread_exit(NULL);

}

int main(){
	
    pthread_t threads[NUM];

    int rc;

    long t;

    for(t=0;t<NUM;t++){

       printf("Main:I am creating thread %ld\n",t);
       rc=pthread_create(&threads[t],NULL,printHello,(void*)t);
    }

    pthread_exit(NULL);
	return 0;
}
