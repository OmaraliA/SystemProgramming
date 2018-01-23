#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

char text1[]="Hello,world!";
char text2[]="file with holes";

int main(int argc, const char *argv[])
{
	
	int fd,len,fd2,fd3;
	off_t ret,ret1,ret2;
	unsigned long *buf;
	ssize_t wn1,wn2;

	int i, err;
	unsigned long holeSize = 0;
	
	fd = open("hole.txt", O_CREAT|O_WRONLY|O_RDONLY);
	fd2 = open("with_holes.txt", O_CREAT | O_WRONLY |O_RDONLY);
	fd3 = open("without_holes.txt", O_CREAT | O_WRONLY|O_RDONLY);
	if (fd==-1){
			printf("Error Number%d\n", errno);
			perror("Program");
	}

	wn1 = write(fd, text1 , strlen(text1));
	if (wn1==-1){
		perror("write");		
	}

	ret = lseek (fd, 40, SEEK_SET);
	if (ret==-1){
		perror("lseek");
	}

	wn2 = write(fd, text2, strlen(text2));
	if (wn2==-1){
		perror("write");		
	}

	//copy with holes to the another file with_holes.txt
	while (len != 0 && (ret1 = read (fd, buf, len)) != 0) {
		if (ret1==-1){
			if (errno == EINTR)
				continue;
				perror ("read");
				break;
			}

			if((read (fd, buf, len)) == ' '){
				break;
			}
		}
	len -= ret1;
	buf += ret1;
	ret2 = write(fd2, buf, ret1);

	if (ret2==-1){
		perror("write");		
	}

	close(fd);
	close(fd2);

	if (close(fd)==-1){
		perror("close");
	}

return 0;
}