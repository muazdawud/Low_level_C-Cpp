#include<stdio.h>

const char* getString(void){
	static char array[] = "Hello World.";

	return array;
}

int main(void){

	const char* buffer = getString();

	printf("String is = %s\n", buffer);

	return 0;
}