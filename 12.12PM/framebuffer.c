/************************************************
* 
*  OLALA LE TUTO DE FRAME BUFFER
*  cours embeded day 5
*  guigur & domo 12/15
*
************************************************/
#include "my.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define RGB16(R,G,B) ((R&0xf8)<<8)|((G&0xfc)<<3)|((B&0xf8)>>3)
#define RGB24(R,G,B) ((R<<16)|(G<<8)|B)
#define RGB32(A,R,G,B) ((A<<24)|(R<<16)|(G<<8)|B)

#define  SCREENWIDTH 480
#define  SCREENHEIGHT 272
#define  BPP 16

void	draw_pix(int x, int y, int color, char *fbmem_addr)
{
  *(unsigned short*)(fbmem_addr + SCREENWIDTH*x*BPP/8+y*BPP/8) = color;
}

void	draw_rect(int x0, int y0, int x1, int y1, int color, char *fbmem_addr)
{
  int	x = x0;
  int	y = y0;

    while (y<y1-y0 && y < SCREENWIDTH)
    {
      while (x<x1-x0 && x < SCREENHEIGHT)
	{
	  draw_pix(x, y, color, fbmem_addr);
	  x++;
	}
      x = x0;
      y++;
    }
}

void	draw_bitmap(int x, int y, char *path, char *fbmem_addr)
{
  int	fd;

int color = 0xff0000;
  

  if ((fd = open(path, O_RDWR)) == -1)
    {
      printf("failed to open the bit map %s", path);
      exit(-1);
    }
  while (y<128 && y < SCREENWIDTH)
    {
      while (x<128 && x < SCREENHEIGHT)
	{
	  
	  draw_pix(x, y, color, fbmem_addr);
	  x++;
	}
      x = 128;
      y++;
    }
}

int	main()
{
  int fd;
  int length = SCREENWIDTH * SCREENHEIGHT * BPP/8;
  char *fbmem_addr;
  struct fb_var_screeninfo modeinfo;
  
  if ((fd = open("/dev/fb0", O_RDWR)) == -1)
    {
      printf("failed to open the fb0");
      exit(-1);
    }
   fbmem_addr = mmap(0, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   
   // int color = RGB16(0xFF, 0, 0);
   ioctl(fd,FBIOGET_VSCREENINFO, &modeinfo);
   
   
   //    draw_rect(0, 0,200, 200, RGB16(255, 56, 2), fbmem_addr);
   draw_bitmap(0,0,"test.bmp", fbmem_addr);



   // draw_rect(12, 78,200, 200, RGB(55, 5, 54), fbmem_addr);
  /*draw_rect(5, 0,225, 206, RGB(88, 66, 5), fbmem_addr);
  draw_rect(2, 20,58, 105, RGB(12, 100, 53), fbmem_addr);
  draw_rect(100, 78,200, 200, RGB(00, 25, 53), fbmem_addr);
  draw_rect(17, 78,200, 200, RGB(200, 42, 11), fbmem_addr);
  draw_rect(58, 150,200, 200, RGB(5, 96, 88), fbmem_addr);
  draw_rect(55, 125,200, 200, RGB(256, 5, 48), fbmem_addr);
  */
  return (0);
}
