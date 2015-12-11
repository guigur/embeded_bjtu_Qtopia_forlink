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


int main()
{
    int fd, m_fd, i;

    fd = open("/dev/leds", O_WRONLY);
    if (fd < 0)
    {
        perror("open devices leds");
        exit(1);
    }
    // Off all led
    for (i = 0; i < 4; i++)
        FOFF(i);

    m_fd = open("/dev/input/event0", O_RDONLY /*| O_NONBLOCK*/);
    if (m_fd < 0)
    {
        perror("open devices key");
        exit(1);
    }
    printf("Key Opened\n");
    input_t input;
    while (42)
    {
        int ret =  read(m_fd, &input, sizeof(input));
        printf("read return %d but struct size is %d\n", ret, sizeof(input));
        if (sizeof(input) != ret)
        {
            perror("Read has fail\n");
            exit(1);
        }
        printf("Key readed\n");
        printf("type =%d code=%d value=%d\n", input.type, input.code, input.value);
    }
    close(m_fd);
    close(fd);
    return 0;
}
