/* guigur 2015
 * vive les margoulins
 */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define ON  0
#define OFF 1

int	main()
{
  int	fd;
  
  printf("Content-type: text/html;charset=gb2312\n\n");
  printf("hello,<b>world</b><br>\n");
  
  fd = open("/dev/leds", O_WRONLY);
  if (fd < 0)
    {
      perror("cant open tty leds");
      exit(-1);
    }
  ioctl(fd, ON, 0);
  //  printf(EXIT_FAILURE);
  return (0);
}
