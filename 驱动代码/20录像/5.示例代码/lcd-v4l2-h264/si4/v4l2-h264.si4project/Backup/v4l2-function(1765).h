#ifndef __V4L2_FUNCTION_H__
#define __V4L2_FUNCTION_H__

#include <linux/videodev2.h>


/* 清0变量宏 */
#define CLEAR(x) memset (&(x), 0, sizeof (x))

/* 定义摄像头设备文件，根据实际情况修改 */
#define VIDEO_DEVICE     "/dev/video1"

/* 定义图宽度,高度        */
#define VID_IMG_W      320  //640     
#define VID_IMG_H      240  //480 


/*自定义视频缓冲区数据结构*/
struct buffer {
    void * start;
    size_t length;//buffer's length is different from cap_image_size
};


/********************************************************************
*  Function：     lcd_draw_image_rgb888()
*  Description:   把rgb888图片数据显示在LCD屏上;
*  Calls:         ;
*  Called By:     ；
*  Input：         x , y :转换成RGB后在LCD显示的起始坐标
*                 w,image_height：图像宽，高
*                 rgb_data:rgb数据指针；
*  Output：        none;
*  Return :       0:转换成功   -1: 转换失败。
*  Author:        chenzhifa;        ;
*  Others:        none;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int lcd_draw_image_rgb888( unsigned int x, unsigned int y,
                           unsigned int w,
                           unsigned int h,
                           unsigned char *rgb_data);


/********************************************************************
*  Function：  lcd_show_rgb_image()
*  Description:   LCD显示rgb888图片数据函数;
*  Calls:         ;
*  Called By:     ；
*  Input：         x , y:lcd显示的起始坐标
*                 w , w:图片的宽度，高度
*                 rgb_data:rgb数据缓冲首地址
*  Output：        none;
*  Return :       0：成功；       -1：失败;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int lcd_show_rgb_image(unsigned x, unsigned y,
                       int w, int h,
                       unsigned char *rgb_data);




/********************************************************************
*  Function：     video_mainloop
*  Description:   循环采集数据主程序;
*  Calls:         ;
*  Called By:     ；
*  Input：        none
*  Output：       none;
*  Return :       成功:0;失败:-1;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_mainloop(void);


/********************************************************************
*  Function：      video_device_open
*  Description:   打开摄像头设备;
*  Calls:         ;
*  Called By:     ；
*  Input：      dev:摄像头设备名
*  Output：     none;
*  Return :       -1:失败； >0 : 摄像头文件描述符
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int  video_device_open(const char*dev);


/********************************************************************
*  Function：      video_device_close 
*  Description:   关闭设备;
*  Calls:         ;
*  Called By:     ；
*  Input：         none
*  Output：        none;
*  Return :       0:成功;    -1:失败;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_close(void);



/********************************************************************
*  Function：      video_device_querycap
*  Description:   查询摄设备功能;
*  Calls:         ;
*  Called By:     ；
*  Input：        none;
*  Output：        cap:保存查询结构的v4l2_capability结构体变量地址;
*  Return :       -1:失败； 0: 成功
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_querycap(struct v4l2_capability *cap);


/********************************************************************
*  Function：      video_device_have_cap
*  Description:   判断设备是否具备指定的功能;
*  Calls:         ;
*  Called By:     ；
*  Input：         none;
*  Output：        cap:已经查询有结果的结构的v4l2_capability结构体变量地址;
*                 capability：要查询的功能掩码,如 V4L2_CAP_VIDEO_CAPTURE ;
*  Return :       -1:参数非法； 0: 不支持指定功能; 1：支持指定的功能;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_have_cap(struct v4l2_capability *cap, unsigned int capability);


/********************************************************************
*  Function：      video_device_check_fmt
*  Description:   查询摄像头支持的所有格式，以及判断是否支持指定格式;
*  Calls:         ;
*  Called By:     ；
*  Input：         format_id: 要确认支持是否支持的目标格式id,如 V4L2_PIX_FMT_YUYV
*  Output：        none;
*  Return :       -1:不支持目标格式； 0: 支持目标格式
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_check_fmt(unsigned int  format_id);


/********************************************************************
*  Function：      video_device_set_fmt
*  Description:   设置摄像头数据格式;
*  Calls:         ;
*  Called By:     ；
*  Input：         fmt: 已经填充好的摄像头格式结构指针
*  Output：        none;
*  Return :       -1:设置失败； 0: 设置成功
*  Author:        chenzhifa;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_set_fmt(struct v4l2_format *fmt);


/********************************************************************
*  Function：     video_reqbufs()
*  Description:   申请视频采集缓冲区;
*  Calls:         ;
*  Called By:     ；
*  Input：         nr:缓冲区数量;
*  Output：        none;
*  Return :       >0: 成功,申请到的缓冲区;  -1:失败；
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_reqbufs(unsigned char nr);



/********************************************************************
*  Function：     v4l2_qbuf_req
*  Description:   把缓冲区放入采集队列
*  Calls:         ;
*  Called By:     ；
*  Input：         n_buffers:缓冲区数量
*  Output：       none;
*  Return :      0:成功；-1:失败;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int  video_qbuf_req(int n_buffers);



/********************************************************************
*  Function：     video_buf_mmap()
*  Description:   映射申请视频采集缓冲区;
*  Calls:         ;
*  Called By:     ；
*  Input：          nr:缓冲区数量;
*  Output：        none;
*  Return :       0:成功; -1：失败;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int  video_buf_mmap(unsigned char nr);



/********************************************************************
*  Function：     video_poll_data()
*  Description:   查询是否有数据就绪;
*  Calls:         ;
*  Called By:     ；
*  Input：        none
*  Output：       none;
*  Return :       >0: 有数据；
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_poll_data(void);



/********************************************************************
*  Function：     video_read_frame()
*  Description:   读取一帧数据,把摄像头原始数据取出存放在vbuffer中;
*  Calls:         ;
*  Called By:     ；
*  Input：        none
*  Output：       vbuffer : 数据存放摄像头原始数据的缓冲区;
*  Return :       成功:>=0.缓冲区索引；;失败:-1
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_read_frame(unsigned char *vbuffer);


/********************************************************************
*  Function：     video_start_capturing
*  Description:   启动视频采集
*  Calls:         ;
*  Called By:     ；
*  Input：        none
*  Output：       none;
*  Return :       0: 成功；-1：失败;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_start_capturing(void);


/********************************************************************
*  Function：     video_stop_capturing()
*  Description:   停止视频采集;
*  Calls:         ;
*  Called By:     ；
*  Input：         none
*  Output：        none;
*  Return :       0:成功; 1:失败;
*  Author:        chenzhifa;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_stop_capturing(void);


/********************************************************************
*  Function：      video_device_init()
*  Description:   摄像头初始化，初始化完成后就可以开始读取数据了;
*  Calls:         ;
*  Called By:     ；
*  Input：      video_path: 摄像头设备路径
*  Output：    none;
*  Return :       -1:失败； 0: 成功
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int  video_device_init(const char *video_path);


/********************************************************************
*  Function：     video_device_uninit()
*  Description:   释放视频采集缓冲区映射，释放占用资源;
*  Calls:         ;
*  Called By:     ；
*  Input：        dev:lcd设备名
*  Output：       none;
*  Return :       none
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
void video_device_uninit(int nr);

#endif


