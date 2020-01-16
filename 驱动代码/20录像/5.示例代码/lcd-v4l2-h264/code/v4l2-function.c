#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <linux/videodev2.h>
#include <linux/fb.h>
#include "lcd.h"
#include "color.h"
#include "v4l2-function.h"
#include "h264encoder.h"

#define SHOW_LCD     1    //是否显示图像在LCD屏上
#define  HVAE_YUYV   0  //是否生成yuyv文件  ，1 生成， 0不生成;
#if HVAE_YUYV                //生成yuv文件		
	const char *yuyv_file_name = "./yuyu422.yuyv";	 //测试  yuyv 文件名
	FILE *yuyv_fp;
#endif

const char *h264_file_name = "./yuyu422toh264.h264";   //测试h264文件名
#define FRANE_COUNT   500                              //测试帧数量

#define MOD_NOBLOCK_OPEN   0    //打开方式：非阻塞设置为1，阻塞设置为0


/*定义设备名称指针*/
static  const char * dev_name = NULL;

/*定义文件句柄，本程序中用于/dec/video0 文件打开句柄*/
static  int fd_vd = -1;

/*定义视频缓冲区指针*/
static  struct buffer * buffers = NULL;

/*申请缓冲区数量*/
static  unsigned int nr_nr = 4;

/*帧的格式，比如宽度，高度等*/
static  struct v4l2_format fmt;

/* 定义视频数据缓冲区 */
unsigned char vbuffer[800 * 480 * 4] = {0};
unsigned char yuv_vbuffer[800 * 480 * 4] = {0};


/*错误信息提示*/
static  void  errno_exit(const char * s)
{
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}


/*视频设备控制函数*/
static  int xioctl(int fd, int request, void * arg)
{
    int r;
    do {
        r = ioctl(fd, request, arg);
    } while (-1 == r && EINTR == errno);
    return r;
}


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
                           unsigned char *rgb_data)
{

    unsigned char *temp_src = NULL;
    unsigned char *temp_des = NULL;
    int i, j;

    /* 参数合法性检测 */
    if(!rgb_data ) {
        printf("ERROR!file:%s; line:%d\r\n", __FILE__, __LINE__);
        return -1;
    }

    /* 取得转成rgb后的源数据，因为output_ptr是外部传入的指针，所以此处不直接使用。*/
    temp_src = rgb_data;

    /* 根据 x,y坐标计算图片应该在lcd屏的显示起始位置 */
    temp_des = fbp + vinfo.xres * vinfo.bits_per_pixel / 8 * y + x * vinfo.bits_per_pixel / 8;

    /* 根据图片的高，宽度显示图片在LCD屏上 */
    for(i = 0; i < h; i++) {
        for(j = 0; j < w; j++) {
            //           RGB888        R                  G               B
            unsigned int color = temp_src[2] << 16 | temp_src[1] << 8 | temp_src[0];
            fb_show_pixel(x + j,  y, color);
            temp_src += 3;       //数据指针增加3字节，指向下一个点位置
        }
        y++;  //下一行
    }

    return 0;
}



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
                       unsigned char *rgb_data)
{
    /* 参数合法性检查 */
    if(!rgb_data  || x > vinfo.xres  || y > vinfo.yres ) {
        return -1;
    }

    if(x + w > vinfo.xres ) {
        w = vinfo.xres - x;
    }

    if(y + h > vinfo.yres ) {
        w = vinfo.yres - y;
    }

    /* 显示图像在LCD屏上 */
    lcd_draw_image_rgb888(x, y, w, h, rgb_data);

    return 0;
}




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
int  video_device_open(const char*dev)
{
#if (MOD_NOBLOCK_OPEN)
    fd_vd = open(dev, O_RDWR  | O_NONBLOCK);
#else
    fd_vd = open(dev, O_RDWR);
#endif
    if (-1 == fd_vd) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n", dev_name, errno, strerror(errno));
        return -1;
    }
    return fd_vd;
}




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
int video_device_close(void)
{
    int ret ;
    ret = close(fd_vd);
    if (ret < 0 ) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n", dev_name, errno, strerror(errno));
        return -1;
    }
    fd_vd = -1;
    return 0;
}



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
int video_device_querycap(struct v4l2_capability *cap)
{
    int ret ;
    ret = xioctl(fd_vd, VIDIOC_QUERYCAP, cap);
    if (ret < 0) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s is no V4L2 device\n", dev_name);
        } else {
            fprintf(stderr, "Cannot open '%s': %d, %s\n", "VIDIOC_QUERYCAP", errno, strerror(errno));
            return -1;
        }
        return -1;
    }
    return 0;
}



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
int video_device_have_cap(struct v4l2_capability *cap, unsigned int capability)
{
    int ret ;

    /*判断是参数合法性*/
    if(cap == NULL) {
        fprintf(stderr, "line:%d, %s() Invalid argument\n", __LINE__, __FUNCTION__);
        return -1;
    }

    /* 返回指定的值 */
    ret = !!(cap->capabilities & capability);

    return ret;
}


/********************************************************************
*  Function：      video_device_check_frmsize
*  Description:   获取摄像头所支持的分辨率;
*  Calls:         ;
*  Called By:     ；
*  Input：         format_id: 目标格式id,如 V4L2_PIX_FMT_YUYV
*  Output：        none;
*  Return :       -1:不支持目标格式； 0: 支持目标格式
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_check_frmsize(unsigned int  format_id)
{
    struct v4l2_frmsizeenum frmsize = {0};
    frmsize.pixel_format = format_id;
    frmsize.index = 0;
    while (xioctl(fd_vd, VIDIOC_ENUM_FRAMESIZES, &frmsize) >= 0) {
        if(frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE) {
            printf("DISCRETE: w*h: %dx%d\n", frmsize.discrete.width, frmsize.discrete.height);
        } else if(frmsize.type == V4L2_FRMSIZE_TYPE_STEPWISE) {
            printf("STEPWISE: w*h: %dx%d\n",  frmsize.stepwise.max_width, frmsize.stepwise.max_height);
        }
        frmsize.index++;
    }
    return 0;
}


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
int video_device_check_fmt(unsigned int  format_id)
{
    int  format_is_surport = 0;                   /*是否支持指定格式标志 */
    struct v4l2_fmtdesc fmtdesc;                  /*查询格式需要临时变量*/

    /*初始化 v4l2_format 结构变量必要信 */
    memset(&fmtdesc, 0, sizeof(fmtdesc));       /*清空结构*/
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  /*摄像头恒定是 V4L2_BUF_TYPE_VIDEO_CAPTURE */

    /* 循环枚举摄像头支持的格式              */
    while ((xioctl(fd_vd, VIDIOC_ENUM_FMT, &fmtdesc)) == 0) {

        /* 输出格式信息 */
        printf("{ pixelformat = '%c%c%c%c', description = '%s' }\n",
               fmtdesc.pixelformat & 0xFF,
               (fmtdesc.pixelformat >> 8) & 0xFF,
               (fmtdesc.pixelformat >> 16) & 0xFF,
               (fmtdesc.pixelformat >> 24) & 0xFF,
               fmtdesc.description);


        /*查询当前格式下所有支持的分辨率 */
        video_device_check_frmsize(format_id);


        /*查询下一个格式*/
        fmtdesc.index++;

        /* 判断当前格式是否是指定的格式， */
        if(fmtdesc.pixelformat == format_id) {
            /* 设置格式支持标志  */
            format_is_surport = 1;
        }

    }

    /* 支持目标格式返回0，不支持返回-1 */
    return format_is_surport ? 0 : -1;
}




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
int video_device_set_fmt(struct v4l2_format *fmt)
{
    int ret;

    /*参数合法性检查*/
    if(fmt == NULL) {
        fprintf(stderr, "%s Invalid argument\n", __FUNCTION__);
        return -1;
    }

    /*开始设置摄像头数据格式*/
    ret = xioctl(fd_vd, VIDIOC_S_FMT, fmt);
    if (ret < 0) {
        fprintf(stderr, "%s does  set format! error\n", dev_name);
        return -1;
    }

    /* 输出设置的图像格式信息,设置的高度，宽度可能会和前面设置的不相同
     * 驱动会根据支持分辨率情况，修正用户不合法的高度，宽度数值，
     * 以下输出设置后，最后的分辨率情况
     */
    printf("=====after set fmt\n");
    printf("	fmt.fmt.pix.width = %d\n", fmt->fmt.pix.width);
    printf("	fmt.fmt.pix.height = %d\n", fmt->fmt.pix.height);
    printf("	fmt.fmt.pix.sizeimage = %d\n", fmt->fmt.pix.sizeimage);
    printf("	fmt.fmt.pix.bytesperline = %d\n", fmt->fmt.pix.bytesperline);


    //d) 设置帧率
    struct v4l2_streamparm  Stream_Parm;
    memset(&Stream_Parm, 0, sizeof(struct v4l2_streamparm));
    Stream_Parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    //每秒30帧
    Stream_Parm.parm.capture.timeperframe.denominator     = 25;  //分子
        Stream_Parm.parm.capture.timeperframe.numerator   = 1;   //分母
    ret = xioctl(fd_vd, VIDIOC_S_PARM, &Stream_Parm);
    if (ret < 0) {
        fprintf(stderr, "%s  VIDIOC_S_PARM! error\n", dev_name);
        return -1;
    }

    //e) 获取帧率，查看设置是否生效
    struct v4l2_streamparm param;
    memset(&param, 0, sizeof(struct v4l2_streamparm));
    param.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = xioctl(fd_vd, VIDIOC_G_PARM, &param);
    if (ret < 0) {
        fprintf(stderr, "%s  VIDIOC_G_PARM! error\n", dev_name);
        return -1;
    }
    printf("fps:%d\r\n", param.parm.capture.timeperframe.denominator / param.parm.capture.timeperframe.numerator);
    
    return 0;
}


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
int video_reqbufs(unsigned char nr)
{
    struct v4l2_requestbuffers req;
    CLEAR (req);
    req.count  = nr;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (-1 == xioctl(fd_vd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support memory mapping\n", dev_name);
        }
        return -1;
    }

    if (req.count < 2) {
        fprintf(stderr, "Insufficient buffer memory on %s\n", dev_name);
        return -1;
    }

    return req.count;
}



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
int  video_qbuf_req(int n_buffers)
{
    int i, ret;
    struct v4l2_buffer buf;
    CLEAR (buf);

    /*把申请到的视频缓冲区全部加入到数据采集缓冲队列中*/
    for (i = 0; i < n_buffers; ++i) {
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = i;
        ret = xioctl(fd_vd, VIDIOC_QBUF, &buf);
        if ( ret < 0) {
            fprintf(stderr, "%s error %d, %s\n", "VIDIOC_QBUF", errno, strerror(errno));
            return -1;
        }
    }

    return 0;
}



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
int  video_buf_mmap(unsigned char nr)
{
    int i  = 0;

    /* 分配存储映射结果的结构空间 */
    buffers = calloc(nr, sizeof(*buffers));
    if (!buffers) {
        fprintf(stderr, "%s error %d, %s\n", "calloc", errno, strerror(errno));
        return -1;
    }

    /* 映射所有的缓存 */
    for (i = 0; i < nr; ++i) {
        struct v4l2_buffer buf;
        CLEAR (buf);
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = i;

        //获取到对应index的缓存信息，此处主要利用length信息及offset信息来完成后面的mmap操作。
        if (-1 == xioctl(fd_vd, VIDIOC_QUERYBUF, &buf)) {
            fprintf(stderr, "%s error %d, %s\n", "VIDIOC_QUERYBUF", errno, strerror(errno));
            return -1;
        }

        buffers[i].length = buf.length;

        // 转换成相对地址
        buffers[i].start = mmap(NULL, buf.length,
                                PROT_READ | PROT_WRITE,
                                MAP_SHARED, fd_vd, buf.m.offset);
        if (MAP_FAILED == buffers[i].start) {
            fprintf(stderr, "%s error %d, %s\n", "mmap", errno, strerror(errno));
            return -1;
        }
    }

    return 0;
}



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
int video_poll_data(void)
{
    int r;
    fd_set  fds;
    struct timeval tv;

    FD_ZERO(&fds);
    FD_SET(fd_vd, &fds);

    /* Timeout. */
    tv.tv_sec = 0;
    tv.tv_usec = 50000;
    r = select(fd_vd + 1, &fds, NULL, NULL, &tv);
    if (-1 == r) {
        if (EINTR == errno) {
            fprintf(stderr, "select EINTR\n");
        } else {
            fprintf(stderr, "select error\n");
        }
    }

    else if (0 == r) {
        // fprintf(stderr, "select timeout\n");
    }
    return r;
}



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
int video_read_frame(unsigned char *vbuffer)
{
    int ret = 0;;
    struct v4l2_buffer buf;

    /* 参数合法性检测 */
    if(!vbuffer) {
        printf("line:%d, Invalid argument\n", __LINE__);
        return -1;
    }

    CLEAR (buf);
    buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    /*
     * 取出FIFO缓存中已经采样的帧缓存,根据返回的buf.index
     * 找到对应的mmap映射好的缓存，取出视频数据。
     */
    ret = xioctl(fd_vd, VIDIOC_DQBUF, &buf);
    if ( ret < 0) {
        fprintf(stderr, "++%s error %d, %s\n", "VIDIOC_DQBUF", errno, strerror(errno));
        return -1;
    }

    /* 把图像数据先复制出去处理 */
    memcpy(vbuffer, buffers[buf.index].start , buffers[buf.index].length);


    /*将刚刚处理完的缓冲重新入队列尾，这样可以循环采集*/
    ret = xioctl(fd_vd, VIDIOC_QBUF, &buf);
    if ( ret < 0) {
        fprintf(stderr, "%s error %d, %s\n", "VIDIOC_QBUF", errno, strerror(errno));
        return -1;
    }

    return buf.index;
}



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
int video_start_capturing(void)
{
    int ret;

    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = xioctl(fd_vd, VIDIOC_STREAMON, &type);
    if (ret < 0) {
        fprintf(stderr, "%s error %d, %s\n", "VIDIOC_STREAMON", errno, strerror(errno));
        return -1;
    }
    return 0;
}


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
int video_stop_capturing(void)
{
    int ret;
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = xioctl(fd_vd, VIDIOC_STREAMOFF, &type);
    if (ret < 0) {
        fprintf(stderr, "%s error %d, %s\n", "VIDIOC_STREAMOFF", errno, strerror(errno));
        return -1;
    }
    return 0;
}


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
int  video_device_init(const char *video_path)
{

    int ret ;
    struct v4l2_capability cap;

    /*视频设备名称初始化*/
    if(video_path == NULL) {
        dev_name = VIDEO_DEVICE;
    } else {
        dev_name =  video_path;
    }

    /*打开视频设备*/
    ret = video_device_open(dev_name);
    if(ret < 0) {
        fprintf(stderr, "%s video_device_open error\n", dev_name);
        return -1;
    }

    /*查询设备的功能，*/
    ret = video_device_querycap(&cap);
    if(ret < 0) {
        fprintf(stderr, "%s video_device_querycap error\n", dev_name);
        return -1;
    }

    /*判断是否有捕获功能*/
    ret = video_device_have_cap(&cap, V4L2_CAP_VIDEO_CAPTURE);
    if(ret < 0) {
        fprintf(stderr, "%s is no video capture device\n", dev_name);
        return -1;
    }

    /*判断是否有启动设备功能*/
    ret = video_device_have_cap(&cap, V4L2_CAP_STREAMING);
    if(ret < 0) {
        fprintf(stderr, "%s does not support streaming i/o\n", dev_name);
        return -1;
    }

    /* 获取视频设备支持的图像格式 */
    ret = video_device_check_fmt(V4L2_PIX_FMT_YUYV);
    if(ret < 0) {
        fprintf(stderr, "%s does not support this format!\n", dev_name);
        return -1;
    }

    /* 设置摄像头采集的视频格式  */
    CLEAR(fmt);             /* 清0结构 */
    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = VID_IMG_W;
    fmt.fmt.pix.height      = VID_IMG_H;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    ret = video_device_set_fmt(&fmt);
    if(ret < 0) {
        fprintf(stderr, "%s video_device_set_fmt error!\n", dev_name);
        return -1;
    }

    /* 申请视频采集缓冲区 */
    nr_nr = video_reqbufs(nr_nr);
    if(nr_nr < 0) {
        fprintf(stderr, "%s video_reqbufs error!\n", dev_name);
        return -1;
    }

    /*查询并且映射缓冲区*/
    ret = video_buf_mmap(nr_nr);
    if(ret < 0) {
        fprintf(stderr, "%s video_buf_mmap error!\n", dev_name);
        return -1;
    }

    /* 把缓冲区放入采集队列 */
    ret = video_qbuf_req(nr_nr);
    if(ret < 0) {
        fprintf(stderr, "%s video_qbuf_req error!\n", dev_name);
        return -1;
    }

    /*启动视频采集数据*/
    ret = video_start_capturing();
    if(ret < 0) {
        fprintf(stderr, "%s video_qbuf_req error!\n", dev_name);
        return -1;
    }

    return 0;
}




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
void video_device_uninit(int nr)
{
    unsigned int i;

    /*停止视频设备*/
    video_stop_capturing();

    /*把所有申请到的视频缓冲区,取消映射*/
    for (i = 0; i < nr; ++i) {
        if (-1 == munmap(buffers[i].start, buffers[i].length)) {
            errno_exit("munmap");
        }
    }

    /*释放视频缓冲区内存*/
    free(buffers);

    /*关闭视频设备*/
    video_device_close();
}



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
int video_mainloop(int *fd)
{
    int ret = 0;
    int index = 0;                              //当前帧编号
    int  frame_count = 0;                       //帧计数

    /*H264初始化 */
    h264_init_encoder(VID_IMG_W, VID_IMG_H);    
    
	/* 打开编码文件 */
    //选择保存的文件路径
    h264_file_open(NULL,*fd);             

#if HVAE_YUYV      //生成yuv文件		
	yuyv_fp = fopen(yuyv_file_name, "wa+");
#endif

    while (1) {

#if (MOD_NOBLOCK_OPEN)  //非阻塞方式打开时候需要先查询是否有数据可读
        ret = video_poll_data();
        if( ret <= 0) {
            continue;
        }
#endif
        //取出一帧数据，原始数据存放在yuv_vbuffer，返回缓冲区的索引
        index = ret = video_read_frame(yuv_vbuffer);
        if( ret < 0) {
            continue;
        }
#if SHOW_LCD
        /* 把数据转换为RGB并存放到LCD显示缓冲区中-*/
        ret = yuv422_to_rgb32(yuv_vbuffer, vbuffer, VID_IMG_W, VID_IMG_H);
        if ( ret < 0) {
            fprintf(stderr, "%s error %d, %s\n", "yuv422_to_rgb32", errno, strerror(errno));
            return ret;
        }

        //LCD屏上显示图片
        ret = lcd_show_rgb_image((vinfo.xres - fmt.fmt.pix.width) / 2, 
                                 (vinfo.yres - fmt.fmt.pix.height) / 2, 
                                  VID_IMG_W, VID_IMG_H, vbuffer);
        if ( ret < 0) {
            fprintf(stderr, "%s error %d, %s\n", "lcd_show_rgb_image", errno, strerror(errno));
            return ret;
        }
#endif 
        if(frame_count++ < FRANE_COUNT) {
           
            putc('.', stderr); /* 模拟输出编码进度 */
            
            /*把yuyv 数据压缩为H264格式编码到文件中 */
            h264_encode_frame(yuv_vbuffer, buffers[index].length);

#if HVAE_YUYV  //生成yuv文件		
			ret = fwrite(yuv_vbuffer,buffers[index].length, 1, yuyv_fp) ;
			if(ret > 0) {
			  //printf("Flush 1 frame.\n");//
			} else {
			   perror(" fwrite yuyv err\n");
			}
#endif
        } else {
            static int first = 0;
            if(first == 0) {
                printf("\r\n");
                first = 1;
                /*关闭文件，释放资源 */
                h264_close_encoder();
                h264_file_close();

#if HVAE_YUYV   //生成yuv文件		    
			    fclose(yuyv_fp);
#endif
            }
        }

    }

    return 0;
}





