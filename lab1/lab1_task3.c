#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd, ret;
    char word[100];
    fd = open(argv[0], O_WRONLY | O_APPEND | O_CREAT);

    if(fd == -1){
        perror("open");
    }
    ret = write(fd, text, strlen(text));
    if(ret == -1){
        perror("write");
    }
    if(close(fd) == -1){
        perror("close");
    }
    return 0;
}