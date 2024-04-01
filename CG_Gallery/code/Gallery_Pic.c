/* encoding UTF-8 encoded by radish */

#include "../include/global.h"
#include "../include/Gallery_Pic.h"
#include "../include/Gallery_Init.h"
#include "../include/jpeglib.h"





extern int *plcd;


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
void DISPLAY_Point(int row, int col, int color)
{
    // limit the screen width and height area
    if (row >= 0 && row <= LCD_WIDTH && col >= 0 && col <= LCD_HEIGHT)
        *(plcd+col*LCD_WIDTH+row) = color;
    return;
}


/* 

    @Feature: replace the screen BGP settings
    @Parameter: 
        @plcd: screen mmap device
    @Return: true of false
    @Annotation: 

*/
bool DISPLAY_REP()
{
    for (int i = 0; i < LCD_HEIGHT; i++)
        for (int j = 0; j < LCD_WIDTH; j++)
            DISPLAY_Point(j,i,0x00);
    return true;
}

/* 

    @Feature: display a .bmp picture center
    @Parameter: 
        @bmpname: the .bmp pic path
        @plcd: screen mmap device
    @Return: void
    @Annotation: if the pic.status.size > LCD_SIZE will be wrong

*/
void DISPLAY_C_bmp(const char * bmpname)
{
    // open bmp file
    int fd_bmp = open(bmpname,O_RDONLY);
    if (fd_bmp == -1) {
        perror("Open the .bmp file error !");
        return;
    }

    unsigned char pinfo[4];
    int w = 0, h = 0;
    short int dep = 0;
    // detect the fd_bmp type
    // read (fd_bmp, bmp_type, 2);
    // if (bmp_type[0] != 0x42 || bmp_type != 0x4d);
    // get bmp file size

    lseek(fd_bmp, 0x12, SEEK_SET);
    read(fd_bmp, pinfo, 4);
    w = (pinfo[3] << 24) | (pinfo[2] << 16) | (pinfo[1] << 8) | (pinfo[0]);

    // the next is height
    read(fd_bmp, pinfo, 4);
    h = (pinfo[3] << 24) | (pinfo[2] << 16) | (pinfo[1] << 8) | (pinfo[0]);

    lseek(fd_bmp, 0x1c, SEEK_SET);
    read(fd_bmp, pinfo, 2);
    dep = (pinfo[1] << 8) | (pinfo[0]);

    if (!(dep == 24 || dep == 32)) {
        printf("Error Depth !\n Confirm the bmp picture error! \n");
        return ;
    }
    #if DEBUG
    printf("%s width: %d, height: %d, depth: %d\n", bmpname, w, h, dep);
    #endif

    int line_bytes = abs(w) * dep / 8; // number of line valid bytes
    int lz = 0;
    if (line_bytes % 4) 
        lz = 4 - line_bytes % 4;
    int size = line_bytes * abs(h); // number of valid bytes ---- pixel array size
    unsigned char rgb[LCD_SIZE];

    lseek(fd_bmp, 54, SEEK_SET);
    read(fd_bmp, rgb, size);

    unsigned char a, r, g, b;
    int color,i = 0, x, y;
    for (y = 0; y < (abs(h) > LCD_HEIGHT ? LCD_HEIGHT : abs(h)); y++) {
        for (x = 0; x < (abs(w) > LCD_WIDTH ? LCD_WIDTH : abs(w)); x++) {
            b = rgb[i++];
            g = rgb[i++];
            r = rgb[i++];
            if (dep == 32) a = rgb[i++];
            else a = 0;
            color = (a << 24) | (r << 16) | (g << 8) | b;
            
            // Display
            int x0 = (w > 0 ? 400-w/2 : abs(w/2)-400); // Initial position offset column
            int y0 = (h > 0 ? 240-h/2 : abs(h/2)-240); // Initial position offset row

            DISPLAY_Point( 
                           w > 0 ? (x0 + x) : (x0 + abs(w) - x - 1),\
                           h > 0 ? (y0 + h - y - 1) : (y0 + y),\
                           color 
                           );
        }
        // Maybe filling with lz in every line
        i += lz;
    }
}

/* 

    @Feature: display a .jpg picture center
    @Parameter: 
        @bmpname: the .jpeg pic path
        @plcd: screen mmap device
    @Return: void
    @Annotation: if the pic.status.size > LCD_SIZE will be wrong

*/
void DISPLAY_C_jpeg(const char * jpegname)
{
    // 1.declare a object to allocate and initial .jpg or .jpeg file
    struct jpeg_decompress_struct dinfo; // declare a decompress object
    struct jpeg_error_mgr j_ero; // declare error info object
    dinfo.err = jpeg_std_error(&j_ero); // Initial error info object
    jpeg_create_decompress(&dinfo); // initialize decompress object dinfo
    // detail will be explained to jpeglib.h

    // 2.Specifies the .jpg or .jpeg file to extract
    FILE *fp_jpg = fopen(jpegname, "r");
    if (fp_jpg == NULL) {
        perror("Open .jpeg or .jpg file error !");
    }
    jpeg_stdio_src(&dinfo, fp_jpg);

    // 3.Get picture info
    jpeg_read_header(&dinfo, TRUE);
    // 4.set Parameters

    // 5.decompress object
    jpeg_start_decompress(&dinfo);

    unsigned char *buffer = malloc(dinfo.output_width * dinfo.output_components);
    // save a line bytes to buffer
    // dinfo.output_scanline ; decompressed n line (0-N)
    while (dinfo.output_scanline < dinfo.output_height)
    {
        jpeg_read_scanlines(&dinfo, // decompress object
                            &buffer, // second pointer to data
                            1 // read line_bytes to decompress 
                            );
        
        unsigned char a,r,g,b;
        int color, x, n = 0;
        int x0 = (dinfo.output_width > 0 ? 400-dinfo.output_width/2 : abs(dinfo.output_width/2)-400); // Initial position offset column
        int y0 = (dinfo.output_height > 0 ? 240-dinfo.output_height/2 : abs(dinfo.output_height/2)-240); // Initial position offset row
        if (dinfo.output_components == 3) // 1 pixel == 3 bytes R G B
        {
            // Display
            for (x = 0; x < dinfo.output_width; x++)
            {
                r = buffer[n++];
                g = buffer[n++];
				b = buffer[n++];
                color = r<<16 | g<<8 | b;
                DISPLAY_Point(
                               x0 + x,
                               dinfo.output_scanline + y0 - 1,
                               color
                               );
            }
        }
        else if (dinfo.output_components == 4) // 1 pixel == 3 bytes A R G B
        {
            // Display
            for(x = 0;x < dinfo.output_width; x++)
			{
				a = buffer[n++];
				r = buffer[n++];
				g = buffer[n++];
				b = buffer[n++];
				color = a<<24 | r<<16 | g<<8 | b;
                DISPLAY_Point(
                                x0 + x,
                                y0 + dinfo.output_scanline - 1,
                                color
                                );
            }
        }
    }

    free(buffer);

    // 7.complete
    jpeg_finish_decompress(&dinfo);
    // 8.free dinfo
    jpeg_destroy_decompress(&dinfo);

    fclose(fp_jpg);
}


void DISPLAY_PIC(const char *filename)
{
    int len = strlen(filename);
    if (filename == NULL) return;
    else if (strcmp(filename+len-4,".bmp")==0) 
        DISPLAY_C_bmp(filename);
    else if (strcmp(filename+len-4,".jpg")==0 || strcmp(filename+len-5,".jpeg")==0)
        DISPLAY_C_jpeg(filename);
    else printf("Error!\n");
    
}