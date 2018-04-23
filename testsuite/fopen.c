#include "stdio.h"

int main(){

	FILE *fp;
	fp = fopen("fopen.c","r");
	fclose(fp);

	return 0;
}
