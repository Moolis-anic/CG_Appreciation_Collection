#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h> // standard library headers
#include <sys/types.h> // open library headers file
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close/read/write library headers file
#include <string.h> // string library headers file
#include <stdlib.h> // stdlib library headers file
#include <stdbool.h>
#include <sys/mman.h> // 映射的头文件
#include <dirent.h> // dir operations library headers file
#include <netdb.h>
#include <termios.h>
#include <errno.h>
#include <math.h>
#include <time.h>
// #include <random.h>


#include <linux/input.h> // 输入事件
// #include <linux/input-event-codes.h> // 触控输入事件

#define error_handler() {fprintf(stderr, "[ %s - %d ]\n", __FUNCTION__, __LINE__);}




/* 

    @Feature: 
    @Parameter: 
    @Return: 
    @Annotation: 

*/





#endif


/* 
----------------------------------------------------------------
This is a type declaration. Do not change it!
@author Radish ~!
@email " aniyo6890@163.com "
@echo " donate me if you want to contribute "
----------------------------------------------------------------
*/