#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RP 0
#define WP 1
int sieve(int pipe[2]);

void main(int argc,char* argv[])
{

  // first feed the data into pipe
  int init[2];
  pipe(init);

  if(fork()==0){
    // in the child process 
    // 1.close the parent write
    // 2.get the prime
    close(init[WP]);

    sieve(init);
    
    close(init[RP]);
    wait(0);
    exit(0);

  }else{
    close(init[RP]);
    for(int i=2;i<=35;i++){
      //feed into pipe
      write(init[WP],&i,sizeof(i));
    }
    close(init[WP]);
    wait(0);
    exit(0);
  }
}

int sieve(int source[2])
{
  int prime=0;
  int status = read(source[RP],&prime,sizeof(prime));
  if(status > 0){
    fprintf(1,"prime %d\n",prime);
  }else{

   return 0; 

 }

  int neightbor=0;
  int flag = 0;
  int child_pipe[2];


  while(read(source[RP],&neightbor,sizeof(neightbor)) && neightbor!=0){
    //check other data
    if((neightbor % prime) != 0){
      if(flag==0){
        pipe(child_pipe);
        flag=1;
        if(fork()==0){
          // close the grandpa pipe
          close(source[RP]);
          
         // close the parent pipe 
          close(child_pipe[WP]);
          sieve(child_pipe);
          close(child_pipe[RP]);
          wait(0);
          exit(0);

          //exit(0);
        }else{
          // close pipe in parent process
          close(child_pipe[RP]);
        }
      }
      write(child_pipe[WP],&neightbor,sizeof(neightbor));
    }
  }  
  close(child_pipe[WP]);
  return 0 ; 
}

