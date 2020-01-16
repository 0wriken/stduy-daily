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

#define SHOW_LCD     1    //�Ƿ���ʾͼ����LCD����
#define  HVAE_YUYV   0  //�Ƿ�����yuyv�ļ�  ��1 ���ɣ� 0������;
#if HVAE_YUYV                //����yuv�ļ�		
	const char *yuyv_file_name = "./yuyu422.yuyv";	 //����  yuyv �ļ���
	FILE *yuyv_fp;
#endif

const char *h264_file_name = "./yuyu422toh264.h264";   //����h264�ļ���
#define FRANE_COUNT   500                              //����֡����

#define MOD_NOBLOCK_OPEN   0    //�򿪷�ʽ������������Ϊ1����������Ϊ0


/*�����豸����ָ��*/
static  const char * dev_name = NULL;

/*�����ļ������������������/dec/video0 �ļ��򿪾��*/
static  int fd_vd = -1;

/*������Ƶ������ָ��*/
static  struct buffer * buffers = NULL;

/*���뻺��������*/
static  unsigned int nr_nr = 4;

/*֡�ĸ�ʽ�������ȣ��߶ȵ�*/
static  struct v4l2_format fmt;

/* ������Ƶ���ݻ����� */
unsigned char vbuffer[800 * 480 * 4] = {0};
unsigned char yuv_vbuffer[800 * 480 * 4] = {0};


/*������Ϣ��ʾ*/
static  void  errno_exit(const char * s)
{
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}


/*��Ƶ�豸���ƺ���*/
static  int xioctl(int fd, int request, void * arg)
{
    int r;
    do {
        r = ioctl(fd, request, arg);
    } while (-1 == r && EINTR == errno);
    return r;
}


/********************************************************************
*  Function��     lcd_draw_image_rgb888()
*  Description:   ��rgb888ͼƬ������ʾ��LCD����;
*  Calls:         ;
*  Called By:     ��
*  Input��         x , y :ת����RGB����LCD��ʾ����ʼ����
*                 w,image_height��ͼ�����
*                 rgb_data:rgb����ָ�룻
*  Output��        none;
*  Return :       0:ת���ɹ�   -1: ת��ʧ�ܡ�
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

    /* �����Ϸ��Լ�� */
    if(!rgb_data ) {
        printf("ERROR!file:%s; line:%d\r\n", __FILE__, __LINE__);
        return -1;
    }

    /* ȡ��ת��rgb���Դ���ݣ���Ϊoutput_ptr���ⲿ�����ָ�룬���Դ˴���ֱ��ʹ�á�*/
    temp_src = rgb_data;

    /* ���� x,y�������ͼƬӦ����lcd������ʾ��ʼλ�� */
    temp_des = fbp + vinfo.xres * vinfo.bits_per_pixel / 8 * y + x * vinfo.bits_per_pixel / 8;

    /* ����ͼƬ�ĸߣ������ʾͼƬ��LCD���� */
    for(i = 0; i < h; i++) {
        for(j = 0; j < w; j++) {
            //           RGB888        R                  G               B
            unsigned int color = temp_src[2] << 16 | temp_src[1] << 8 | temp_src[0];
            fb_show_pixel(x + j,  y, color);
            temp_src += 3;       //����ָ������3�ֽڣ�ָ����һ����λ��
        }
        y++;  //��һ��
    }

    return 0;
}



/********************************************************************
*  Function��  lcd_show_rgb_image()
*  Description:   LCD��ʾrgb888ͼƬ���ݺ���;
*  Calls:         ;
*  Called By:     ��
*  Input��         x , y:lcd��ʾ����ʼ����
*                 w , w:ͼƬ�Ŀ�ȣ��߶�
*                 rgb_data:rgb���ݻ����׵�ַ
*  Output��        none;
*  Return :       0���ɹ���       -1��ʧ��;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int lcd_show_rgb_image(unsigned x, unsigned y,
                       int w, int h,
                       unsigned char *rgb_data)
{
    /* �����Ϸ��Լ�� */
    if(!rgb_data  || x > vinfo.xres  || y > vinfo.yres ) {
        return -1;
    }

    if(x + w > vinfo.xres ) {
        w = vinfo.xres - x;
    }

    if(y + h > vinfo.yres ) {
        w = vinfo.yres - y;
    }

    /* ��ʾͼ����LCD���� */
    lcd_draw_image_rgb888(x, y, w, h, rgb_data);

    return 0;
}




/********************************************************************
*  Function��      video_device_open
*  Description:   ������ͷ�豸;
*  Calls:         ;
*  Called By:     ��
*  Input��      dev:����ͷ�豸��
*  Output��     none;
*  Return :       -1:ʧ�ܣ� >0 : ����ͷ�ļ�������
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
*  Function��      video_device_close
*  Description:   �ر��豸;
*  Calls:         ;
*  Called By:     ��
*  Input��         none
*  Output��        none;
*  Return :       0:�ɹ�;    -1:ʧ��;
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
*  Function��      video_device_querycap
*  Description:   ��ѯ���豸����;
*  Calls:         ;
*  Called By:     ��
*  Input��        none;
*  Output��        cap:�����ѯ�ṹ��v4l2_capability�ṹ�������ַ;
*  Return :       -1:ʧ�ܣ� 0: �ɹ�
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
*  Function��      video_device_have_cap
*  Description:   �ж��豸�Ƿ�߱�ָ���Ĺ���;
*  Calls:         ;
*  Called By:     ��
*  Input��         none;
*  Output��        cap:�Ѿ���ѯ�н���Ľṹ��v4l2_capability�ṹ�������ַ;
*                 capability��Ҫ��ѯ�Ĺ�������,�� V4L2_CAP_VIDEO_CAPTURE ;
*  Return :       -1:�����Ƿ��� 0: ��֧��ָ������; 1��֧��ָ���Ĺ���;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_have_cap(struct v4l2_capability *cap, unsigned int capability)
{
    int ret ;

    /*�ж��ǲ����Ϸ���*/
    if(cap == NULL) {
        fprintf(stderr, "line:%d, %s() Invalid argument\n", __LINE__, __FUNCTION__);
        return -1;
    }

    /* ����ָ����ֵ */
    ret = !!(cap->capabilities & capability);

    return ret;
}


/********************************************************************
*  Function��      video_device_check_frmsize
*  Description:   ��ȡ����ͷ��֧�ֵķֱ���;
*  Calls:         ;
*  Called By:     ��
*  Input��         format_id: Ŀ���ʽid,�� V4L2_PIX_FMT_YUYV
*  Output��        none;
*  Return :       -1:��֧��Ŀ���ʽ�� 0: ֧��Ŀ���ʽ
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
*  Function��      video_device_check_fmt
*  Description:   ��ѯ����ͷ֧�ֵ����и�ʽ���Լ��ж��Ƿ�֧��ָ����ʽ;
*  Calls:         ;
*  Called By:     ��
*  Input��         format_id: Ҫȷ��֧���Ƿ�֧�ֵ�Ŀ���ʽid,�� V4L2_PIX_FMT_YUYV
*  Output��        none;
*  Return :       -1:��֧��Ŀ���ʽ�� 0: ֧��Ŀ���ʽ
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_check_fmt(unsigned int  format_id)
{
    int  format_is_surport = 0;                   /*�Ƿ�֧��ָ����ʽ��־ */
    struct v4l2_fmtdesc fmtdesc;                  /*��ѯ��ʽ��Ҫ��ʱ����*/

    /*��ʼ�� v4l2_format �ṹ������Ҫ�� */
    memset(&fmtdesc, 0, sizeof(fmtdesc));       /*��սṹ*/
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  /*����ͷ�㶨�� V4L2_BUF_TYPE_VIDEO_CAPTURE */

    /* ѭ��ö������ͷ֧�ֵĸ�ʽ              */
    while ((xioctl(fd_vd, VIDIOC_ENUM_FMT, &fmtdesc)) == 0) {

        /* �����ʽ��Ϣ */
        printf("{ pixelformat = '%c%c%c%c', description = '%s' }\n",
               fmtdesc.pixelformat & 0xFF,
               (fmtdesc.pixelformat >> 8) & 0xFF,
               (fmtdesc.pixelformat >> 16) & 0xFF,
               (fmtdesc.pixelformat >> 24) & 0xFF,
               fmtdesc.description);


        /*��ѯ��ǰ��ʽ������֧�ֵķֱ��� */
        video_device_check_frmsize(format_id);


        /*��ѯ��һ����ʽ*/
        fmtdesc.index++;

        /* �жϵ�ǰ��ʽ�Ƿ���ָ���ĸ�ʽ�� */
        if(fmtdesc.pixelformat == format_id) {
            /* ���ø�ʽ֧�ֱ�־  */
            format_is_surport = 1;
        }

    }

    /* ֧��Ŀ���ʽ����0����֧�ַ���-1 */
    return format_is_surport ? 0 : -1;
}




/********************************************************************
*  Function��      video_device_set_fmt
*  Description:   ��������ͷ���ݸ�ʽ;
*  Calls:         ;
*  Called By:     ��
*  Input��         fmt: �Ѿ����õ�����ͷ��ʽ�ṹָ��
*  Output��        none;
*  Return :       -1:����ʧ�ܣ� 0: ���óɹ�
*  Author:        chenzhifa;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_device_set_fmt(struct v4l2_format *fmt)
{
    int ret;

    /*�����Ϸ��Լ��*/
    if(fmt == NULL) {
        fprintf(stderr, "%s Invalid argument\n", __FUNCTION__);
        return -1;
    }

    /*��ʼ��������ͷ���ݸ�ʽ*/
    ret = xioctl(fd_vd, VIDIOC_S_FMT, fmt);
    if (ret < 0) {
        fprintf(stderr, "%s does  set format! error\n", dev_name);
        return -1;
    }

    /* ������õ�ͼ���ʽ��Ϣ,���õĸ߶ȣ���ȿ��ܻ��ǰ�����õĲ���ͬ
     * ���������֧�ֱַ�������������û����Ϸ��ĸ߶ȣ������ֵ��
     * ����������ú����ķֱ������
     */
    printf("=====after set fmt\n");
    printf("	fmt.fmt.pix.width = %d\n", fmt->fmt.pix.width);
    printf("	fmt.fmt.pix.height = %d\n", fmt->fmt.pix.height);
    printf("	fmt.fmt.pix.sizeimage = %d\n", fmt->fmt.pix.sizeimage);
    printf("	fmt.fmt.pix.bytesperline = %d\n", fmt->fmt.pix.bytesperline);


    //d) ����֡��
    struct v4l2_streamparm  Stream_Parm;
    memset(&Stream_Parm, 0, sizeof(struct v4l2_streamparm));
    Stream_Parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    //ÿ��30֡
    Stream_Parm.parm.capture.timeperframe.denominator     = 25;  //����
        Stream_Parm.parm.capture.timeperframe.numerator   = 1;   //��ĸ
    ret = xioctl(fd_vd, VIDIOC_S_PARM, &Stream_Parm);
    if (ret < 0) {
        fprintf(stderr, "%s  VIDIOC_S_PARM! error\n", dev_name);
        return -1;
    }

    //e) ��ȡ֡�ʣ��鿴�����Ƿ���Ч
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
*  Function��     video_reqbufs()
*  Description:   ������Ƶ�ɼ�������;
*  Calls:         ;
*  Called By:     ��
*  Input��         nr:����������;
*  Output��        none;
*  Return :       >0: �ɹ�,���뵽�Ļ�����;  -1:ʧ�ܣ�
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
*  Function��     v4l2_qbuf_req
*  Description:   �ѻ���������ɼ�����
*  Calls:         ;
*  Called By:     ��
*  Input��         n_buffers:����������
*  Output��       none;
*  Return :      0:�ɹ���-1:ʧ��;
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

    /*�����뵽����Ƶ������ȫ�����뵽���ݲɼ����������*/
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
*  Function��     video_buf_mmap()
*  Description:   ӳ��������Ƶ�ɼ�������;
*  Calls:         ;
*  Called By:     ��
*  Input��          nr:����������;
*  Output��        none;
*  Return :       0:�ɹ�; -1��ʧ��;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int  video_buf_mmap(unsigned char nr)
{
    int i  = 0;

    /* ����洢ӳ�����Ľṹ�ռ� */
    buffers = calloc(nr, sizeof(*buffers));
    if (!buffers) {
        fprintf(stderr, "%s error %d, %s\n", "calloc", errno, strerror(errno));
        return -1;
    }

    /* ӳ�����еĻ��� */
    for (i = 0; i < nr; ++i) {
        struct v4l2_buffer buf;
        CLEAR (buf);
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = i;

        //��ȡ����Ӧindex�Ļ�����Ϣ���˴���Ҫ����length��Ϣ��offset��Ϣ����ɺ����mmap������
        if (-1 == xioctl(fd_vd, VIDIOC_QUERYBUF, &buf)) {
            fprintf(stderr, "%s error %d, %s\n", "VIDIOC_QUERYBUF", errno, strerror(errno));
            return -1;
        }

        buffers[i].length = buf.length;

        // ת������Ե�ַ
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
*  Function��     video_poll_data()
*  Description:   ��ѯ�Ƿ������ݾ���;
*  Calls:         ;
*  Called By:     ��
*  Input��        none
*  Output��       none;
*  Return :       >0: �����ݣ�
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
*  Function��     video_read_frame()
*  Description:   ��ȡһ֡����,������ͷԭʼ����ȡ�������vbuffer��;
*  Calls:         ;
*  Called By:     ��
*  Input��        none
*  Output��       vbuffer : ���ݴ������ͷԭʼ���ݵĻ�����;
*  Return :       �ɹ�:>=0.������������;ʧ��:-1
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_read_frame(unsigned char *vbuffer)
{
    int ret = 0;;
    struct v4l2_buffer buf;

    /* �����Ϸ��Լ�� */
    if(!vbuffer) {
        printf("line:%d, Invalid argument\n", __LINE__);
        return -1;
    }

    CLEAR (buf);
    buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    /*
     * ȡ��FIFO�������Ѿ�������֡����,���ݷ��ص�buf.index
     * �ҵ���Ӧ��mmapӳ��õĻ��棬ȡ����Ƶ���ݡ�
     */
    ret = xioctl(fd_vd, VIDIOC_DQBUF, &buf);
    if ( ret < 0) {
        fprintf(stderr, "++%s error %d, %s\n", "VIDIOC_DQBUF", errno, strerror(errno));
        return -1;
    }

    /* ��ͼ�������ȸ��Ƴ�ȥ���� */
    memcpy(vbuffer, buffers[buf.index].start , buffers[buf.index].length);


    /*���ոմ�����Ļ������������β����������ѭ���ɼ�*/
    ret = xioctl(fd_vd, VIDIOC_QBUF, &buf);
    if ( ret < 0) {
        fprintf(stderr, "%s error %d, %s\n", "VIDIOC_QBUF", errno, strerror(errno));
        return -1;
    }

    return buf.index;
}



/********************************************************************
*  Function��     video_start_capturing
*  Description:   ������Ƶ�ɼ�
*  Calls:         ;
*  Called By:     ��
*  Input��        none
*  Output��       none;
*  Return :       0: �ɹ���-1��ʧ��;
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
*  Function��     video_stop_capturing()
*  Description:   ֹͣ��Ƶ�ɼ�;
*  Calls:         ;
*  Called By:     ��
*  Input��         none
*  Output��        none;
*  Return :       0:�ɹ�; 1:ʧ��;
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
*  Function��      video_device_init()
*  Description:   ����ͷ��ʼ������ʼ����ɺ�Ϳ��Կ�ʼ��ȡ������;
*  Calls:         ;
*  Called By:     ��
*  Input��      video_path: ����ͷ�豸·��
*  Output��    none;
*  Return :       -1:ʧ�ܣ� 0: �ɹ�
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int  video_device_init(const char *video_path)
{

    int ret ;
    struct v4l2_capability cap;

    /*��Ƶ�豸���Ƴ�ʼ��*/
    if(video_path == NULL) {
        dev_name = VIDEO_DEVICE;
    } else {
        dev_name =  video_path;
    }

    /*����Ƶ�豸*/
    ret = video_device_open(dev_name);
    if(ret < 0) {
        fprintf(stderr, "%s video_device_open error\n", dev_name);
        return -1;
    }

    /*��ѯ�豸�Ĺ��ܣ�*/
    ret = video_device_querycap(&cap);
    if(ret < 0) {
        fprintf(stderr, "%s video_device_querycap error\n", dev_name);
        return -1;
    }

    /*�ж��Ƿ��в�����*/
    ret = video_device_have_cap(&cap, V4L2_CAP_VIDEO_CAPTURE);
    if(ret < 0) {
        fprintf(stderr, "%s is no video capture device\n", dev_name);
        return -1;
    }

    /*�ж��Ƿ��������豸����*/
    ret = video_device_have_cap(&cap, V4L2_CAP_STREAMING);
    if(ret < 0) {
        fprintf(stderr, "%s does not support streaming i/o\n", dev_name);
        return -1;
    }

    /* ��ȡ��Ƶ�豸֧�ֵ�ͼ���ʽ */
    ret = video_device_check_fmt(V4L2_PIX_FMT_YUYV);
    if(ret < 0) {
        fprintf(stderr, "%s does not support this format!\n", dev_name);
        return -1;
    }

    /* ��������ͷ�ɼ�����Ƶ��ʽ  */
    CLEAR(fmt);             /* ��0�ṹ */
    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = VID_IMG_W;
    fmt.fmt.pix.height      = VID_IMG_H;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    ret = video_device_set_fmt(&fmt);
    if(ret < 0) {
        fprintf(stderr, "%s video_device_set_fmt error!\n", dev_name);
        return -1;
    }

    /* ������Ƶ�ɼ������� */
    nr_nr = video_reqbufs(nr_nr);
    if(nr_nr < 0) {
        fprintf(stderr, "%s video_reqbufs error!\n", dev_name);
        return -1;
    }

    /*��ѯ����ӳ�仺����*/
    ret = video_buf_mmap(nr_nr);
    if(ret < 0) {
        fprintf(stderr, "%s video_buf_mmap error!\n", dev_name);
        return -1;
    }

    /* �ѻ���������ɼ����� */
    ret = video_qbuf_req(nr_nr);
    if(ret < 0) {
        fprintf(stderr, "%s video_qbuf_req error!\n", dev_name);
        return -1;
    }

    /*������Ƶ�ɼ�����*/
    ret = video_start_capturing();
    if(ret < 0) {
        fprintf(stderr, "%s video_qbuf_req error!\n", dev_name);
        return -1;
    }

    return 0;
}




/********************************************************************
*  Function��     video_device_uninit()
*  Description:   �ͷ���Ƶ�ɼ�������ӳ�䣬�ͷ�ռ����Դ;
*  Calls:         ;
*  Called By:     ��
*  Input��        dev:lcd�豸��
*  Output��       none;
*  Return :       none
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
void video_device_uninit(int nr)
{
    unsigned int i;

    /*ֹͣ��Ƶ�豸*/
    video_stop_capturing();

    /*���������뵽����Ƶ������,ȡ��ӳ��*/
    for (i = 0; i < nr; ++i) {
        if (-1 == munmap(buffers[i].start, buffers[i].length)) {
            errno_exit("munmap");
        }
    }

    /*�ͷ���Ƶ�������ڴ�*/
    free(buffers);

    /*�ر���Ƶ�豸*/
    video_device_close();
}



/********************************************************************
*  Function��     video_mainloop
*  Description:   ѭ���ɼ�����������;
*  Calls:         ;
*  Called By:     ��
*  Input��        none
*  Output��       none;
*  Return :       �ɹ�:0;ʧ��:-1;
*  Author:        chenzhifa;        ;
*  Others:        ;
*  date of completion:   
*  date of last modify:  
*********************************************************************/
int video_mainloop(int *fd)
{
    int ret = 0;
    int index = 0;                              //��ǰ֡���
    int  frame_count = 0;                       //֡����

    /*H264��ʼ�� */
    h264_init_encoder(VID_IMG_W, VID_IMG_H);    
    
	/* �򿪱����ļ� */
    //ѡ�񱣴���ļ�·��
    h264_file_open(NULL,*fd);             

#if HVAE_YUYV      //����yuv�ļ�		
	yuyv_fp = fopen(yuyv_file_name, "wa+");
#endif

    while (1) {

#if (MOD_NOBLOCK_OPEN)  //��������ʽ��ʱ����Ҫ�Ȳ�ѯ�Ƿ������ݿɶ�
        ret = video_poll_data();
        if( ret <= 0) {
            continue;
        }
#endif
        //ȡ��һ֡���ݣ�ԭʼ���ݴ����yuv_vbuffer�����ػ�����������
        index = ret = video_read_frame(yuv_vbuffer);
        if( ret < 0) {
            continue;
        }
#if SHOW_LCD
        /* ������ת��ΪRGB����ŵ�LCD��ʾ��������-*/
        ret = yuv422_to_rgb32(yuv_vbuffer, vbuffer, VID_IMG_W, VID_IMG_H);
        if ( ret < 0) {
            fprintf(stderr, "%s error %d, %s\n", "yuv422_to_rgb32", errno, strerror(errno));
            return ret;
        }

        //LCD������ʾͼƬ
        ret = lcd_show_rgb_image((vinfo.xres - fmt.fmt.pix.width) / 2, 
                                 (vinfo.yres - fmt.fmt.pix.height) / 2, 
                                  VID_IMG_W, VID_IMG_H, vbuffer);
        if ( ret < 0) {
            fprintf(stderr, "%s error %d, %s\n", "lcd_show_rgb_image", errno, strerror(errno));
            return ret;
        }
#endif 
        if(frame_count++ < FRANE_COUNT) {
           
            putc('.', stderr); /* ģ������������ */
            
            /*��yuyv ����ѹ��ΪH264��ʽ���뵽�ļ��� */
            h264_encode_frame(yuv_vbuffer, buffers[index].length);

#if HVAE_YUYV  //����yuv�ļ�		
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
                /*�ر��ļ����ͷ���Դ */
                h264_close_encoder();
                h264_file_close();

#if HVAE_YUYV   //����yuv�ļ�		    
			    fclose(yuyv_fp);
#endif
            }
        }

    }

    return 0;
}





