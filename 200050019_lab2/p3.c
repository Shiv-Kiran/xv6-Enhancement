#include<stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include <stdlib.h>



int main(){
	while(1){
		int process_id = fork();
		if(process_id ==0){
			printf(">>>");
			char str[50] ;
			scanf("%[^\n]s",str);
			char* args[] = {str,NULL};

			execv(args[0],args);
			printf("This should not be printted");
			exit(0);
		}else
			wait(NULL);
	
	
	
	}

	
	
}
