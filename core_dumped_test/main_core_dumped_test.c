#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void core_test1()
{
    int array[10];
    int i = 0;
    
    printf("%d\n", i);
    //below will call segmentfault
    for(i=0;i<100;i++)
    {
        array[i]=i;
    }
}





int main(int argc, char **argv)
{
	printf("welcome to %s \n",argv[0]);


    core_test1();
    //while(1)
    {

        //camera_image_save();
    }

    return 1;

}
