TARGET:=GALLERY
#定义变量，保存最终的目标名

CC:=arm-linux-gcc
#定义变量，保存编译器

SRCS:=$(wildcard *.c)
#定义变量 SRCS 用来保存当前目录下的所有 .c文件列表

SRCS+=$(wildcard code/*.c)

# SRCS+=$(wildcard path/*.c)
#如果说 .c文件在多个目录下，就根据情况去增加 path就是文件的路径

OBJS:=$(patsubst %.c,%.o,$(SRCS))
#把 SRCS 字符串中的 .c 替换成了 .o

SHF:=/home/radish/nfsboot/
#指定共享文件夹

INC:=-I /opt/arm_libs/include
#指定头文件的搜索路径
INC+=-I ./include

#INC+=-I path
#如果头文件存在不同的目录下，需要用多个-I 去指定

LIB:=-L /opt/arm_libs/lib -ljpeg
#指定库的搜索路径及库的名字
# LIB+=-L ./
#LIB+=-L path -l xxxx
#如果有多个库文件，就分别指定即可

$(TARGET) : $(OBJS)
	$(CC) $^ $(LIB) -o $(TARGET)
	cp $(TARGET) $(SHF)
	chmod 777 $(SHF)$(TARGET)
%.o : %.c
#%是通配 %.o匹配所有的.o文件
	$(CC) -c $^ $(INC) -o $@
	
clean :
	rm $(OBJS) $(TARGET)
	rm $(SHF)$(TARGET) 
