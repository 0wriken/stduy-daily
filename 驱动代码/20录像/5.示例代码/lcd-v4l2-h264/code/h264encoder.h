#ifndef _H264ENCODER_H
#define _H264ENCODER_H

#include <stdint.h>
#include <stdio.h>
#include "x264.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

typedef unsigned char uint8_t;

typedef struct {
	x264_param_t *param;
	x264_t *handle;
	x264_picture_t *picture; 
	x264_nal_t *nal;
} Encoder;


void compress_begin(Encoder *en, int width, int height);

int encode_frame(Encoder *en, int type, uint8_t *in, uint8_t *out);

void compress_end(Encoder *en);

//-------------------------------------------------------------
void h264_init_encoder(int width, int height);


void h264_file_open(const char *h264_file_name ,int fd);

void h264_close_encoder(void);

void h264_file_close(void);


//把文件压缩成H264格式写入文件
void h264_encode_frame(uint8_t *yuv_frame, size_t yuv_length);

#endif

