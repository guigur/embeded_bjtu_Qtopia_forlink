#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jpeglib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#define VIDEO_WIDTH  480
#define VIDEO_HEIGHT 272
#define VIDEO_DEPTH  16

#define CAM_WIDTH 320
#define CAM_HEIGHT 240
#define CAM_DEPTH 24

void saveimg(char *buffer)
{
  struct jpeg_compress_struct cinfo;
  FILE *outfile = fopen("/tmp/test.jpeg", "w+");
  JSAMPROW row_pointer[CAM_HEIGHT];
  int scanline = 0;
  fprintf(outfile, "SALUT");
  fclose(outfile);
  /*  printf("1\n");
  jpeg_create_compress(&cinfo);
  printf("2\n");
  jpeg_stdio_dest(&cinfo, outfile);
  printf("3\n");
  cinfo.image_height = CAM_HEIGHT;

    printf("4\n");
    cinfo.image_width  = CAM_WIDTH;
  printf("5\n");
    cinfo.input_components = 3;
  printf("6\n");
    cinfo.in_color_space = JCS_RGB;
  printf("7\n");
  jpeg_set_defaults(&cinfo);
  printf("8\n");
  */
  //  jpeg_start_compress(&cinfo, 1);
  /*printf("9\n");
    while (cinfo.next_scanline < cinfo.image_height)
  {
    row_pointer[0] = &buffer[cinfo.next_scanline * cinfo.image_width * 3];
    jpeg_write_scanlines(&cinfo,row_pointer,1);
    }

  //jpeg_finish_compress(&cinfo);
  printf("10\n");*/
  
}

int main()
{
  struct fb_var_screeninfo modeinfo;
  struct v4l2_format fmt; //Frame format, such

  int fdcam = 0, fdfbo = 0;
  int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  fmt.fmt.pix.width  = VIDEO_WIDTH;
  fmt.fmt.pix.height = VIDEO_HEIGHT;
  //fmt.fmt.pix.depth  = VIDEO_DEPTH;
  fmt.fmt.pix.pixelformat= V4L2_PIX_FMT_RGB565;
  
  int video_size  = (VIDEO_WIDTH * VIDEO_HEIGHT * VIDEO_DEPTH) / 8;
  int cam_size  = (CAM_WIDTH * CAM_HEIGHT * CAM_DEPTH) / 8;
  //int cambuf[size];
  char *fbmem_addr;

  fdcam = open("/dev/urandom", O_RDWR);
  fdfbo = open("/dev/fb0", O_RDWR);
  if (!fdcam || !fdfbo)
    printf("ERROR: Bad file descriptor\n");
  
  ioctl(fdfbo, FBIOGET_VSCREENINFO, &modeinfo);
  ioctl(fdcam, VIDIOC_S_FMT, &fmt);
  ioctl(fdcam, VIDIOC_STREAMON, &fmt.type);
    
  while (42)
{
  fbmem_addr = mmap(0, cam_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdfbo, 0);
  read(fdcam,  fbmem_addr, cam_size);
  write(fdfbo, fbmem_addr, video_size);
  saveimg(fbmem_addr);
 }
 
  return 0;
}
