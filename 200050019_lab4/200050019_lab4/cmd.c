#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){

    int c = fork();
    if (c!=0){
        wait();
        exit();
    }else{
        char * args[argc];
        for(int i=0;i<argc;i++){
            args[i-1] = argv[i];
        }
        exec(args[0], args);
        exit();
    }
}