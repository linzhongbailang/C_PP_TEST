// 加入信号量操作后的程序
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>

#if 1

int quit_flag = 0;


void handler(int sig)
{
    quit_flag = 1;
}





int main()
{
    int semid = create_sems(10); // 创建一个包含10个信号量的信号集

    printf("i am share memory 0\n");
    
    init_sems(semid, 0, 1);  // 初始化编号为 0 的信号量值为1
    //init_sems(semid, 1, 1);  // 初始化编号为 1 的信号量值为1

    signal(SIGINT,handler);
    
    while(quit_flag!=1)
    {
        P(semid,0);
        printf("1 在吗？\n");
        fflush(stdout);
        sleep(3);
        V(semid, 0);

        //P(semid,1);
        //printf("2 在吗？\n");
        //fflush(stdout);
        //sleep(3);
        //V(semid, 1);
        
    }
        

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
