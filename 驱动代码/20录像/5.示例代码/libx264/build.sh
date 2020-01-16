#!/bin/bash
#20181223 modify by chenzhifa
set -e

#Դ��Ŀ¼
SOURCE_DIR=./source

#����Ŀ¼
BUILD_DIR=/tmp/build

#���ļ�ϵͳ·���������Լ�������޸�
export ROOTFS=~/work/rootfs-hf-mfc

#���밲װ����·���������Լ�������޸ģ�Ĭ�ϵ�ǰĿ¼��/usr/arm/x264
export INSTALL_DIR=/usr/arm/x264

#�������������ǰ׺
export CROSS_COMPILE_PREFIX=arm-linux-gnueabihf-

#Ŀ������ͣ������Լ�������޸�
export HOST_ARCH=arm-linux-gnueabihf

#����������������
export CC="${CROSS_COMPILE_PREFIX}gcc"
export CPP="${CROSS_COMPILE_PREFIX}gcc -E"
export AR="${CROSS_COMPILE_PREFIX}ar"
export RANLIB="${CROSS_COMPILE_PREFIX}ranlib"

#��������Ŀ¼
if [ ! -d $BUILD_DIR ]; then
	mkdir $BUILD_DIR -p
fi

#####################################################################
#### ���롢��װ x264 ����
#####################################################################

function build_x264(){
	# build x264-snapshot-20180727-2245.tar.bz2
	echo "============Start build x264-snapshot-20180727-2245.tar.bz2 ========"

	#��ѹԴ��Դ�룬���ҽ���
	tar -xf  $SOURCE_DIR/x264-snapshot-20180727-2245.tar.bz2  -C $BUILD_DIR
	cd $BUILD_DIR/x264-snapshot-20180727-2245

	#����
	CC=${CROSS_COMPILE_PREFIX}gcc \
	./configure \
	--host=$HOST_ARCH \
	--prefix=$INSTALL_DIR \
	 --enable-shared \
	 --enable-static \
	 --extra-cflags="-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=hard -mfpu=vfpv3 "  \
	 --disable-opencl


	#���룬��װ
	make -j8 &&  make install -j8 && cd -

	#������
	if [ $? -eq 0 ]; then
		echo "====Build  x264 ok!===="
	else
		echo "====Build  x264 failed!===="
		exit 1
	fi

	#���ƶ�̬�⵽���ļ�ϵͳ
	cp $INSTALL_DIR/lib/libx264*so*  $ROOTFS/lib/ -fv
}



#####################################################################
#### ����÷� ����
#####################################################################
usage()
{
	echo "====USAGE: build.sh modules===="
	echo "x264            -build x264"
}


#####################################################################
### �����ǵ��ú���
#####################################################################

#��������Ƿ�Ϸ�
if [ $# != 1 ] ; then
	usage
	exit 1;
fi

#�������Ŀ��
BUILD_TARGET=$1

#=====================================================
# build target
#=====================================================
if [ $BUILD_TARGET == x264 ];then
	build_x264
	exit 0
elif [ $BUILD_TARGET == cleanall ];then
	#clean_all
	exit 0
elif [ $BUILD_TARGET == --help ] || [ $BUILD_TARGET == help ] || [ $BUILD_TARGET == -h ];then
	usage
	exit 0
else
	echo "No taget to build!"
	exit 1
fi

