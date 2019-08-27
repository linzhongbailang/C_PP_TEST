// 加入信号量操作后的程序
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>

#if 1
int main()
{
    int sem_id = get_sems(0);
    if(sem_id<0)
        return -1 ;

    printf("i am share memory 1 \n");
    while(1)
    {
        P(sem_id, 0); // 对该信号量集中的0号信号  做P操作
        printf("你好 i am 1\n");
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
