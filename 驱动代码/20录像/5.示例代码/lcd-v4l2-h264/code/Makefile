#可执行程序名
EXE:=app-v4l2-h264

#编译器名
CC:=aarch64-linux-gnu-gcc

#make cp 复制到的目标路径 
ROOTFS=/home/wriken/work/rootfs

#安装路径 
DEST=${ROOTFS}/bin

#编译标志l
CFLAGS=-I/home/wriken/work/arm-x264/include 
LDFLAG=-L/home/wriken/work/arm-x264/lib -pthread -lm -lx264  

#生成的可执行文件路径
BINDIR:=.

#生成的目标文件路径
DIR	:=./debug

#C文件编译选项显示所有警告信息，优化级别为2
#CFLAGS += -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=hard -mfpu=vfpv3 

#C++文件编译选项显示所有警告信息
CXXFLAGS+= -Wall -g 

SRCS:= $($(wildcard *.c))
OC	:= $(patsubst %.c, $(DIR)/%.o, $(wildcard *.c))
OBJS:= $(OC)  

$(BINDIR)/$(EXE): $(DIR) $(BINDIR) $(OBJS)   
	$(CC) -o $@ $(OBJS) $(LDFLAG)  

$(DIR):
	@mkdir -p  $(DIR) $(BINDIR) 
	
$(BINDIR):
	@mkdir -p  $(BINDIR) 

$(DIR)/%.o : %.c
	$(CC) -c $(CFLAGS)  $(LDFLAG)  $< -o $@

cp: $(BINDIR)/$(EXE)   
	@cp -frv $(BINDIR)/$(EXE)    $(DEST)  

PHONY:rebuild clean 
rebuild:clean $(EXE)    #先执行清理，在执行 all
clean:
	@#为观察RM这个预订义变量，使用它代替rm 
	$(RM)  -rf $(BINDIR)/$(EXE) $(DIR) $(OBJS) *~ *.bak




