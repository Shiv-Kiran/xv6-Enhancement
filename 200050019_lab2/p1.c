#include<stdio.h>
#include <unistd.h>


int main(){
	int pid = fork();
	if(pid!=0){
	
		printf("Parent: My process ID is:%d \n",getpid());
		printf("Parent: The child process ID is:%d \n",pid);}
		else{
		printf("Child: MY process ID is:%d \n",getpid());
		printf("Child: The parent process ID is:%d \n",getppid());
		}
	

    return 0;
}
