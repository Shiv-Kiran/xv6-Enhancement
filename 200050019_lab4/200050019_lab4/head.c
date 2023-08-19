#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void head(int fd, int no_lines){
  int n;
  int lines = 0;
  while ((n = read(fd, buf, sizeof(buf))) > 0){
    if (lines == no_lines){
      exit();
    }
    for (int i = 0; i < n; i++){
      if (buf[i] == '\n'){
        lines++;
        if (lines == no_lines){
          exit();
        }
      }
      if (write(1, buf + i, 1) != 1){
        printf(1, "cat: write error\n");
        exit();
      }
      
    }
  }
  if (n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int main(int argc, char *argv[]){

  int fd, i;

  int no_lines = atoi(argv[1]);

  if (argc <= 1){
    head(0, 0);
    exit();
  }
  else if (argc == 2){
    head(0, no_lines);
    exit();
  }

  for (i = 2; i < argc; i++){
    printf(1, "-----%s-----\n", argv[i]);
    if ((fd = open(argv[i], 0)) < 0){

      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    head(fd, no_lines);
    close(fd);
  }
  exit();
}