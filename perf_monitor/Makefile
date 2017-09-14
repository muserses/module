#
# Makefile
# muserses, 2017-01-14 18:01
#

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-


obj-m := PerfMonitor.o
KDIR := ~/linux

#CCFLAG = -std=gnu99

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean


# vim:ft=make
#
