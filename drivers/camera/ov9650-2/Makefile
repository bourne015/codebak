ifneq ($(KERNELRELEASE), )
obj-m += ov9650_drv.o
obj-m += ov9650_dev.o
#obj-m += mylcd.o
#obj-m += lcd-dev.o
#obj-m += lcd-drv.o

else
KDIR := /home/tao/ok6410/forlinx/linux-3.0.1
all :
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux-
clean :
	rm -f *.cmd *.ko.cmd *.ko *.o *.mod.o *.mod.c *.symvers *.order
endif

