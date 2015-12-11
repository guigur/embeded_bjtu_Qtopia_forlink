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
#include <string.h>



#define ON  0
#define OFF 1

#define LED_ON(led) ioctl(fd_leds, ON, led)
#define LED_OFF(led) ioctl(fd_leds, OFF, led)

int	fd_leds;

void led_all_off(int fd_led);
// http param parsing GET/POST
int cgiGetVal(char *);
int is_this_param(char *param, char *data);
int extract_value(char *param, char *data);
void print_small_form();

int	main()
{

    //printf("HTTP/1.1 302\n\n");
    //printf("Location: /ex1.html\n\n");
    printf("Content-type: text/html;charset=gb2312\n\n");

    printf("hello,<b>world</b><br>\n");

    fd_leds = open("/dev/leds", O_WRONLY);
    if (fd_leds < 0)
    {
        perror("cant open tty leds");
        exit(-1);
    }
    led_all_off(fd_leds);

    char *data = getenv("QUERY_STRING");
    long led_num = 0;

    if (data == NULL)
    {
        printf("<P>Error: Error in passing data from form to script.");
        return 0;
    }

    char led_name[4][8] = {"LED1", "LED2", "LED3", "LED4"};
    for (int i = 0; i < 4; i++)
        if (cgiGetVal(led_name[i]) != -1)
        {
            LED_ON(i);
            printf("<P> %s is on", led_name[i]);
        }
    print_small_form();
    return (0);
}

void led_all_off(int fd_led)
{
    int i = 0;
    for (i = 0; i <= 3; i++)
        LED_OFF(i);
}

// form
void print_small_form()
{
    char form[1024];
    int fd = open("ex1.html", O_RDONLY); 
    int ret = read(fd, form, 1022);
    close(fd);
    form[ret] = 0;
    printf("%s", form);
}

// ======================= CGI LIB

int cgiGetVal(char *param)
{
    char *data = getenv("QUERY_STRING");
    int i = 0;

    if (data == NULL)
        return -1;
    if (data[i] != '\0' && is_this_param(param, data))
        return extract_value(param, data);
    while (data[i] != '\0')
    {
        if (data[i] == '&')
        {
            if (is_this_param(param, data + i + 1))
                return extract_value(param, data + i + 1);
        }
        i++;
    }
    return -1;
}

int is_this_param(char *param, char *data)
{
    // printf("<P> is this param %s for {%s}", param, data);
    int len = strlen(param);
    if (!(strlen(data) >= (len + 1)))
        return 0;
    if (strncmp(param, data, len) == 0)
        return 1;
    // printf("<P>No match");
    return 0;
}

int extract_value(char *param, char *data)
{
    int val = 0;
    if (sscanf(data + strlen(param) + 1, "%ld", &val) != 1)
        return 0;
    return val;
}
