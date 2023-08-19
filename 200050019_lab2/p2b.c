#include<stdio.h>
#include <unistd.h>
#include<sys/wait.h>


int main(){
	int n; scanf("%d",&n);
	int pid = fork();
	if(pid == 0){
	for(int i=1;i<n+1;i++)
		 printf("C %d %d \n",getpid(), i);
		 }
	else {
	wait(NULL); // asking to make child wait
	for(int i=1;i<n+1;i++)	
		printf("P %d %d \n", getpid(),  i+n);
	}

    return 0;
}
