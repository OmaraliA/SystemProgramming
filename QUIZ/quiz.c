/**
	Aru Omarali
	program that copyies the input to the output, where input or output may be from standard input or output

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

extern int errno;
#define len 4096
int main(int argc, char ** argv){
	
	int fd1,fd2;
	int length;
	ssize_t ret;
	ssize_t ret2;
	char buf[len];

	//Do not allow a file to be copied over itself
	if(argv[1]==argv[2]){
		printf("%s\n", "Error! Please write another destination filename");
		return 0;
	}

	//files to open
	fd1 = open(argv[1], O_CREAT | O_RDONLY);

	if (fd1==-1){
		printf("Error Number%d\n", errno);
		perror("Program");
	}

	fd2 = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
	
	if (fd2==-1){
		printf("Error Number%d\n", errno);
		perror("Program");
	}

	//если первый аргумент равен "input", то я ввожу данные и записываю файл
	//имя файла это аргумент 2
	if(argv[1]="input"){
		fgets(buf, len, stdin);
		ret2 = write(fd2, buf, sizeof(buf));

		if (ret2==-1){
			perror("write");		
		}

		//error check of stdin
		if (ferror(stdin)){
			perror("read_error");
			exit(0);
		}
	}
	

	//если второй аргумент равен "input", то я ввожу данные и записываю файл
	//имя файла это аргумент 1
	else if(argv[2]="output"){
		ret = read (fd1, &buf,len);
		if (ret==-1){
			if (errno == EINTR)
				perror ("read");	
		}

		while(ret!=0){
			fputs(buf, stdout);

			if (ferror(stdout)){
				perror("write_error");
				exit(0);
			}
		}
	
	}
	
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
	
