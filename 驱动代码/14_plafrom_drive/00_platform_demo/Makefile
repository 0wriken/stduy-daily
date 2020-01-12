# Makefile 2.6
#  platform_driver  platform_device 是模块名，也是对应的c文件名。 
obj-m += platform_device.o  platform_driver.o
#应用程序源文件列表
APP_SRC :=app.c
#应用程序名
#APP_NAME:=app
#编译器
cc:=aarch64-linux-gnu-gcc

# KDIR  内核源码路径，根据自己需要设置
# X86 源码路径统一是/lib/modules/$(shell uname -r)/build
#如果要编译ARM的模块，则修改成ARM的内核源码路径 
KDIR  := /home/edu118/work/nanopc-t4/kernel-rockchip

#根文件系统路径
ROOTFS :=/home/edu118/work/nanopc-t4/rootfs

#模块最终存放
DEST_DIR :=$(ROOTFS)/home

all:
	@make -C $(KDIR) M=$(PWD) modules   
#	@$(cc) $(APP_SRC) -o $(APP_NAME)	
	@rm -fr  .tmp_versions *.o *.mod.o *.mod.c  *.bak *.symvers *.markers *.unsigned *.order *~ .*.*.cmd .*.*.*.cmd
	@cp -fv *.ko  $(APP_NAME)	 ${DEST_DIR}
		
clean:
	@make  -C $(KDIR)   M=$(PWD)  modules  clean
	@rm -f *.ko  $(APP_NAME) *.o *.mod.o *.mod.c  *.bak *.symvers *.markers *.unsigned *.order *~

install:
	@make -s -C ${KDIR} M=$PWD INSTALL_MOD_PATH=${ROOTFS} modules_install
