#include<stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include <stdlib.h>

int main(){
	int id = fork();
	if (id!=0){
	printf("Parent: My process ID is: %d \n",getpid());
	printf("Parent: The child process ID is : %d \n", id);
	
	}else{
	printf("Child: My process ID is : %d \n",getpid());
	printf("Child: The parent process ID is: %d \n",getppid());
	sleep(5);
	printf("/n");
	printf("Child: After sleeping for 5 seconds \n");
	printf("Child: My process ID is: %d \n",getpid());
	printf("Child: The parent process ID is: %d \n \n",getppid());
	
	
	}

}


