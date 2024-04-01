

#include "../include/global.h"
#include "../include/LList_Pinfo.h"

#define DEBUG 0

/* 

    @Feature: linklist initialization
    @Parameter: *lk
    @Return: *lk
    @Annotation: generate a new cycle link list 

*/
GP_HEAD *init_ClkList()
{
    #if 0
    // 内存
    GP_HEAD *lk = (GP_HEAD *)calloc(1, sizeof(GP_HEAD));
    #else
    // 堆区
    GP_HEAD *lk = (GP_HEAD *)malloc(sizeof(GP_HEAD));
    if (lk == NULL) {
        perror("HEAD malloc failed");
        return NULL;
    }
    #endif

    lk->pic_num = 0;
    lk->head = NULL;
    lk->tail = NULL;


    return lk;
}


/* 

    @Feature: insert a new node into link list
    @Parameter: *p, *lk
    @Return: void
    @Annotation: base on Cycle GP_HEAD

*/
void insert_HoTClkList(GP_HEAD *lk, elementType picname)
{
    GP_INFO *p = (GP_INFO *)malloc(sizeof(GP_INFO));
    p->picname = (elementType)malloc(strlen(picname) + 1);
    strcpy(p->picname, picname);
    printf("%s\n",p->picname);



    p->prev = NULL;
    p->next = NULL;

    if(lk->head == NULL)
    {
        lk->head = p;
        lk->tail = p;
    }
    else
    {
        #if 0 //交换     
            p->next = lk->head;
            lk->head->prev = p;
            lk->head = p;
        #else
            lk->tail->next = p;
            p->prev = lk->tail;
            lk->tail = p;

        #endif
    }
    lk->pic_num ++;
    lk->tail->next = lk->head; // connected head and tail node 
    lk->head->prev = lk->tail;
}


/* 

    @Feature: print all of the links list node
    @Parameter: *p, *lk
    @Return: void
    @Annotation: 遍历打印

*/
void printf_ClkList(GP_HEAD *lk)
{
    GP_INFO *p = lk->head; // for pointer to the head
    for(int i = 0; i < lk->pic_num; i++)
    {
        printf("%s\n", p->picname); // 循环打印
        p = p->next;
    }

    printf("\n");
    for(int i = 0; i < lk->pic_num; i++)
    {
        printf("%s\n", p->picname); // 循环打印
        p = p->prev;
    }
}


/* 

    @Feature: destroy all GP_INFO node structures
    @Parameter: *p, *lk
    @Return: void
    @Annotation: 遍历打印

*/
bool destroy_ClkList(GP_HEAD *lk)
{
    GP_INFO * p = lk->head;
	GP_INFO * q;
	//while(p)
	int i;
	for(i=0;i<lk->pic_num;i++)
	{
		q = p->next;//保存p的后继元素地址
		//删除p节点
		p->next = NULL;
        p->prev = NULL;
        free(p->picname);
		free(p);
		p = q;
	}
	
	lk->head = NULL;
	lk->tail = NULL;
	lk->pic_num = 0;
	
	free(lk);
    return true;
}


bool READ_Directory(const char *src, GP_HEAD *lk) {
    DIR *dir = opendir(src);
    if (dir == NULL) {
        perror("Open Picture directory Error");
        return false;
    }

    struct dirent * dp = NULL;

    while (dp = readdir(dir)) {
        // force writing like following
        if (0==strcmp(dp->d_name,".") || 0==strcmp(dp->d_name,"..") || 0==strcmp(dp->d_name,"icon"))
        {
            // closedir(dir);
            continue;
        }
        char buf_name[512] = "";

        sprintf(buf_name, "%s/%s", src, dp->d_name);

        #if DEBUG
        printf("%s\n",buf_name);
        #endif

        struct stat status;
        int ret = stat(buf_name, &status);
        if(-1 == ret)
		{
			perror("stat fail");
			return false;
		}

        if ((status.st_mode & S_IFMT) == S_IFDIR) {
            READ_Directory(buf_name, lk);
        }
        else if ((status.st_mode & S_IFMT) == S_IFREG) {
            int len = strlen(buf_name);
			if(strcmp(buf_name+len-4,".bmp")==0 || \
               strcmp(buf_name+len-4,".jpg")==0 || \
               strcmp(buf_name+len-5,".jpeg")==0) {        //后缀是 .bmp/.jpg/.jpeg
                insert_HoTClkList(lk, buf_name);
            //    error_handler();
            }
        }
    
    }

    closedir(dir);
    return true;
}