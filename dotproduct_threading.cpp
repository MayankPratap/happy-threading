/* Following Code is for finding dot product of two vectors using multithreading  . 

   Suppose two vectors are A = [ A1,A2,....An] and B=[B1,B2,...Bn]
   
   Then their dot product is A.B=A1*B1 + A2*B2 + .....  An*Bn 

*/


#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

struct ans{

   double *a;     // Represents vector A
   double *b;     // Represents vector B
   double sum;    // Final result will be stored
   int veclen;   // veclen is the length of summation that a single thread has to handle 

};

struct ans dotdata;

pthread_mutex_t lock;


#define NUM 5
#define VECLEN 100

pthread_t threads[NUM];

void *dotprod(void *arg){

   int start,end,len;

   long offset;

   double mysum,*x,*y;

   offset=(long)arg;

   len=dotdata.veclen;

   start=offset*len;

   end=start+len;

   x=dotdata.a;

   y=dotdata.b;

   mysum=0;

   for(long i=start;i<end;++i){

       mysum+=x[i]*y[i];

   }

   // I have used mutex lock just for practice , they do not serve any purpose here.

   pthread_mutex_lock(&lock);

   dotdata.sum+=mysum;

   pthread_mutex_unlock(&lock);


   pthread_exit(NULL);

}

int main(){

    long i;

    double *a,*b;

    a=(double*)malloc(NUM*VECLEN*sizeof(double));
    b=(double*)malloc(NUM*VECLEN*sizeof(double));
  
    /*
         I am initialising my vectors as A=[1,1,....1] and B=[1,1,.....1]
     
    */


    for(long i=0;i<VECLEN*NUM;++i){

        a[i]=1.0;
        b[i]=a[i];
    }

    dotdata.veclen=VECLEN;
    dotdata.a=a;
    dotdata.b=b;
    dotdata.sum=0;

    pthread_mutex_init(&lock,NULL);

    for(long i=0;i<NUM;++i){

       pthread_create(&threads[i],NULL,dotprod,(void*)i);
    }


    for(long i=0;i<NUM;++i){

       pthread_join(threads[i],NULL);

    }
 
    printf("Sum= %lf\n",dotdata.sum);

    free(a);
    free(b);

    pthread_mutex_destroy(&lock);

    pthread_exit(NULL);

	return 0;
}
