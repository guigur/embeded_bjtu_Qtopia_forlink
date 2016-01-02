#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stropts.h>
#include <sys/mman.h>

#include <cpio.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pthread.h>
#include <pwd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <tar.h>
#include <termios.h>
#include <unistd.h>
#include <utime.h>

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VIDEO_WIDTH  320
#define VIDEO_HEIGHT 240
#define VIDEO_DEPTH  16


int main()
{
  struct fb_var_screeninfo modeinfo;

  struct v4l2_format fmt; //Frame format, such

  int fdcam = 0, fdfbo = 0;
  int size  = (VIDEO_WIDTH * VIDEO_HEIGHT * VIDEO_DEPTH) / 8;
  int cambuf[size];
  char *fbmem_addr;

  //  int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  //fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  //fmt.fmt.pix.width = VIDEO_WIDTH;
  //fmt.fmt.pix.height = VIDEO_HEIGHT;
  //fmt.fmt.pix.depth = VIDEO_DEPTH;
  //fmt.fmt.pix.pixelformat= V4L2_PIX_FMT_RGB565;
  printf("test");

  fdcam = open("/dev/urandom", O_RDWR);
  fdfbo = open("/dev/fb0", O_RDWR);
  if (!fdcam || !fdfbo)
    printf("ERROR: Bad file descriptor\n");
  
  ioctl(fdfbo, FBIOGET_VSCREENINFO, &modeinfo);
  // ioctl(fdcam, VIDIOC_S_FMT, &fmt);
  //ioctl(fdcam, VIDIOC_STREAMON, &type);
  fbmem_addr = mmap(0, size, PROT_READ |
		    PROT_WRITE, MAP_SHARED, fdfbo, 0);
  while (42)
  {
    write(1, "suce\n", 5);
    read(fdcam, fbmem_addr, size);
    write(fdfbo, fbmem_addr, size);
  }
  return 0;
}
