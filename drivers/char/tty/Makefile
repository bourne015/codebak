KERNELDIR=/home/fantao/ok6410/linux-3.0.1
# The current directory is passed to sub-makes as argument
PWD:=$(shell pwd)
#INSTALLDIR=/arm2410s/basic/gprs
CROSS_COMPILE=arm-linux-
CC=$(CROSS_COMPILE)gcc


obj-m := gprs.o

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	cp gprs.ko $(INSTALLDIR)


clean:
	rm -rf *.o *~ core *.symvers .depend .*.cmd *.ko *.mod.c .tmp_versions $(INSTALLDIR)/gprs.ko

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

#.PHONY: modules modules_install clean


