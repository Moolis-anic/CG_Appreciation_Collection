/* encoding UTF-8 encoded by radish */

#include "../include/global.h"
#include "../include/Gallery_Pic.h"
#include "../include/Gallery_Init.h"
#include "../include/Gallery_Opera.h"
#include "../include/LList_Pinfo.h"
#include "../include/jpeglib.h"




//Get Position of Touch Screen 
int Get_xy(int fd_in, int *x1, int *y1, int *x2, int *y2) {
    int count = 0;
    while (1) {
        //Load Position X Y of Touch Screen
        read(fd_in, &ev, sizeof(ev));
        if (ev.type == EV_ABS && count == 0) {         //Judge Event
            if (ev.code == ABS_X) {                    //X position
                *x1 = ((ev.value*800)/1024);           //First

            }
        }

        if (ev.type == EV_ABS && count == 0) {         //Judge Event
            if (ev.code == ABS_Y) {                    //Y position
                *y1 = ((ev.value*480)/600);
                count ++;
            }
        }

        if (ev.type == EV_ABS && count != 0) {         //Judge Event
            if (ev.code == ABS_X) {                    //X position
                *x2 = ((ev.value*800)/1024);
            }
        }
        
        if (ev.type == EV_ABS && count != 0) {         //Judge Event
            if (ev.code == ABS_Y) {                    //Y position
                *y2 = ((ev.value*480)/600);
            }
        }

        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
            break;                                      //Quit
        
    }
}

GP_INFO * Click_Control(int sc_x1, int sc_y1, int sc_x2, int sc_y2, GP_INFO *pic) { 


    // char buf[256]; // save path temp
    int slope = (sc_y2 - sc_y1) / (sc_x2 - sc_x1);
    // error_handler();
    if (sc_x2 - sc_x1 > 0) {              // prev operation ?
        if (slope > 1) {
            // up operation
        }
        else {
            // prev operation
            pic = pic->prev;
            DISPLAY_REP();
            DISPLAY_PIC(pic->picname);
            printf("%s Picture \n",pic->picname);
            // error_handler();
        }
    }
    else if (sc_x2 - sc_x1 < 0) {         // next operation ?
        if (slope < -1) {
            // down operation
        } 
        else {
            // next operation
            pic = pic->next;
            DISPLAY_REP();
            DISPLAY_PIC(pic->picname);
            printf("%s Picture \n",pic->picname);
        }
    }


    return pic; // return pic
}