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

#define FON(led) ioctl(fd, ON, led)
#define FOFF(led) ioctl(fd, OFF, led)

#define GREEN   2
#define YELLOW  1
#define RED     0

int main()
{
    int fd, i;

    fd = open("/dev/leds", O_WRONLY);
    if (fd < 0)
    {
        perror("open devices leds");
        exit(1);
    }
    for (i = 0; i < 4; i++)
        FOFF(i);
    // green on 30 sec
    FON(GREEN);
    sleep(30);
    FOFF(GREEN);
    // green flash 3 times
    for (i = 0; i < 3; i++)
    {
        usleep(500000);
        FON(GREEN);
        usleep(500000);
        FOFF(GREEN);
    }
    FON(YELLOW);
    sleep(4); 
    FOFF(YELLOW);
    FON(RED);
    sleep(30);
    FOFF(RED);
    close(fd);
    return 0;
}
