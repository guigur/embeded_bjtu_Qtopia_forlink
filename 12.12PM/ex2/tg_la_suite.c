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

typedef struct InputData
{
  unsigned int dummy1;
  unsigned int dummy2;
  unsigned short type;
  unsigned short code;
  unsigned int value;
  unsigned int dummy3;
  unsigned int dummy4;
  unsigned int dummy5;
  unsigned int dummy6;
}input_t;


void saveimg(char *buffer)
{
  struct jpeg_compress_struct cinfo;
  FILE *outfile = fopen("/tmp/test.jpeg", "w+");
  JSAMPROW row_pointer[CAM_HEIGHT];
  int scanline = 0;

  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, outfile);

  cinfo.image_height = CAM_HEIGHT;
  cinfo.image_width  = CAM_WIDTH;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;

  jpeg_set_defaults(&cinfo);
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_start_compress(&cinfo, 1);
  while (cinfo.next_scanline < cinfo.image_height)
  {
    row_pointer[0] = &buffer[cinfo.next_scanline * cinfo.image_width * 3];
    jpeg_write_scanlines(&cinfo,row_pointer,1);
  }

  jpeg_finish_compress(&cinfo);
}

int main()
{
  struct fb_var_screeninfo modeinfo;
  struct v4l2_format fmt; //Frame format, such

  int fdcam = 0, fdfbo = 0, fdev = 0;
  input_t input;
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

  read(fdev, &input, sizeof(input));
  fdcam = open("/dev/video0", O_RDWR);
  fdfbo = open("/dev/fb0", O_RDWR);
  fdev  = open("/dev/event0", O_RDONLY);
  if (!fdcam || !fdfbo || !fdev)
    printf("ERROR: Bad file descriptor\n");
  
  ioctl(fdfbo, FBIOGET_VSCREENINFO, &modeinfo);
  ioctl(fdcam, VIDIOC_S_FMT, &fmt);
  ioctl(fdcam, VIDIOC_STREAMON, &fmt.type);
    
  while (42)
{
  fbmem_addr = mmap(0, cam_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdfbo, 0);
  read(fdcam,  fbmem_addr, cam_size);
  write(fdfbo, fbmem_addr, video_size);
  if (input.type == 1 && input.code == 106 && input.value == 1)
    saveimg(fbmem_addr);
 }
 
  return 0;
}
