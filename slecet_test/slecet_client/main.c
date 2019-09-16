// 加入信号量操作后的程序
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>






int quit_flag = 0;


void handler(int sig)
{
    quit_flag = 1;
}





int main(int argc,char *argv[])
{
    int fd=0;
    char file_name[50];
    int index=0;
    
    printf("%s start\n",argv[0]);
    
    
    signal(SIGINT,handler);
    
    while(quit_flag!=1)
    {
        memset(file_name,0,sizeof(file_name));
        sprintf(file_name,"file%d",index++);
            
        fd = open(file_name,O_RDONLY|O_CREAT,S_IRUSR);
        printf("open %s  fd=%d",fd);
        close(fd);
        sleep(1);
        
    }
        
    
    return 0;
}

