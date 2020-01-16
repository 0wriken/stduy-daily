
#ifndef   __WRITE_JPEG_H__
#define   __WRITE_JPEG_H__

/********************************************************************
 *  Function：      rgb888_write_jpeg()
 *  Description:   rgb888数据转保存到jpeg图像文件;
 *  Calls:         ;
 *  Called By:
 *  Input：         filename:jpeg图片名字符串; lpbuf:rgb数据指针
 *                 width,height :摄像头采集回来的图片数据宽度和高度
 *  Output：        head:存放输出文件名输出内容链表头
 *  Return :       0:写入成功            ;  -1:失败
 *  Author:        ;
 *  Others:        ;
 *  date of completion:   2013-10-11
 *  date of last modify:  2013-10-11
 *********************************************************************/
int rgb888_write_jpeg(const char*filename, unsigned char *lpbuf, int width, int height);


/********************************************************************
 *  Function：      yuv422_write_raw()
 *  Description:   把yuv422数据保存成单个原始数据图像文件;
 *  Calls:         ;
 *  Called By:
 *  Input：         filename:yuv图片名字符串; yuvdata:yuv数据指针
 *                 width,height :摄像头采集回来的图片数据宽度和高度
 *  Output：        none; 
 *  Return :       0:写入成功            ;  -1:失败
 *  Author:        ;
 *  Others:        ;
 *  date of completion:   2013-10-11
 *  date of last modify:  2013-10-11
 *********************************************************************/
int yuv422_write_raw(const char*filename,unsigned char *yuvdata,  size_t data_len);


#endif



