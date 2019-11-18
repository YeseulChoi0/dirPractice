#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
  char directory [1000];
  //printf("At least this :( \n");
  if (argc == 1){
    fgets(directory, 1000, stdin);
    directory[strlen(directory) - 1] = '\0';
  }else{
    strcpy(directory, argv[1]);
  }
  //printf("directory: 1%s1\n", directory);

  //printf("j\n");
  DIR * dir = opendir(directory);
  if (errno > 0){
    printf("%s\n", strerror(errno));
    exit(0);
  }
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
