// 加入信号量操作后的程序
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SHARE_MEM_SIZE 0Xff



int sharememory(int ipc_size,int flag)
{
	int id;
	key_t key=ftok("/tmp",66);
	if(key < 0)
	{
		printf("get key error\n");
		return -1;
	}
	id = shmget(key,ipc_size,flag);
	if(id < 0)
	{
		printf("get id error\n");
		return -1;
	}
	return id;
}
 
int create_ipc(int ipc_size)
{
	return sharememory(ipc_size,IPC_CREAT|IPC_EXCL|0666);
}
int get_ipc(int ipc_size)
{
	return sharememory(ipc_size,IPC_CREAT|0666);
}


#if 1
int main()
{
    int sem_id = get_sems(0);
    if(sem_id<0)
        return -1 ;

    int ret=0;
    int share_mem_id;
    

    share_mem_id =get_ipc(SHARE_MEM_SIZE);
    if(ret==-1)
        return -1;

    unsigned char *share_mem_addr=shmat(share_mem_id,NULL,0);
    if(share_mem_addr<0)
    {
        printf("shmat eroor \n ");
        return -1;
    }

    printf("i am share memory 1 \n");
    while(1)
    {
        P(sem_id, 0); // 对该信号量集中的0号信号  做P操作
        printf("read share mem\n");
        for(int i=0;i<SHARE_MEM_SIZE;i++)
        {
            if(share_mem_addr[i]!=i)
            {
                printf("share read error index:%d",i);
            }
        }
        fflush(stdout);
        V(sem_id, 0);
    }
    return 0;
}
#else
// 未加信号量的测试代码
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>

int main()
{

    pid_t id = fork(); // 创建子进程
    if( id < 0)
    {
        perror("fork");
        return -1;
    }
    else if (0 == id)
    {// child 
        int sem_id = get_sems();
        while(1)
        {
            printf("你");
            fflush(stdout);
            sleep(1);
            printf("好");
            printf(":");
            fflush(stdout);
            sleep(1);
        }
    }
    else
    {// father
        while(1)
        {
            printf("在");
            sleep(1);
            printf("吗");
            printf("?");
            fflush(stdout);
        }
        wait(NULL);
    }

    return 0;
}


#endif
