#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
void findFromDir(char* path, char* name);

void main(int argc, char* argv[]){
  if(argc!=3){
    fprintf(2,"usage: find filepath ...");
    exit(1);
  }else{
    char* path = argv[1];
    char* name = argv[2];
    findFromDir(path,name); 
    exit(0);
 }
}



void findFromDir(char *path, char *name){
  char buf[128],*p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path,0))<0){
    fprintf(2, "find : cannot open %s\n",path);
  }

  if(fstat(fd,&st) < 0){
    fprintf(2, "find cannot stat %s\n",path);
    close(fd);
  }
  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
    printf("find : path too long \n");
  }

  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/';
  while( read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)
      continue;
    
    if(strcmp(".",de.name) == 0 || strcmp("..",de.name) == 0){
      continue;
    }
    // concat the file path
    memmove(p,de.name,DIRSIZ);
    p[DIRSIZ] = 0;
    
    if(stat(buf,&st) < 0){
      printf("find : cannot stat %s \n", buf);
      continue;
    }
    
    if(st.type == T_DIR ){
      findFromDir( buf,name);
      continue;
    }
    
    if(strcmp(de.name,name) == 0){
      printf("%s\n",buf);
    }

  }

  close(fd);
}
