#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

extern int errno;

int main(int argc, char ** argv){
	int choice;
	int fd1,fd2;
	int length;
	ssize_t ret;
	ssize_t ret2;
	int len;
	 
    printf("\n\n Please, enter the buffer size :");
    scanf("%d",&len);

	char buf[len];

	if(argv[1]==argv[2]){
		printf("%s\n", "Error! Please write another destination filename");
		return 0;
	}

	//files to open
	fd1 = open(argv[1], O_CREAT | O_RDONLY);
	fd2 = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);

	if (fd1==-1){
		printf("Error Number%d\n", errno);
		perror("Program");
	}

	if (fd2==-1){
		printf("Error Number%d\n", errno);
		perror("Program");
	}

	//non-blocking reading
	while ((ret = read (fd1, &buf,len))) {
		if (ret==-1){
			if (errno == EINTR)
				continue;
				perror ("read");
				break;
		}
		ret2 = write(fd2, &buf, ret);
		if (ret2==-1){
		perror("write");		
	}	
	}
	if (close(fd1)==-1){
		perror("close");
	}

	if(close(fd2)==-1){
		perror("close");
	}
	return 0;
}
	
