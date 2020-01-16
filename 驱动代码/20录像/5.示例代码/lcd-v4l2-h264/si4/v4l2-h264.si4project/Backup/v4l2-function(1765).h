#ifndef __V4L2_FUNCTION_H__
#define __V4L2_FUNCTION_H__

#include <linux/videodev2.h>


/* ��0������ */
#define CLEAR(x) memset (&(x), 0, sizeof (x))

/* ��������ͷ�豸�ļ�������ʵ������޸� */
#define VIDEO_DEVICE     "/dev/video1"

/* ����ͼ���,�߶�        */
#define VID_IMG_W      320  //640     
#define VID_IMG_H      240  //480 


/*�Զ�����Ƶ���������ݽṹ*/
struct buffer {
    void * start;
    size_t length;//buffer's length is different from cap_image_size
};


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
                           unsigned char *rgb_data);


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
                       unsigned char *rgb_data);




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
int video_mainloop(void);


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
int  video_device_open(const char*dev);


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
int video_device_close(void);



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
int video_device_querycap(struct v4l2_capability *cap);


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
int video_device_have_cap(struct v4l2_capability *cap, unsigned int capability);


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
int video_device_check_fmt(unsigned int  format_id);


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
int video_device_set_fmt(struct v4l2_format *fmt);


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
int video_reqbufs(unsigned char nr);



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
int  video_qbuf_req(int n_buffers);



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
int  video_buf_mmap(unsigned char nr);



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
int video_poll_data(void);



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
int video_read_frame(unsigned char *vbuffer);


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
int video_start_capturing(void);


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
int video_stop_capturing(void);


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
int  video_device_init(const char *video_path);


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
void video_device_uninit(int nr);

#endif


