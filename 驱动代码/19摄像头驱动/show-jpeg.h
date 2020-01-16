
#ifndef   _SHOW_JPEG_H__
#define   _SHOW_JPEG_H__


/********************************************************************
*  Function：      lcd_show_jpeg()
*  Description:   把jpeg图片解码成rgb888图片数据显示在LCD屏上;
*  Calls:         ;
*  Called By:     ；
*  Input：         file ：jpeg图片路径; x,y：lcd屏上显示起始坐标
*  Output：        none;
*  Return :       0:成功 ;    -1: 显示失败。
*  Author:        chenzhifa;        ;
*  Others:        none;
*  date of completion:   2012-12-20
*  date of last modify:  2012-12-20
*********************************************************************/
int lcd_show_jpeg( const char *file, int x, int y);


#endif



