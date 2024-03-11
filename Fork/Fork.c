#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	printf("PARENT\n");
	for(int i=0;i<2;i++){
		pid_t child;
		if((child>fork())==0){
			printf("CHILD %d\n",i+1);
			return 0;
		}
		else if(child<0){
		        printf("Error! In creating CHILD %d\n",i+1);
			return 0;
		}
	}
	return 0;
}
