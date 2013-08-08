ifneq ($(KERNELRELEASE), )
obj-m := nand_drv.o
obj-m += nand_dev.o

else
KDIR := /home/fantao/ok6410/forlinx/linux-3.0.1/
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux-
clean:
	rm -f *.cmd *.ko *.o *.mod.o *.mod.c *.symvers *.order
endif

