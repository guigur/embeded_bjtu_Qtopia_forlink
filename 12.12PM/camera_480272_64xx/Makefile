CROSS_COMPILE =/usr/local/arm/4.3.2/bin/arm-linux-
KERNELDIR =
#CFLAGS = -I$(KERNELDIR)/include -O -Wall -static
CFLAGS = -O
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

ALL :  testcamera 

testcamera:  v4l2.c

	$(CC) -o  testcamera  v4l2.c $(CFLAGS) -I/usr/local/arm/4.3.2/include
 	
clean :
	rm -rf testcamera
