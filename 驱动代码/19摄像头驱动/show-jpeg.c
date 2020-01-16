#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
#include "lcd.h"


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
 *  date of completion:    
 *  date of last modify:   
 *********************************************************************/
int lcd_show_jpeg( const char *file, int x, int y)
{

	//1.JPEG对象分配空间并初始化
	//1)定义JPEG对象及错误处理对象
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	//2)设置错误处理函数
	cinfo.err = jpeg_std_error(&jerr);
	//2)创建JPEG对象
	jpeg_create_decompress(&cinfo);

	printf("line:%d\n\n", __LINE__);

	//2. 初始化解码对象
	//1）打开jpeg图像
	FILE* infile;
	if ((infile = fopen(file, "rb")) == NULL) {
		fprintf(stderr, "open %s failed\n", file);
		return -1;
	}
	//2）绑定jpeg解码对象到打开的输入文件中
	jpeg_stdio_src(&cinfo, infile);

	//3. 获取JPEG文件信息
	jpeg_read_header(&cinfo, TRUE);  //读取jpeg文件头信息

	//4.设置解码参数
	//1）设置解码颜色空间解码为 RGB888
	cinfo.out_color_space = JCS_RGB;
	//2）设定解压缩参数，将图像长宽缩小为原图的1/2，根据实际情况调整
	cinfo.scale_num   = 1;
	cinfo.scale_denom = 1;

	//5.JPEG图片解码开始
	jpeg_start_decompress(&cinfo);


	//6.读取jpeg解码后的数据并进行处理
	//1）为一条扫描线上的像素点分配存储空间
#if 0
	unsigned char  *buffer;
	buffer = (unsigned char *) malloc(cinfo.output_width * cinfo.output_components);
#else
	JSAMPARRAY buffer;     //定义一个二维指针，指向一个 char 类型的二维数组
	unsigned int row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
#endif
	//2) 以行为单位，循环读取jpeg解码后的数据
	while (cinfo.output_scanline < cinfo.output_height) {

		//(1)读取一行数据到buffer中，执行完成后 buffer 中包含了一解码好的一行数据
		jpeg_read_scanlines(&cinfo, buffer, 1);

		//(2) 处理存储到jpeg数据缓冲区的数据
#if 0
		int i;
		//下面开始处理一行数据，如何处理，则用户自行决定，本例子直接输出在终端上。
		for (i = 0; i < cinfo.output_width; i++) {
			//输出在终端中，测试使用
			printf("%02X%02X%02X ", buffer[i * 3], buffer[i * 3 + 1], buffer[i * 3 + 2]);
			if (0 == ((i + 1) % 10) || i == cinfo.output_width - 1) {
				printf("\n");
			}
		}
		printf("least:%d\n\n", cinfo.output_height - cinfo.output_scanline);
#endif

		//显示一行数据LCD屏上
		int j = 0;
		unsigned char *temp_src = buffer[0];
		for(j = 0; j < cinfo.output_width; j++) {
			//           RGB888        R                  G               B
			unsigned int color = temp_src[0] << 16 | temp_src[1] << 8 | temp_src[2];
			fb_show_pixel(x + j,  y, color);
			temp_src += 3;       //数据指针增加3字节，指向下一个点位置
		}
		y++;                     //下一行，坐标自增加
		//printf("cinfo.output_scanline:%d\r\n",cinfo.output_scanline);
	}

	printf("-----decode end-----\r\n");

	//7. 解码结束后，需要调用jpeg_finish_decompress 函数，
	jpeg_finish_decompress(&cinfo);

	//8. 释放解码对象，关闭文件
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

	return 0;
}


