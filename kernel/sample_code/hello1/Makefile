CFILES := hello.c sub.c 
obj-m := hello.o 
hello-objs := $(CFILES:.c=.o)
all:
	make -C /lib/modules/$(shell uname -r)/build V=1 M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build V=1 M=$(PWD) clean

