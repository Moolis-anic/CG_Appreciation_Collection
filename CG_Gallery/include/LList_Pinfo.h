
#ifndef __LLIST_PINFO_H__
#define __LLIST_PINFO_H__

#include "global.h"

// Declare a type named elementType for easy modification
typedef char * elementType; //声明一个类型为elementtype 便于修改

// To define a global structure for save pic data
typedef struct _GALLERY_PIC_INFO_ {
    struct _GALLERY_PIC_INFO_ *prev; // Previous picture
    struct _GALLERY_PIC_INFO_ *next; // Next picture
    elementType picname; // Pointer to current pic path
    
}GP_INFO;

// To define a global structure for picture path header
typedef struct _GALLERY_PIC_HEADER_INFO_ {
    GP_INFO *head; // Pointer to first picture path
    GP_INFO *tail; // Pointer to last picture path
    int pic_num; // Number of pictures

}GP_HEAD;



/* 

    @Feature: linklist initialization
    @Parameter: *lk
    @Return: *lk
    @Annotation: generate a new cycle link list 

*/
GP_HEAD *init_ClkList();


/* 

    @Feature: insert a new node into link list
    @Parameter: *p, *lk
    @Return: void
    @Annotation: base on Cycle GP_HEAD

*/
void insert_HoTClkList(GP_HEAD *lk, elementType data);


/* 

    @Feature: print all of the links list node
    @Parameter: *p, *lk
    @Return: void
    @Annotation: 遍历打印

*/
void printf_ClkList(GP_HEAD *lk);


/* 

    @Feature: destroy all GP_INFO node structures
    @Parameter: *p, *lk
    @Return: void
    @Annotation: 遍历打印

*/
bool destroy_ClkList(GP_HEAD *lk);



bool READ_Directory(const char *src, GP_HEAD *lk);





#endif // _GALLERY_PICTURE_PATH
