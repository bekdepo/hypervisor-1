obj-m += hvisor.o
hvisor-objs := hypervisor.o platform_linux.o arch_x64.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

