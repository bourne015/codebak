ifneq ($(KERNELRELEASE), )
obj-m += key_dev.o
obj-m += key_drv.o

else
KDIR := /home/tao/ok6410/forlinx/linux-3.0.1/
all :
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux-
clean :
	rm -f *.cmd *.ko *.o *.mod.o *.mod.c *.symvers *.order
endif

