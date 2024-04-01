
#ifndef __GALLERY_OPERA_H__
#define __GALLERY_OPERA_H__


#include "global.h"
#include "Gallery_Pic.h"
#include "Gallery_Init.h"
#include "jpeglib.h"
#include "LList_Pinfo.h"




//Get Position of Touch Screen 
int Get_xy(int fd_in, int *x1, int *y1, int *x2, int *y2);


// reset Position
void Clear(int sc_x1, int sc_y1, int sc_x2, int sc_y2);



GP_INFO * Click_Control(int sc_x1, int sc_y1, int sc_x2, int sc_y2, GP_INFO * pic);












#endif