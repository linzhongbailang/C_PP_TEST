#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define IMAGE_X       736
#define IMAGE_Y       480



#define ROI_X1              2
#define ROI_Y1              2
#define ROI_X2              IMAGE_X-2
#define ROI_Y2              IMAGE_Y-2



#define IMAGE_X_VAILD       (ROI_X2-ROI_X1)//700
#define IMAGE_Y_VAILD       (ROI_Y2-ROI_Y1)






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

static int intnv12_save(int x,int y,int x_vail,int y_vail,char *data,char * file_name)
{
    
    int ret=0;
    FILE * fp_yuv;
    int index=0;
    
    
    //open file 
    fp_yuv = fopen(file_name, "wb");
	if (!fp_yuv) {
        printf("------%s Could not open %s\n", __func__,file_name);
   	}
    else
    {
        char * dest_data=malloc(x_vail*y_vail*3/2);
        if(dest_data==NULL)
        {
            printf("------%s (%d)   Could not malloc file data buf \n", __func__,__LINE__);
            fclose(fp_yuv);
            return 0;
        }
        
        //save y
        for(int i=0;i<y;i++)
        {
            memcpy(dest_data+i*x_vail,data+i*x,x_vail);
        }
        //save uv
        for(int i=0;i<y/2;i++)
        {
            memcpy(dest_data+x_vail*y+i*x_vail,data+y*x+i*x,x_vail);
                

        }
        fwrite(dest_data, 1, x_vail*y*3/2, fp_yuv);
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
static int nv12_roi(char *src_data,int origin_wid,int origin_height,char *des_data,int start_x,int start_y,int end_x,int end_y)
{
    int roi_wid=end_x-start_x;
    int roi_height=end_y-start_y;
    //提取y
    for(int i=start_y;i<end_y;i++)
    {
        memcpy(des_data+i*roi_wid,src_data+i*origin_wid+start_x,roi_wid);
    }
    //提取 uv
    for(int i=start_y/2;i<end_y/2;i++)
    {
        memcpy( des_data+roi_wid*(end_y-start_y)+i*(end_x-start_x),
                src_data+origin_wid*origin_height+i*origin_wid+start_x,
                end_x-start_x);
    }

}
static int nv12_yuv_4s_pro(char * data,int image_index)
{
    //static int image_idex=0;
    char file_name[50]={0,};
    char * roi_data;

    roi_data=malloc((ROI_Y2-ROI_Y1)*(ROI_X2-ROI_X1)*3/2);
    if(roi_data==NULL)
    {
        printf("------%s malloc roi data failed\n", __func__);
        return -1;
    }
        
    
    memset(file_name,0,sizeof(file_name));
    memset(roi_data,0,(ROI_Y2-ROI_Y1)*(ROI_X2-ROI_X1)*3/2);
    //sprintf(file_name,"NV12_%dx%d_front_%d.yuv",IMAGE_X,IMAGE_Y,image_index);
    //Image_save(file_name,data,IMAGE_X*IMAGE_Y*3/2);
    sprintf(file_name,"NV12_%dx%d_front_%d.yuv",IMAGE_X_VAILD,IMAGE_Y_VAILD,image_index);
    //intnv12_save(IMAGE_X,IMAGE_Y,IMAGE_X_VAILD,IMAGE_Y_VAILD,data,file_name);
    nv12_roi(data, IMAGE_X, IMAGE_Y, roi_data, ROI_X1, ROI_Y1, ROI_X2,ROI_Y2);
    Image_save(file_name,roi_data,(ROI_X2-ROI_X1)*(ROI_Y2-ROI_Y1)*3/2);


#if 1    
    memset(file_name,0,sizeof(file_name));
    memset(roi_data,0,(ROI_Y2-ROI_Y1)*(ROI_X2-ROI_X1)*3/2);
    //sprintf(file_name,"NV12_%dx%d_rear_%d.yuv",IMAGE_X,IMAGE_Y,image_index);
    //Image_save(file_name,data+IMAGE_X*IMAGE_Y*3/2,IMAGE_X*IMAGE_Y*3/2);
    sprintf(file_name,"NV12_%dx%d_rear_%d.yuv",IMAGE_X_VAILD,IMAGE_Y_VAILD,image_index);
    //intnv12_save(IMAGE_X,IMAGE_Y,IMAGE_X_VAILD,IMAGE_Y_VAILD,data+IMAGE_X*IMAGE_Y*3/2*1,file_name);
    nv12_roi( data+IMAGE_X*IMAGE_Y*3/2*1, IMAGE_X, IMAGE_Y,roi_data, ROI_X1, ROI_Y1, ROI_X2,ROI_Y2);
    Image_save(file_name,roi_data,(ROI_X2-ROI_X1)*(ROI_Y2-ROI_Y1)*3/2);

    memset(file_name,0,sizeof(file_name));
    memset(roi_data,0,(ROI_Y2-ROI_Y1)*(ROI_X2-ROI_X1)*3/2);
    //sprintf(file_name,"NV12_%dx%d_left_%d.yuv",IMAGE_X,IMAGE_Y,image_index);
    //Image_save(file_name,data+IMAGE_X*IMAGE_Y*3/2*2,IMAGE_X*IMAGE_Y*3/2);
    sprintf(file_name,"NV12_%dx%d_left_%d.yuv",IMAGE_X_VAILD,IMAGE_Y_VAILD,image_index);
    //intnv12_save(IMAGE_X,IMAGE_Y,IMAGE_X_VAILD,IMAGE_Y_VAILD,data+IMAGE_X*IMAGE_Y*3,file_name);
    nv12_roi(data+IMAGE_X*IMAGE_Y*3/2*2, IMAGE_X, IMAGE_Y, roi_data, ROI_X1, ROI_Y1, ROI_X2,ROI_Y2);
    Image_save(file_name,roi_data,(ROI_X2-ROI_X1)*(ROI_Y2-ROI_Y1)*3/2);

        
    memset(file_name,0,sizeof(file_name));
    memset(roi_data,0,(ROI_Y2-ROI_Y1)*(ROI_X2-ROI_X1)*3/2);
    //sprintf(file_name,"NV12_%dx%d_rigth_%d.yuv",IMAGE_X,IMAGE_Y,image_index);
    //Image_save(file_name,data+IMAGE_X*IMAGE_Y*3/2*3,IMAGE_X*IMAGE_Y*3/2);
    sprintf(file_name,"NV12_%dx%d_rigth_%d.yuv",IMAGE_X_VAILD,IMAGE_Y_VAILD,image_index);
    //intnv12_save(IMAGE_X,IMAGE_Y,IMAGE_X_VAILD,IMAGE_Y_VAILD,data+IMAGE_X*IMAGE_Y*3*3/2,file_name);
    nv12_roi(data+IMAGE_X*IMAGE_Y*3/2*3, IMAGE_X, IMAGE_Y,roi_data,  ROI_X1, ROI_Y1, ROI_X2,ROI_Y2);
    Image_save(file_name,roi_data,(ROI_X2-ROI_X1)*(ROI_Y2-ROI_Y1)*3/2);
#endif    
    printf("------%s fwrite NV12_xx_%d.yuv done\n", __func__,image_index);


}



int main(int argc, char **argv)
{
    int ret=0;
    FILE * fp_nv12_video;
    int image_index=0;

    
	printf("%s start\n",argv[0]);
    
    //open file 
    fp_nv12_video = fopen("nv12_736x480_00.yuv", "r");
	if (!fp_nv12_video) {
        printf("------%s (%d)  Could not open src file\n", __func__,__LINE__);
        return -1;
    }
    
    
    
    //
    char * file_data=(char *)malloc(IMAGE_X*IMAGE_Y*6);
    if(file_data==NULL)
    {
        printf("------%s (%d)   Could not malloc file data buf \n", __func__,__LINE__);
        fclose(fp_nv12_video);
        return -1;
    }
    
           
    while(1)
    {
        memset(file_data,0,IMAGE_X*IMAGE_Y*6);
        //camera_image_save();
        fread(file_data,IMAGE_X*IMAGE_Y*6,1,fp_nv12_video);
        if(feof(fp_nv12_video)!=0)
        {
            printf("------%s (%d)   read over\n", __func__,__LINE__);    
            break;
        }

        //
        nv12_yuv_4s_pro(file_data,image_index++);
        
        
    }
    free(file_data);
    
	printf("%s exit\n",argv[0]);
}
