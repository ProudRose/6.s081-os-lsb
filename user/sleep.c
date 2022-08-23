#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char* argv[]){
  if(argc <=1){
    fprintf(2,"usage: sleep number...\n");
    exit(1);
  }

  int tick = atoi(argv[1]);
  if(tick == 0){
    fprintf(2, "please input write number");
    exit(1);
  }

  sleep(tick);
  exit(0);
}


