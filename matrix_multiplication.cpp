#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;

int n,m,l,a;

int mat1[500][500],mat2[500][500],mat3[500][500];

struct thread_data{

   int thread_id;
   int row;
   int col;

};

struct thread_data thread_data_array[1000000];

void *calc(void *threadarg){

   struct thread_data *my_data;

   my_data=(struct thread_data*)threadarg;

   int taskid=my_data->thread_id;
   int row=my_data->row;
   int col=my_data->col;

   int res=0;

   printf("Hi! I am thread %d\n",taskid);

   for(int i=0;i<m;++i){

       res+=mat1[row][i]*mat2[i][col];
   }

   mat3[row][col]=res;

   pthread_exit(NULL);

}


int main(){
   
  
    printf("Enter dimensions of 1st matrix\n");

    scanf("%d %d",&n,&m);

    printf("Enter dimensions of 2nd matrix\n");

    scanf("%d %d",&a,&l);

    if(a!=m){

       printf("Matrices cannot be multiplied\n");
       
    }

    else{

       printf("Enter values in 1st matrix\n");

       for(int i=0;i<n;++i){
 
          for(int j=0;j<m;++j){

             scanf("%d",&mat1[i][j]);

          }

       }

       printf("Enter values in 2nd matrix\n");

       for(int i=0;i<m;++i){

          for(int j=0;j<l;++j){

             scanf("%d",&mat2[i][j]);

          }

       }

    
    
       const int NUM=n*l;	
       pthread_t threads[NUM];
       pthread_attr_t attr;

       int rc;
       long t=0;

       void *status;

       /* Initialise thread attribute */

       pthread_attr_init(&attr);

       pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);



       for(int i=0;i<n;++i){

            for(int j=0;j<l;++j){

                 printf("Main:I am creating thread %ld to find value of %d row and %d col of result matrix\n",t,i,j);

                 thread_data_array[t].thread_id=t;
                 thread_data_array[t].row=i;
                 thread_data_array[t].col=j;

                 rc=pthread_create(&threads[t],&attr,calc,(void*)&thread_data_array[t]);
                 rc=pthread_join(threads[t],&status); 

                 t++;
            }
       }


       for(int i=0;i<n;++i){

           for(int j=0;j<l;++j)
              printf("%d ",mat3[i][j]);

           printf("\n");
       }

     
    }

      pthread_exit(NULL);    


	return 0;
}
