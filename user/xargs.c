#include<kernel/types.h>
#include<kernel/stat.h>
#include<user/user.h>
#include<kernel/param.h>



void main(int argc, char* argv[]){
  if(argc < 2){
    fprintf(2, "usage xargs pganem args");
  }else{
    char exe_name[64];
    int arg_idx = 0;
    char* new_argv[MAXARG];


    new_argv[arg_idx] = malloc(64);
    strcpy(exe_name,argv[1]);
    for(int i=1;i<argc;i++){

      new_argv[arg_idx] = malloc(64);
      strcpy(new_argv[arg_idx],argv[i]); 
      arg_idx ++;
    }
    // read the std input data
    char single_arg;
    char buf[64];
    int index = 0;

    while( read(0,&single_arg,1) != 0){
      // end of one line
      if(single_arg == '\n'){
        
        buf[index] = 0;
        new_argv[arg_idx] = malloc(index+1);
        strcpy(new_argv[arg_idx],buf);
        arg_idx ++;

        memset(buf,index,0);
        index = 0;
        continue;
      }
      // space which means another argv
      if(single_arg == ' '){
        new_argv[arg_idx] = malloc(index+1);
        
        buf[index] = 0;
        strcpy(new_argv[arg_idx],buf);
        arg_idx ++;
      
        // printf("arg :  %s \n",buf);
        memset(buf,index,0);
        index = 0;
        continue;
      }

      buf[index] = single_arg;
      index ++;
    }
    /*
    for(int j=0;j < arg_idx; j++){
      printf("all argc: %d | argv : %s\n",j,new_argv[j]);
    }
     */
    if(fork()==0){
      exec(exe_name,new_argv);
    }
    wait(0);
    
  }
  exit(0);
}
