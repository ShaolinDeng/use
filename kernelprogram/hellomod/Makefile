ifeq ($(KERNELRELEASE),)
	obj-m :=hello.o
else
	KERNELDIR ? =/home/dengshaolin/linux-2.6.31.6
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)modules
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c
endif
