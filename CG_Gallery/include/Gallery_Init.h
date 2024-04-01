#ifndef __GALLERY_INIT_H__
#define __GALLERY_INIT_H__

#include "global.h"


#define LCD_PATH "/dev/fb0"
#define INPUT_PATH "/dev/input/event0"


#define LCD_WIDTH 800
#define LCD_HEIGHT 480
#define LCD_SIZE 800*480*4


// declare a global structure alias
struct input_event ev;




/* 

    @Feature: Init a screen interface file descriptor with open fd_lcd
    @Parameter: 
        @fd_lcd: file descriptor to be opened
        @plcd: mmap the screen pointer
    @Return: -1 or fd_lcd
    @Annotation: 

*/
int LCD_Init(void);

/* 

    @Feature: close the screen fd_lcd, touch screen fd_in and unmap the screen plcd
    @Parameter: 
        @fd: screen to be closed
    @Return: void
    @Annotation: 

*/
void LCD_Close(int fd_lcd, int fd_in);

/* 

    @Feature: Init a touch interface file descriptor with open fd_in
    @Parameter: 
        @fd_in: file descriptor to be opened
        @
    @Return: 
    @Annotation: 
*/
int LCD_IN_Init(void);












#endif
/* 
----------------------------------------------------------------
This is a type declaration. Do not change it!
@author Radish ~!
@email " aniyo6890@163.com "
@echo " donate me if you want to contribute "
----------------------------------------------------------------
*/