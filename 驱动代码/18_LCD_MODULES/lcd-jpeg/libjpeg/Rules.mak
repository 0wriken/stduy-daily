TOPDIR= ..
CROSS = arm-none-linux-gnueabi-
CC:= ${CROSS}gcc

#LDFLAGS += -static  
EXTRA_LIBS += 
EXP_INSTALL = install -m 755 
INSTALL_DIR = ../bin
