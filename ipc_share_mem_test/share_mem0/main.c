// 加入信号量操作后的程序
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>


#if 1


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
int destroy_sharememory(int id)
{
	return shmctl(id,IPC_RMID,NULL);
}


int quit_flag = 0;


void handler(int sig)
{
    quit_flag = 1;
}





int main()
{
    int semid = create_sems(10); // 创建一个包含10个信号量的信号集
    int ret=0;
    int share_mem_id;
    
    printf("i am share memory 0\n");
    
    init_sems(semid, 0, 1);  // 初始化编号为 0 的信号量值为1
    //init_sems(semid, 1, 1);  // 初始化编号为 1 的信号量值为1
    
    share_mem_id=create_ipc(SHARE_MEM_SIZE);
    if(share_mem_id==-1)
    {
        printf("create ipc error");
        return -1;    
    }
    unsigned char *share_mem_addr=shmat(share_mem_id,NULL,0);
    if(share_mem_addr<0)
    {
        printf("shmat eroor \n ");
        return -1;
    }
    
    signal(SIGINT,handler);
    
    while(quit_flag!=1)
    {
        P(semid,0);
        printf("write data to share mem\n");
        memset(share_mem_addr,0,SHARE_MEM_SIZE);
        for(int i=0;i<SHARE_MEM_SIZE;i++)
        {
            share_mem_addr[i]=i;
        }
        
        fflush(stdout);
        sleep(3);
        V(semid, 0);

        //P(semid,1);
        //printf("2 在吗？\n");
        //fflush(stdout);
        //sleep(3);
        //V(semid, 1);
        
    }
        
    shmctl(share_mem_id,IPC_RMID,NULL);
    destroy_sems(semid);
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
