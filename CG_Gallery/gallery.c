/* encoding UTF-8 encoded by radish */

#include "include/global.h"
#include "include/Gallery_Init.h"
#include "include/Gallery_Pic.h"
#include "include/Gallery_Opera.h"
#include "include/LList_Pinfo.h"
#include "include/jpeglib.h"



// define a global variable pointer for memory
int *plcd = NULL;


int main(int argc, char **argv)
{
    int fd_lcd = LCD_Init();
    int fd_in = LCD_IN_Init();

    plcd = (int *)mmap(NULL, // allocated by system
                         LCD_SIZE, // size of screen
                         PROT_READ | PROT_WRITE, // read/write access permissions
                         MAP_SHARED, // map method
                         fd_lcd, // file descriptor
                         0); // cursor offset
    if (plcd == MAP_FAILED) {
        perror("Failed to map /dev/fb0");
        return -1;
    }
    GP_HEAD * G = init_ClkList();

    if(!READ_Directory("Picture", G))
        printf("Directory Open fail !\n");
    
    
    // printf_ClkList(G);
    if (G->pic_num == 0) 
    {
        printf("No Picture!\n");
        return -2;
    }
    // printf("num = %d\n", G->pic_num);
    int sc_x1 = 0, sc_y1 = 0, sc_x2 = 0, sc_y2 = 0;
    DISPLAY_C_bmp("Picture/icon/Gallery_BGP.bmp");
    GP_INFO * p = G->head;

    while (1) {
        // get input position
        // error_handler();
        Get_xy(fd_in, &sc_x1, &sc_y1, &sc_x2, &sc_y2);
        // error_handler();
        p = Click_Control(sc_x1, sc_y1, sc_x2, sc_y2, p);
        if (sc_x1 > 750 && sc_y1 < 50)
            break;
    }

    








    sleep(5); // sleep
    DISPLAY_REP();
    // DISPLAY_C_jpeg("Picture/evilDemon.jpg");






    destroy_ClkList(G);





    LCD_Close(fd_lcd, fd_in);
    munmap(plcd, LCD_SIZE);
    return 0;
}