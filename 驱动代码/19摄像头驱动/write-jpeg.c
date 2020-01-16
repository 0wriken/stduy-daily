#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
#include <stdlib.h>



/********************************************************************
 *  Function：      rgb888_write_jpeg()
 *  Description:   rgb888数据转保存到jpeg图像文件;
 *  Calls:         ;
 *  Called By:
 *  Input：         filename:jpeg图片名字符串; lpbuf:rgb数据指针
 *                 width,height :摄像头采集回来的图片数据宽度和高度
 *  Output：        
 *  Return :       0:写入成功  ;      -1:失败;
 *  Author:        ;
 *  Others:        ;
 *  date of completion:    
 *  date of last modify:   
 *********************************************************************/
int rgb888_write_jpeg(const char*filename, unsigned char *lpbuf, int width, int height)
{

    if(!lpbuf || !filename || width <= 0 || height <= 0 ) {
        printf("Parameter error!\n") ;
        return -1;
    }

    //1.JPEG对象分配空间并初始化
    struct jpeg_compress_struct cinfo ;
    struct jpeg_error_mgr jerr ;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);


    //2.初始化压缩对象
    FILE *fptr_jpg = fopen (filename, "wb");
    if(fptr_jpg == NULL) {
        printf("Encoder:open file failed!\n") ;
        return -1;
    }
    jpeg_stdio_dest(&cinfo, fptr_jpg);

    //3. 设置压缩参数
    cinfo.image_width      = width;
    cinfo.image_height     = height;
    cinfo.input_components = 3;
    cinfo.in_color_space   = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 92, TRUE);


    //4.JPEG图片压缩开始
    jpeg_start_compress(&cinfo, TRUE);


    //5.把RGB数据写入文件
    JSAMPROW row_pointer;
    unsigned int  row_stride = width * 3;  //原始数据是RGB88
    row_pointer = malloc(row_stride) ;     //分配一行的缓冲区
    //循环逐行写入JPEG文件
    while (cinfo.next_scanline < cinfo.image_height) {
        int x ;
        //把RGB数据装载到行缓冲区中
        for (x = 0; x < row_stride; x += 3) {
            row_pointer[x + 0] = lpbuf[x + 2];
            row_pointer[x + 1] = lpbuf[x + 1];
            row_pointer[x + 2] = lpbuf[x + 0];
        }
        
        //写入数据
        jpeg_write_scanlines (&cinfo, &row_pointer, 1);

        //指向下一行RGB数据
        lpbuf += row_stride;
    }

    //压缩结束
    jpeg_finish_compress(&cinfo);

    //关闭文件，销毁资源
    fclose(fptr_jpg);
    jpeg_destroy_compress(&cinfo);
    free(row_pointer) ;
    
	printf("Write jpeg file:%s \r\n", filename);

    return 0 ;

}


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
 *  date of completion:   
 *  date of last modify:   
 *********************************************************************/
int yuv422_write_raw(const char*filename, unsigned char *yuvdata, size_t data_len)
{

	int ret;

    if(!yuvdata || !filename ) {
        printf("Parameter error!\n") ;
        return -1;
    }

    FILE *outfile = fopen (filename, "wb");
    if(outfile == NULL) {
        printf("Encoder:open file failed!\n") ;
        return -1;
    }
   
	ret = fwrite(yuvdata, data_len, 1, outfile);
	if(ret == 0   && ferror(outfile)){
		perror("fwrite");
	    return -1;
	}	
	printf("fwrite return value:%d\r\n",ret);
 
    fclose(outfile);
	printf("Write yuv422 file:%s \r\n", filename);

    return 0 ;

}


