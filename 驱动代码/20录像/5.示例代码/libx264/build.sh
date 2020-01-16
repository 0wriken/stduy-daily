#!/bin/bash
#20181223 modify by chenzhifa
set -e

#源码目录
SOURCE_DIR=./source

#编译目录
BUILD_DIR=/tmp/build

#根文件系统路径，根据自己的情况修改
export ROOTFS=~/work/rootfs-hf-mfc

#编译安装本地路径，根据自己的情况修改，默认当前目录的/usr/arm/x264
export INSTALL_DIR=/usr/arm/x264

#导出交叉编译器前缀
export CROSS_COMPILE_PREFIX=arm-linux-gnueabihf-

#目标机类型，根据自己的情况修改
export HOST_ARCH=arm-linux-gnueabihf

#导出编译器工具链
export CC="${CROSS_COMPILE_PREFIX}gcc"
export CPP="${CROSS_COMPILE_PREFIX}gcc -E"
export AR="${CROSS_COMPILE_PREFIX}ar"
export RANLIB="${CROSS_COMPILE_PREFIX}ranlib"

#创建编译目录
if [ ! -d $BUILD_DIR ]; then
	mkdir $BUILD_DIR -p
fi

#####################################################################
#### 编译、安装 x264 函数
#####################################################################

function build_x264(){
	# build x264-snapshot-20180727-2245.tar.bz2
	echo "============Start build x264-snapshot-20180727-2245.tar.bz2 ========"

	#解压源码源码，并且进入
	tar -xf  $SOURCE_DIR/x264-snapshot-20180727-2245.tar.bz2  -C $BUILD_DIR
	cd $BUILD_DIR/x264-snapshot-20180727-2245

	#配置
	CC=${CROSS_COMPILE_PREFIX}gcc \
	./configure \
	--host=$HOST_ARCH \
	--prefix=$INSTALL_DIR \
	 --enable-shared \
	 --enable-static \
	 --extra-cflags="-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=hard -mfpu=vfpv3 "  \
	 --disable-opencl


	#编译，安装
	make -j8 &&  make install -j8 && cd -

	#输出结果
	if [ $? -eq 0 ]; then
		echo "====Build  x264 ok!===="
	else
		echo "====Build  x264 failed!===="
		exit 1
	fi

	#复制动态库到根文件系统
	cp $INSTALL_DIR/lib/libx264*so*  $ROOTFS/lib/ -fv
}



#####################################################################
#### 输出用法 函数
#####################################################################
usage()
{
	echo "====USAGE: build.sh modules===="
	echo "x264            -build x264"
}


#####################################################################
### 以下是调用函数
#####################################################################

#参数检测是否合法
if [ $# != 1 ] ; then
	usage
	exit 1;
fi

#保存编译目标
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

