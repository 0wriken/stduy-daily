

/*=============================================================================
#     FileName: h264encoder.c
#         Desc: this program aim to get image from USB camera,
#               used the V4L2 interface.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "h264encoder.h"

#define X264_MAX(a,b) ( (a)>(b) ? (a) : (b) )


//把文件压缩成H264格式写入文件
void h264_encode_frame(uint8_t *yuv_frame, size_t yuv_length);

int s_fd;
Encoder en;
FILE *h264_fp;
char *h264_buf;

/* ticks/frame = ticks/second / frames/second */
int64_t ticks_per_frame;

/*
* In order to replicate x264CLI's option handling, these functions MUST be called 
* in the following order: 
* 1) x264_param_default_preset 
* 2) Custom user options (via param_parse or directly assigned variables) 
* 3) x264_param_apply_fastfirstpass 
* 4) x264_param_apply_profile 
*/
void compress_begin(Encoder *en, int width, int height)
{
    en->param = (x264_param_t *) malloc(sizeof(x264_param_t));
    en->picture = (x264_picture_t *) malloc(sizeof(x264_picture_t));

#if 0
    x264_param_default(en->param); //set default param
    //en->param->rc.i_rc_method = X264_RC_CQP;
    // en->param->i_log_level = X264_LOG_NONE;
    //en->param->rc.i_rc_method =X264_RC_ABR;

    en->param->i_threads         = X264_SYNC_LOOKAHEAD_AUTO;
    en->param->i_width           = width; //set frame width
    en->param->i_height          = height; //set frame height
    en->param->i_csp             = X264_CSP_I422;
	en->param->i_frame_total     = 0;
	en->param->i_keyint_max      = 10;
	en->param->rc.i_lookahead    = 0; 
	en->param->i_bframe          = 5; 
	en->param->b_open_gop        = 0;
	en->param->i_bframe_pyramid  = 0;
	en->param->i_bframe_adaptive = X264_B_ADAPT_TRELLIS;
	en->param->rc.i_bitrate      = 1024 * 10;//rate 10 kbps
	en->param->i_fps_num         = 12; 
	en->param->i_fps_den         = 1;

#else   //不设置帧率，默认是25
    x264_param_default(en->param);                //set default param
	en->param->i_width			 = width;         //set frame width
	en->param->i_height 		 = height;        //set frame height
	en->param->i_csp			 = X264_CSP_I422;
	///en->param->i_csp			 = X264_CSP_YUYV;
#endif

     // 设置 Profile.使用 high422
	x264_param_apply_profile(en->param, x264_profile_names[4]); 

	//打开编码器句柄,通过 x264_encoder_parameters 得到设置给X264的参数.
	//通过x264_encoder_reconfig 更新X264的参数
	if ((en->handle = x264_encoder_open(en->param)) == 0) {
		return;
	}
   
	/* Create a new pic */
	x264_picture_alloc(en->picture, X264_CSP_I422, en->param->i_width,	en->param->i_height);


}


int encode_frame(Encoder *en, int type, uint8_t *in, uint8_t *out)
{
    x264_picture_t pic_out;
    int index_y, index_u, index_v;
    int num;
    int nNal = -1;
    int i = 0;
    static long int pts = 0;
    uint8_t *p_out = out;
    char *y = en->picture->img.plane[0];
    char *u = en->picture->img.plane[1];
    char *v = en->picture->img.plane[2];
    char * ptr;
	int i_frame_size;

    index_y = 0;
    index_u = 0;
    index_v = 0;

    num = en->param->i_width * en->param->i_height * 2 - 4  ;
	
    /*把YUV422转换为YUV422P  */

    for(i = 0; i < num; i = i + 4) {
        *(y + (index_y++)) = *(in + i);
        *(u + (index_u++)) = *(in + i + 1);
        *(y + (index_y++)) = *(in + i + 2);
        *(v + (index_v++)) = *(in + i + 3);
    }


    switch (type) {
        case 0:
            en->picture->i_type = X264_TYPE_P;
            break;
        case 1:
            en->picture->i_type = X264_TYPE_IDR;
            break;
        case 2:
            en->picture->i_type = X264_TYPE_I;
            break;
        default:
            en->picture->i_type = X264_TYPE_AUTO;
            break;
    }

    en->picture->i_pts = pts++;
	i_frame_size = x264_encoder_encode(en->handle, &(en->nal), &nNal, en->picture, &pic_out) ;
    if (i_frame_size < 0) {
		perror("error x264_encoder_encode");
        return -1;
    }
#if 0
    for (i = 0; i < nNal; i++) {
        memcpy(p_out, en->nal[i].p_payload, en->nal[i].i_payload);
        p_out += en->nal[i].i_payload;
        result += en->nal[i].i_payload;
    }
#else
	if(i_frame_size){
		printf("i_frame_size:%d\r\n",i_frame_size);
		memcpy(p_out, en->nal->p_payload, i_frame_size);
	}
#endif

    return i_frame_size;
}


//输出最后一帧数据编码中编码器中剩余的码流数据
int  flush_encoder(Encoder *en)
{
    int i_frame_size;
    int i = 0, j = 0;
    int nNal = -1;
    
    x264_picture_t pic_out={0};

	//* 获取X264中缓冲帧数.
	int iFrames = x264_encoder_delayed_frames(en->handle);
	printf("curent delayed frames:%d \r\n",iFrames);

    //输出编码器中剩余的码流数据
#if 0
    while(1) {
        i_frame_size = x264_encoder_encode(en->handle, &(en->nal), &nNal, NULL, &pic_out);
        if(i_frame_size == 0) {
            break;
        }
        
        for (j = 0; j < nNal; ++j) {
            ret = fwrite(en->nal[j].p_payload, en->nal[j].i_payload, 1, h264_fp) ;
            if(ret > 0) {
               //printf("Flush 1 frame.\n");//
            } else {
                perror("encode_frame fwrite err\n");
            }
        }
    }
#endif
    /* Flush delayed frames */
    while( x264_encoder_delayed_frames( en->handle ))
    {
        i_frame_size = x264_encoder_encode(en->handle, &(en->nal), &nNal, NULL, &pic_out);
        if( i_frame_size < 0 ){
			perror("error x264_encoder_encode \r\n");
			return -1;
		}

        else if( i_frame_size )
        {
            if( !fwrite( en->nal->p_payload, i_frame_size, 1, h264_fp )){
				perror("error fwrite nal->p_payload\r\n");
				return -1;
			}
        }
    }

	return 0;
}


void compress_end(Encoder *en)
{

    //输出最后一帧数据编码中编码器中剩余的码流数据
    flush_encoder(en);
    
    if (en->handle) {
        x264_encoder_close(en->handle);
    }

    if (en->picture) {
        x264_picture_clean(en->picture);
        free(en->picture);
        en->picture = 0;
    }

    if (en->param) {
        free(en->param);
        en->param = 0;
    }
}


void h264_init_encoder(int width, int height)
{
    compress_begin(&en, width, height);
    h264_buf = (char *) malloc( width * height * 2); 
}


void h264_file_open(const char *h264_file_name,int fd)
{
    if(h264_file_name==NULL)
    {
        s_fd=fd;
        return ;
    }
    else
    {
        h264_fp = fopen(h264_file_name, "wa+");    
        return ;
    }
    
    
}

void h264_close_encoder(void)
{
    compress_end(&en);
    free(h264_buf);
}

void h264_file_close(void)
{
    if(h264_fp==NULL)
    {
        return ;
    }
    fclose(h264_fp);
}


//把文件压缩成H264格式写入文件
void h264_encode_frame(uint8_t *yuv_frame, size_t yuv_length)
{
    int h264_length = 0;
    static int count = 0;
    h264_length = encode_frame(&en, -1, yuv_frame, h264_buf);
    if (h264_length > 0) {
        if(s_fd)
        {
            //发送给服务器数据
            if(send(s_fd,h264_buf,strlen(h264_buf),0)==-1)
            {
                perror("send");
                exit(0);
            }
        }
        if(h264_fp!=NULL)
        {
            if(fwrite(h264_buf, h264_length, 1, h264_fp) > 0) {
            } else {
                perror("encode_frame fwrite err\n");
            }
        }
    }
}


