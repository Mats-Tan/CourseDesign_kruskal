#include <stdio.h>

int main(int avgr,char* agrc[]){
	if(avgr >1){
		printf("%s\n",*(++agrc));
	}else{
		printf("ERROR\n");
	}
	return 0;

}