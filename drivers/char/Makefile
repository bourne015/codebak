ifneq ($(KERNELRELEASE), )
obj-m += char2.o

else
KVERS = $(shell uname -r)
#KDIR := /home/fantao/ok6410/linux-3.0.1/
KDIR := /lib/modules/$(KVERS)/build

all :
	make -C $(KDIR) M=$(PWD) modules
clean :
	rm -f *.cmd *.ko *.o *.mod.o *.mod.c *.symvers *.order
endif

