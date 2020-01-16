#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
#include <stdlib.h>



/********************************************************************
 *  Function��      rgb888_write_jpeg()
 *  Description:   rgb888����ת���浽jpegͼ���ļ�;
 *  Calls:         ;
 *  Called By:
 *  Input��         filename:jpegͼƬ���ַ���; lpbuf:rgb����ָ��
 *                 width,height :����ͷ�ɼ�������ͼƬ���ݿ�Ⱥ͸߶�
 *  Output��        
 *  Return :       0:д��ɹ�  ;      -1:ʧ��;
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

    //1.JPEG�������ռ䲢��ʼ��
    struct jpeg_compress_struct cinfo ;
    struct jpeg_error_mgr jerr ;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);


    //2.��ʼ��ѹ������
    FILE *fptr_jpg = fopen (filename, "wb");
    if(fptr_jpg == NULL) {
        printf("Encoder:open file failed!\n") ;
        return -1;
    }
    jpeg_stdio_dest(&cinfo, fptr_jpg);

    //3. ����ѹ������
    cinfo.image_width      = width;
    cinfo.image_height     = height;
    cinfo.input_components = 3;
    cinfo.in_color_space   = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 92, TRUE);


    //4.JPEGͼƬѹ����ʼ
    jpeg_start_compress(&cinfo, TRUE);


    //5.��RGB����д���ļ�
    JSAMPROW row_pointer;
    unsigned int  row_stride = width * 3;  //ԭʼ������RGB88
    row_pointer = malloc(row_stride) ;     //����һ�еĻ�����
    //ѭ������д��JPEG�ļ�
    while (cinfo.next_scanline < cinfo.image_height) {
        int x ;
        //��RGB����װ�ص��л�������
        for (x = 0; x < row_stride; x += 3) {
            row_pointer[x + 0] = lpbuf[x + 2];
            row_pointer[x + 1] = lpbuf[x + 1];
            row_pointer[x + 2] = lpbuf[x + 0];
        }
        
        //д������
        jpeg_write_scanlines (&cinfo, &row_pointer, 1);

        //ָ����һ��RGB����
        lpbuf += row_stride;
    }

    //ѹ������
    jpeg_finish_compress(&cinfo);

    //�ر��ļ���������Դ
    fclose(fptr_jpg);
    jpeg_destroy_compress(&cinfo);
    free(row_pointer) ;
    
	printf("Write jpeg file:%s \r\n", filename);

    return 0 ;

}


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


