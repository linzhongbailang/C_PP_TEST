#include <stdlib.h>
#include <stdio.h>
#include <string.h>



static int Image_save(char * file_name,unsigned char *data_ptr,int len)
{
    int ret=0;
    FILE * fp_yuv;
    
    //open file 
    fp_yuv = fopen(file_name, "wb");
	if (!fp_yuv) {
        printf("------%s Could not open %s\n", __func__,file_name);
   	}
    else
    {
        fwrite(data_ptr, 1, len, fp_yuv);
        fclose(fp_yuv);

    }

    return 1;
}



static int camera_image_save(void)
{
    static int image_idex=0;
    static int save_num=0;
    char file_name[50]={0,};
    unsigned char data[6]={1,2,3,4,5,6};
    
    image_idex++;
    if(image_idex%100==0)
    {
        //save 4 camera image files
        save_num++;
        if(save_num<=9){
            memset(file_name,0,sizeof(file_name));
            sprintf(file_name,"camera1_1280x720_%d.yuv",save_num);
            Image_save(file_name,data,5);
        
            memset(file_name,0,sizeof(file_name));
            sprintf(file_name,"camera2_1280x720_%d.yuv",save_num);
            Image_save(file_name,data,5);
        
            memset(file_name,0,sizeof(file_name));
            sprintf(file_name,"camera3_1280x720_%d.yuv",save_num);
            Image_save(file_name,data,5);
        
            memset(file_name,0,sizeof(file_name));
            sprintf(file_name,"camera4_1280x720_%d.yuv",save_num);
            Image_save(file_name,data,5);
            
            printf("------%s fwrite 1280x720_00.yuv done\n", __func__);
        }
    }



}



int main(int argc, char **argv)
{
	printf("linux app test \n");

    while(1)
    {

        camera_image_save();
    }

}
