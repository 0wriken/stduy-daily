#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
#include "lcd.h"


/********************************************************************
 *  Function��      lcd_show_jpeg()
 *  Description:   ��jpegͼƬ�����rgb888ͼƬ������ʾ��LCD����;
 *  Calls:         ;
 *  Called By:     ��
 *  Input��         file ��jpegͼƬ·��; x,y��lcd������ʾ��ʼ����
 *  Output��        none;
 *  Return :       0:�ɹ� ;    -1: ��ʾʧ�ܡ�
 *  Author:        chenzhifa;        ;
 *  Others:        none;
 *  date of completion:    
 *  date of last modify:   
 *********************************************************************/
int lcd_show_jpeg( const char *file, int x, int y)
{

	//1.JPEG�������ռ䲢��ʼ��
	//1)����JPEG���󼰴��������
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	//2)���ô�������
	cinfo.err = jpeg_std_error(&jerr);
	//2)����JPEG����
	jpeg_create_decompress(&cinfo);

	printf("line:%d\n\n", __LINE__);

	//2. ��ʼ���������
	//1����jpegͼ��
	FILE* infile;
	if ((infile = fopen(file, "rb")) == NULL) {
		fprintf(stderr, "open %s failed\n", file);
		return -1;
	}
	//2����jpeg������󵽴򿪵������ļ���
	jpeg_stdio_src(&cinfo, infile);

	//3. ��ȡJPEG�ļ���Ϣ
	jpeg_read_header(&cinfo, TRUE);  //��ȡjpeg�ļ�ͷ��Ϣ

	//4.���ý������
	//1�����ý�����ɫ�ռ����Ϊ RGB888
	cinfo.out_color_space = JCS_RGB;
	//2���趨��ѹ����������ͼ�񳤿���СΪԭͼ��1/2������ʵ���������
	cinfo.scale_num   = 1;
	cinfo.scale_denom = 1;

	//5.JPEGͼƬ���뿪ʼ
	jpeg_start_decompress(&cinfo);


	//6.��ȡjpeg���������ݲ����д���
	//1��Ϊһ��ɨ�����ϵ����ص����洢�ռ�
#if 0
	unsigned char  *buffer;
	buffer = (unsigned char *) malloc(cinfo.output_width * cinfo.output_components);
#else
	JSAMPARRAY buffer;     //����һ����άָ�룬ָ��һ�� char ���͵Ķ�ά����
	unsigned int row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
#endif
	//2) ����Ϊ��λ��ѭ����ȡjpeg����������
	while (cinfo.output_scanline < cinfo.output_height) {

		//(1)��ȡһ�����ݵ�buffer�У�ִ����ɺ� buffer �а�����һ����õ�һ������
		jpeg_read_scanlines(&cinfo, buffer, 1);

		//(2) ����洢��jpeg���ݻ�����������
#if 0
		int i;
		//���濪ʼ����һ�����ݣ���δ������û����о�����������ֱ��������ն��ϡ�
		for (i = 0; i < cinfo.output_width; i++) {
			//������ն��У�����ʹ��
			printf("%02X%02X%02X ", buffer[i * 3], buffer[i * 3 + 1], buffer[i * 3 + 2]);
			if (0 == ((i + 1) % 10) || i == cinfo.output_width - 1) {
				printf("\n");
			}
		}
		printf("least:%d\n\n", cinfo.output_height - cinfo.output_scanline);
#endif

		//��ʾһ������LCD����
		int j = 0;
		unsigned char *temp_src = buffer[0];
		for(j = 0; j < cinfo.output_width; j++) {
			//           RGB888        R                  G               B
			unsigned int color = temp_src[0] << 16 | temp_src[1] << 8 | temp_src[2];
			fb_show_pixel(x + j,  y, color);
			temp_src += 3;       //����ָ������3�ֽڣ�ָ����һ����λ��
		}
		y++;                     //��һ�У�����������
		//printf("cinfo.output_scanline:%d\r\n",cinfo.output_scanline);
	}

	printf("-----decode end-----\r\n");

	//7. �����������Ҫ����jpeg_finish_decompress ������
	jpeg_finish_decompress(&cinfo);

	//8. �ͷŽ�����󣬹ر��ļ�
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

	return 0;
}


