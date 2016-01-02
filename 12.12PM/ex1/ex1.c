#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stropts.h>
#include <sys/mman.h>

#define VIDEO_WIDTH  320
#define VIDEO_HEIGHT 240
#define VIDEO_DEPTH  16

int main()
{
  struct fb_var_screeninfo modeinfo;

  int fdcam = 0, fdfbo = 0;
  int size  = (VIDEO_WIDTH * VIDEO_HEIGHT * VIDEO_DEPTH) / 8;
  int cambuf[size];
  char *fbmem_addr;

  printf("test");

  fdcam = open("/dev/urandom", O_RDWR);
  fdfbo = open("/dev/fb0", O_RDWR);
  if (!fdcam || !fdfbo)
    printf("ERROR: Bad file descriptor\n");
  
  ioctl(fdfbo, FBIOGET_VSCREENINFO, &modeinfo);

  //  fbmem_addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fdfbo, 0);
  //while (cinfo.next_scanline < cinfo.image_height)
  /*{
      row_pointer[0] = &image_buffer[cinfo.next_scanline * image_width * 3];
      (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
      }*/

  draw_pixel(10,10);
    // write(1, "suce\n", 5);
    //read(fdcam, fbmem_addr, size);
    //write(fdfbo, fbmem_addr, size);
    //}
  return 0;
}
