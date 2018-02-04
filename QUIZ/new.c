/**
    Aru Omarali
    program that copyies the source code of the input to the output file
*/

#include <stdio.h>
int main() {
    FILE *fp;
    char c;
    fp = fopen("quiz.c","r");

    do {
         c = getc(fp);
         putchar(c);

         //fputs(c, stdout);
    }

    while(c != EOF);
        fclose(fp);
return 0;
}