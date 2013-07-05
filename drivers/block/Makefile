ifneq ($(KERNELRELEASE), )
obj-m := s3c_nand.o

else
KDIR := /home/fantao/ok6410/linux-3.0.1/
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux-
clean:
	rm -f *.cmd *.ko *.o *.mod.o *.mod.c *.symvers *.order
endif

