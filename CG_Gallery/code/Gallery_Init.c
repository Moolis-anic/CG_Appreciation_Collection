/* encoding UTF-8 encoded by radish */

#include "../include/global.h"
#include "../include/Gallery_Init.h"



/* 

    @Feature: Init a screen interface file descriptor with open fd_lcd
    @Parameter: 
        @fd_lcd: file descriptor to be opened
        @plcd: mmap the screen pointer
    @Return: -1 or fd_lcd
    @Annotation: 

*/
int LCD_Init(void)
{
    // open a screen file descriptor
    int fd_lcd = open(LCD_PATH, O_RDWR);
    if (fd_lcd < 0) {
        perror("LCD_Init error !");
        return -1;
    }
    return fd_lcd;
}


/* 

    @Feature: close the screen fd_lcd, and unmap the screen plcd
    @Parameter: 
        @fd: screen to be closed
    @Return: void
    @Annotation: 

*/
void LCD_Close(int fd_lcd, int fd_in)
{
    close(fd_in);
    close(fd_lcd);
}


/* 

    @Feature: Init a touch interface file descriptor with open fd_in
    @Parameter: 
        @fd_in: file descriptor to be opened
        @ev: event object 
    @Return: -1 or fd_in
    @Annotation: 
*/
int LCD_IN_Init(void)
{
    int fd_in = open(INPUT_PATH, O_RDONLY);
    if (fd_in < 0) {
        perror("LCD_IN_Init error !");
        return -1;
    }
    return fd_in;
}

