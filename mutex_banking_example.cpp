/* Problem Statement :- 
 
  Write a program to simulate deposit/withdraw activities on a
  banking   account:   Initialize   the   beginning   balance   (global
  variable) to 1 million, withdraw 600 thousands, and then deposit
  500 thousands. Create two Posix threads in main(), which call the
  withdraw and the deposit functions respectively. Both withdraw and
  deposit   functions   have   one   parameter,   which   represent   the   amount
  to   withdraw  or   deposit.


*/

/* To see the difference comment the lines having "pthread_mutex" at beginning and then run the program again */

#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

pthread_mutex_t lock;
long balance;

void *withdraw(void *amount){

   pthread_mutex_lock(&lock);

   printf("Balance while withdrawing = %ld\n",balance);

   long deduct=(long)amount;
   balance-=deduct;
   printf("Balance after deduction = %ld\n",balance);

   pthread_mutex_unlock(&lock);

   pthread_exit(NULL);

}

void *deposit(void *amount){	

   pthread_mutex_lock(&lock);
   printf("Balance before depositing = %ld\n",balance);
   long add=(long)amount;
   balance+=add;

   printf("Balance after depositing = %ld\n",balance);

   pthread_mutex_unlock(&lock);

   pthread_exit(NULL);
  
}


int main(){

    //Initialising beginning balance

    balance=1000000;

    pthread_t thread_id1,thread_id2;
    pthread_mutex_init(&lock,NULL);

    void *status;
    int rc;


   
    long amount=500000;
    pthread_create(&thread_id1,NULL,deposit,(void*)amount);
   
   // sleep(0.1);
    amount=600000;
    pthread_create(&thread_id2,NULL,withdraw,(void*)amount);
   
    pthread_join(thread_id1,NULL);
    pthread_join(thread_id2,NULL);

    printf("Main:Final Balance in my account is %ld\n",balance);
    pthread_exit(NULL);

	return 0;
}
