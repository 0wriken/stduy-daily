
#ifndef   __WRITE_JPEG_H__
#define   __WRITE_JPEG_H__

/********************************************************************
 *  Function��      rgb888_write_jpeg()
 *  Description:   rgb888����ת���浽jpegͼ���ļ�;
 *  Calls:         ;
 *  Called By:
 *  Input��         filename:jpegͼƬ���ַ���; lpbuf:rgb����ָ��
 *                 width,height :����ͷ�ɼ�������ͼƬ���ݿ�Ⱥ͸߶�
 *  Output��        head:�������ļ��������������ͷ
 *  Return :       0:д��ɹ�            ;  -1:ʧ��
 *  Author:        ;
 *  Others:        ;
 *  date of completion:   2013-10-11
 *  date of last modify:  2013-10-11
 *********************************************************************/
int rgb888_write_jpeg(const char*filename, unsigned char *lpbuf, int width, int height);


/********************************************************************
 *  Function��      yuv422_write_raw()
 *  Description:   ��yuv422���ݱ���ɵ���ԭʼ����ͼ���ļ�;
 *  Calls:         ;
 *  Called By:
 *  Input��         filename:yuvͼƬ���ַ���; yuvdata:yuv����ָ��
 *                 width,height :����ͷ�ɼ�������ͼƬ���ݿ�Ⱥ͸߶�
 *  Output��        none; 
 *  Return :       0:д��ɹ�            ;  -1:ʧ��
 *  Author:        ;
 *  Others:        ;
 *  date of completion:   2013-10-11
 *  date of last modify:  2013-10-11
 *********************************************************************/
int yuv422_write_raw(const char*filename,unsigned char *yuvdata,  size_t data_len);


#endif



