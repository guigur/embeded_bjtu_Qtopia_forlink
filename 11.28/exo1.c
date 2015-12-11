#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stropts.h>
//#include <sys/mman.h>

#define ON  0
#define OFF 1

int main()
{
    int fd;

    fd = open("/dev/leds", O_WRONLY);
    if (fd < 0)
    {
        perror("open devices leds");
        exit(1);
    }
    printf("Opened");
    int i;
    // ALL on
    for (i = 0; i < 4; i++)
        ioctl(fd, ON, i);
    sleep(3);
    // ALL off
    for (i = 0; i < 4; i++)
        ioctl(fd, OFF, i);
    sleep(3);
    // ALL on one by one
    for (i = 0; i < 4; i++)
    {
        ioctl(fd, ON, i);
        sleep(1);
    }
    // ALL Off
    for (i = 0; i < 4; i++)
        ioctl(fd, OFF, i);
    close(fd);
    printf("END\n");
    return 0;
}
