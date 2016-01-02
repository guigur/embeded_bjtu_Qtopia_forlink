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

  fdcam = open("/dev/video0", O_RDWR);
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
  }
 
  return 0;
}
