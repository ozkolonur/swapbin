/* TODO use getopt */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <malloc.h>
#include <string.h>

/* abcd --> badc */
void swapBytes(char *buf)
{
    char tmp;
    tmp = *buf;
    *buf = *(buf+1); 
    *(buf+1) = tmp;
    return;
}
/* abcd --> cdab */
void swapWords(char *buf)
{
    char tmp1, tmp2, tmp3, tmp4;
    tmp1 = *buf; tmp2 = *(buf+1); tmp3 = *(buf+2); tmp4 = *(buf+3);
    *buf = tmp3; *(buf+1) = tmp4; *(buf+2) = tmp1; *(buf+3) = tmp2;
    return;
}


int main(int argc, char *argv[])
{
    int fd, bufSize, i;
    struct stat stFileStat;
    char *buf = NULL;
    
    if((fd = open(argv[1], O_RDONLY) ) < 0)
    {
	perror("open");
	goto lException;
    }
    
    if (fstat(fd, &stFileStat) != 0)
    {
	perror("stat");
	goto lException;
    }
    
    if((stFileStat.st_size % 4) != 0)
	bufSize = stFileStat.st_size + (4 - (stFileStat.st_size % 4));
    else
	bufSize = stFileStat.st_size;

    buf = malloc(bufSize);
    memset(buf, 0, bufSize);

    if(read(fd, buf, stFileStat.st_size) < stFileStat.st_size)
    {
	perror("read");
	goto lException;
    }
    close(fd);
    fd = -1;
    
    if(strcmp(argv[2], "-b") == 0)
    {
	printf("Byteswapping %s...", argv[1]);
	for(i=0; i< (bufSize + 1); i=i+2)
	    swapBytes(buf+i);
    }
    else if(strcmp(argv[2], "-w") == 0)
    {
	printf("Wordswapping %s...", argv[1]);
	for(i=0; i< (bufSize + 1); i=i+4)
	    swapWords(buf+i);
    }
    else 
    {
	printf("Usage: swapbin filename mode\nModes:\t");
	printf("-b byte swapping\n\t-w word swapping\n");
	goto lException;
    }
    printf("OK\n");
    if((fd = open(argv[1], O_WRONLY) ) < 0)
    {
	perror("open");
	goto lException;
    }

    if(write(fd, buf, bufSize) < bufSize)
    {
	perror("read");
	goto lException;
    }

    close(fd);
    fd = -1;

//    if(buf != NULL)
//	free(buf);
    
    return 0;

lException:
printf("%d\n", __LINE__);
    if (fd = -1)
	close(fd);
printf("%d\n", __LINE__);
    if(buf != NULL)
	free(buf);
    return -1;
}


