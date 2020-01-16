#可执行程序名
EXE:=v4l2-lcd-jpeg

#编译器名
CC:=aarch64-linux-gnu-gcc

#make cp 复制到的目标路径 
DEST := /home/wriken/work/rootfs/bin

#编译标志
INCLUDE = -Wall -I/usr/arm/libjpeg/include 
LDFLAG  = -L/usr/arm/libjpeg/lib   -ljpeg -lpthread -static

#生成的可执行文件路径
BINDIR:=.

#生成的目标文件路径
DIR	:=./debug

#C文件编译选项显示所有警告信息，优化级别为2
CFLAGS:= -Wall -O1 -fpic  $(INCLUDE)

#C++文件编译选项显示所有警告信息
CXXFLAGS:= -Wall -g 

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
	@cp -frv $(BINDIR)/$(EXE)   $(DEST)  

PHONY:rebuild clean 
rebuild:clean $(EXE)    #先执行清理，在执行 all
clean:
	@#为观察RM这个预订义变量，使用它代替rm 
	$(RM)  -rf $(BINDIR)/$(EXE) $(DIR) $(OBJS) *~ *.bak




