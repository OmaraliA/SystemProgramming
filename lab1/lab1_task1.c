#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

extern int errno;

int main(int argc, char ** argv){
	
	int fd1,fd2;
	int len;
	ssize_t ret;
	ssize_t ret2;
	unsigned long *buf;

	char * file1 = argv[1];
	char * file2 = argv[2];

	//Do not allow a file to be copied over itself
	if(file1 == file2){
		printf("%s\n", "Error! Please write another destination filename");
		return 0;
	}

	//files to open
	fd1 = open(arg1, O_CREAT | O_RDONLY);
	fd2 = open(arg2, O_CREAT | O_WRONLY);

	if (fd1==-1){
			printf("Error Number%d\n", errno);
			perror("Program");
	}

	//non-blocking reading
	while (len != 0 && (ret = read (fd1, buf, len)) != 0) {
		if (ret==-1){
			if (errno == EINTR)
				continue;
				perror ("read");
				break;
			}
	}

	len -= ret;
	buf += ret;
	ret2 = write(fd2, buf, ret);

	if (ret2==-1){
		perror("write");		
	}

	close(fd1);
	close(fd2);

	if (close(fd1)==-1||close(fd2)==-1){
		perror("close");
	}
	return 0;
}
	