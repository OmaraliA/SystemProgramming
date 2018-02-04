
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#define MAXLINE 4

int main(void)
{
	char buf[MAXLINE];

	fgets(buf, MAXLINE, stdin);
	fputs(buf, stdout);

	if (ferror(stdin)){
		perror("read_error");
		exit(0);
	}
	
	
}