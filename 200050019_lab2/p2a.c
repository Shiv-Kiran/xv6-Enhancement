#include<stdio.h>
#include <unistd.h>


int main(){
	int n; scanf("%d",&n);
	int pid = fork();
	for(int i=1;i<n+1;i++){
		if(pid==0) printf("%d %d \n",i,getpid());
		else printf("%d %d \n", i+n, getpid());
	}

    return 0;
}
