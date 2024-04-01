#ifndef __GALLERY_PIC_H__
#define __GALLERY_PIC_H__

#include "global.h"
#include "jpeglib.h"



/* 

    @Feature:  set the screen (row, col) to color based 
    @Parameter: 
        @plcd: screen mmap device
        @row: the row of setting point
        @col: the col of setting point
        @color: the color of setting point
    @Return: void
    @Annotation: 

*/
void DISPLAY_Point(int row, int col, int color);


/* 

    @Feature: replace the screen BGP settings
    @Parameter: 
        @plcd: screen mmap device
    @Return: true of false
    @Annotation: 

*/
bool DISPLAY_REP();


/* 

    @Feature: display a .bmp picture center
    @Parameter: 
        @bmpname: the .bmp pic path
        @plcd: screen mmap device
    @Return: void
    @Annotation: if the pic.status.size > LCD_SIZE will be wrong

*/
void DISPLAY_C_bmp(const char * bmpname);


/* 

    @Feature: display a .jpg picture center
    @Parameter: 
        @bmpname: the .jpeg pic path
        @plcd: screen mmap device
    @Return: void
    @Annotation: if the pic.status.size > LCD_SIZE will be wrong

*/
void DISPLAY_C_jpeg(const char * jpegname);



void DISPLAY_PIC(const char *filename);
// continue...



#endif