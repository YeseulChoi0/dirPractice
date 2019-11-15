#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
  DIR * dir = opendir("./");
  int type = 0;
  struct dirent * nextFile = readdir(dir);
  struct stat file;
  //char * name = "";
  int totSize = 0;
  while (nextFile != NULL){
    char * name = nextFile -> d_name;
    printf("name: %s\t", name);
    type = nextFile -> d_type;
    char * dispType = (type == 4) ? "directory" : "file";
    printf("type: %s \t", dispType);
    if (type != 4){
      stat(name, &file);
      printf("size: %lld bytes", file.st_size);
      totSize += file.st_size;
    }
    printf("\n");
    nextFile = readdir(dir);
  }
  printf("total size of all normal files: %d\n", totSize);
  closedir(dir);
  return 0;
}
